package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller;

import javafx.beans.binding.Bindings;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.util.StringConverter;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.validator.ProductValidator;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.ProductRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Product;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.EditCell;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.ProductEntry;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.net.URL;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import java.util.function.Function;

/**
 * Controller for the product view.
 */
public class ProductController implements Initializable {
    @FXML
    public TableView<ProductEntry> productTableView;
    @FXML
    public TextField productNameTextField;
    @FXML
    public TextField productPriceTextField;
    @FXML
    public TextField productQuantityTextField;

    private final ProductRepository productRepository;
    private final ObservableList<ProductEntry> productEntries;
    private final ProductValidator validator;

    /**
     * Initializes a new instance of the ProductController class.
     *
     * @param productRepository The product repository.
     */
    public ProductController(ProductRepository productRepository) {
        this.productRepository = productRepository;
        productEntries = productRepository.productEntries;
        validator = new ProductValidator();
    }

    /**
     * Initializes the controller.
     *
     * @param url            The URL.
     * @param resourceBundle The resource bundle.
     */
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        initializeColumns();
        productTableView.setItems(productEntries);
        initializeContextMenu();
        productTableView.getItems().addListener((ListChangeListener.Change<? extends ProductEntry> change) -> {
            while (change.next()) {
                if (change.wasUpdated()) {
                    for (var x : change.getList().subList(change.getFrom(), change.getTo())) {
                        productRepository.update(x.getId(), new Product(x.getId(), x.getName(), x.getPrice(), x.getQuantity()));
                    }
                }
            }
        });

        productTableView.setOnKeyPressed(event -> {
            TablePosition<ProductEntry, ?> pos = productTableView.getFocusModel().getFocusedCell();
            if (pos != null) {
                productTableView.edit(pos.getRow(), pos.getTableColumn());
            }
        });
    }

    /**
     * Creates a new column for the table view.
     *
     * @param field    The field to create the column for.
     * @param property The property to bind the column to.
     * @param <T>      The type of the column.
     * @return The created column.
     */
    private <T> TableColumn<T, String> createColumn(Field field, Function<T, StringProperty> property) {
        TableColumn<T, String> col = new TableColumn<>(field.getName());
        col.setCellValueFactory(cellData -> property.apply(cellData.getValue()));

        col.setCellFactory(column -> EditCell.createStringEditCell());
        return col;
    }

    /**
     * Initializes the columns of the table view.
     */
    private void initializeColumns() {
        productTableView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        productTableView.getSelectionModel().setCellSelectionEnabled(true);
        productTableView.setEditable(true);

        List<Field> fields = Arrays.asList(ProductEntry.class.getDeclaredFields());

        for (Field field : fields) {
            try {
                Method propertyMethod = ProductEntry.class.getDeclaredMethod(field.getName() + "Property");
                Function<ProductEntry, StringProperty> propertyFunction = instance -> {
                    try {
                        Object result = propertyMethod.invoke(instance);
                        if (result instanceof StringProperty) {
                            return (StringProperty) result;
                        } else if (result instanceof IntegerProperty) {
                            IntegerProperty intProp = (IntegerProperty) result;
                            StringProperty stringProperty = new SimpleStringProperty();

                            Bindings.bindBidirectional(
                                    stringProperty,
                                    intProp,
                                    new StringConverter<Number>() {
                                        @Override
                                        public String toString(Number object) {
                                            if (object == null) {
                                                return "";
                                            }
                                            return String.valueOf(object.intValue());
                                        }

                                        @Override
                                        public Number fromString(String string) {
                                            try {
                                                return Integer.parseInt(string);
                                            } catch (NumberFormatException e) {
                                                return null;
                                            }
                                        }
                                    }
                            );

                            return stringProperty;
                        } else if (result instanceof DoubleProperty) {
                            DoubleProperty doubleProp = (DoubleProperty) result;
                            StringProperty stringProperty = new SimpleStringProperty();

                            Bindings.bindBidirectional(
                                    stringProperty,
                                    doubleProp,
                                    new StringConverter<Number>() {
                                        @Override
                                        public String toString(Number object) {
                                            if (object == null) {
                                                return "";
                                            }
                                            return String.valueOf(object.doubleValue());
                                        }

                                        @Override
                                        public Number fromString(String string) {
                                            try {
                                                return Double.parseDouble(string);
                                            } catch (NumberFormatException e) {
                                                return null;
                                            }
                                        }
                                    }
                            );

                            return stringProperty;
                        }

                        return null;
                    } catch (Exception e) {
                        e.printStackTrace();
                        return null;
                    }
                };

                var column = createColumn(field, propertyFunction);
                productTableView.getColumns().add(column);

            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Initializes the context menu for the table view with a delete button.
     */
    private void initializeContextMenu() {
        ContextMenu contextMenu = new ContextMenu();
        MenuItem deleteItem = new MenuItem("Delete");
        deleteItem.setOnAction(event -> {
            ProductEntry selectedItem = productTableView.getSelectionModel().getSelectedItem();
            productRepository.delete(selectedItem.getId());
        });
        contextMenu.getItems().add(deleteItem);
        productTableView.setContextMenu(contextMenu);
    }

    /**
     * Handles the add product button click event.
     */
    public void onAddProduct() {
        if (!validator.validateProduct(productNameTextField.getText(),
                productPriceTextField.getText(),
                productQuantityTextField.getText())
        ) {
            return;
        }

        String name = productNameTextField.getText();
        double price = Double.parseDouble(productPriceTextField.getText());
        int quantity = Integer.parseInt(productQuantityTextField.getText());

        Product product = new Product(name, price, quantity);
        productRepository.insert(product);
    }
}
