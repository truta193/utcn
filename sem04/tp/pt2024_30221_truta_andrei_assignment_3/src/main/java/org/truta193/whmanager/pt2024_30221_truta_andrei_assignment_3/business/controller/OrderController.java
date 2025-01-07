package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller;

import javafx.beans.binding.Bindings;
import javafx.beans.property.*;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.util.StringConverter;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.validator.OrderValidator;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.ClientRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.OrderRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.ProductRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Order;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Product;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.ClientEntry;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.OrderEntry;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.ProductEntry;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.net.URL;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import java.util.function.Function;

/**
 * Controller for the order view.
 */
public class OrderController implements Initializable {

    private final OrderRepository orderRepository;
    private final ClientRepository clientRepository;
    private final ProductRepository productRepository;
    private final ObservableList<OrderEntry> orderEntries;
    private final ObservableList<ClientEntry> clientEntries;
    private final ObservableList<ProductEntry> productEntries;
    private final OrderValidator validator;

    @FXML
    public TableView<OrderEntry> orderTableView;
    @FXML
    public TableView<ClientEntry> clientTableView;
    @FXML
    public TableView<ProductEntry> productTableView;
    @FXML
    public Button orderButton;
    @FXML
    public TextField quantityTextField;

    /**
     * Property that indicates if the order is valid.
     */
    private BooleanProperty isOrderValid = new SimpleBooleanProperty(true);

    /**
     * Initializes a new instance of the OrderController class.
     *
     * @param orderRepository   The order repository.
     * @param clientRepository  The client repository.
     * @param productRepository The product repository.
     */
    public OrderController(OrderRepository orderRepository, ClientRepository clientRepository, ProductRepository productRepository) {
        this.orderRepository = orderRepository;
        this.clientRepository = clientRepository;
        this.productRepository = productRepository;

        orderEntries = orderRepository.orderEntries;
        clientEntries = clientRepository.clientEntries;
        productEntries = productRepository.productEntries;

        validator = new OrderValidator();
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
        orderTableView.setItems(orderEntries);
        clientTableView.setItems(clientEntries);
        productTableView.setItems(productEntries);
        initializeContextMenu();

        orderTableView.setOnKeyPressed(event -> {
            TablePosition<OrderEntry, ?> pos = orderTableView.getFocusModel().getFocusedCell();
            if (pos != null) {
                orderTableView.edit(pos.getRow(), pos.getTableColumn());
            }
        });
    }

    /**
     * Gets the value of the orderValid property.
     *
     * @return The value of the orderValid property.
     */
    public final Boolean getOrderValid() {
        return isOrderValid.get();
    }

    /**
     * Sets the value of the orderValid property.
     *
     * @param value The value to set.
     */
    public final void setOrderValid(Boolean value) {
        isOrderValid.set(value);
    }

    /**
     * Gets the orderValid property.
     *
     * @return The orderValid property.
     */
    public final BooleanProperty orderValidProperty() {
        return this.isOrderValid;
    }

    /**
     * Creates a new column for the table view.
     *
     * @param field    The field to create the column for.
     * @param property The property function.
     * @param <T>      The type of the table view.
     * @return The created column.
     */
    private <T> TableColumn<T, String> createColumn(Field field, Function<T, StringProperty> property) {
        TableColumn<T, String> col = new TableColumn<>(field.getName());
        col.setCellValueFactory(cellData -> property.apply(cellData.getValue()));
        return col;
    }

    /**
     * Initializes the columns for the table views.
     */
    private void initializeColumns() {
        orderTableView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        orderTableView.getSelectionModel().setCellSelectionEnabled(true);
        orderTableView.setEditable(true);

        List<Field> fields = Arrays.asList(OrderEntry.class.getDeclaredFields());

        for (Field field : fields) {
            try {
                Method propertyMethod = OrderEntry.class.getDeclaredMethod(field.getName() + "Property");
                Function<OrderEntry, StringProperty> propertyFunction = instance -> {
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
                orderTableView.getColumns().add(column);

            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
        }

        List<Field> clientFields = Arrays.asList(ClientEntry.class.getDeclaredFields());
        for (Field field : clientFields) {
            try {
                Method propertyMethod = ClientEntry.class.getDeclaredMethod(field.getName() + "Property");
                Function<ClientEntry, StringProperty> propertyFunction = instance -> {
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
                        }

                        return null;
                    } catch (Exception e) {
                        e.printStackTrace();
                        return null;
                    }
                };

                var column = createColumn(field, propertyFunction);
                clientTableView.getColumns().add(column);

            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
        }

        List<Field> productFields = Arrays.asList(ProductEntry.class.getDeclaredFields());
        for (Field field : productFields) {
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
     * Initializes the context menu for the table view.
     */
    private void initializeContextMenu() {
        ContextMenu contextMenu = new ContextMenu();
        MenuItem deleteItem = new MenuItem("Delete");
        deleteItem.setOnAction(event -> {
            OrderEntry selectedItem = orderTableView.getSelectionModel().getSelectedItem();
            orderRepository.delete(selectedItem.getId());
            orderEntries.remove(selectedItem);
        });
        contextMenu.getItems().add(deleteItem);
        orderTableView.setContextMenu(contextMenu);
    }

    /**
     * Handles the order button click event.
     */
    public void onOrder() {
        if (!validator.validateOrder(clientTableView, productTableView, quantityTextField.getText())) {
            isOrderValid.set(false);
            return;
        } else {
            isOrderValid.set(true);
        }

        ClientEntry clientEntry = clientTableView.getSelectionModel().getSelectedItem();
        ProductEntry productEntry = productTableView.getSelectionModel().getSelectedItem();

        int quantity = Integer.parseInt(quantityTextField.getText());
        Product trueProduct = productRepository.getById(productEntry.getId());
        if (trueProduct.getQuantity() < quantity || quantity <= 0) {
            return;
        }

        orderRepository.insert(new Order(clientEntry.getId(), productEntry.getId(), quantity, quantity * trueProduct.getPrice()));
        trueProduct.setQuantity(trueProduct.getQuantity() - quantity);
        productEntries.set(productEntries.indexOf(productEntry), new ProductEntry(trueProduct));
    }
}
