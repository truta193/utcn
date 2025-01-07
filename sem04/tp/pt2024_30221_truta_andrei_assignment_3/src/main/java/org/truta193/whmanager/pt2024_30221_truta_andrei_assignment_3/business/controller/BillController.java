package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller;

import javafx.beans.binding.Bindings;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.BillRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.BillEntry;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.EditCell;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.net.URL;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import java.util.function.Function;

/**
 * Controller for the bill view.
 */
public class BillController implements Initializable {
    @FXML
    public TableView billTableView;

    private final BillRepository billRepository;
    private final ObservableList<BillEntry> billEntries;

    public BillController(BillRepository billRepository) {
        this.billRepository = billRepository;
        billEntries = billRepository.billEntries;
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
        billTableView.setItems(billEntries);
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

        col.setCellFactory(column -> EditCell.createStringEditCell());
        return col;
    }

    /**
     * Initializes the columns for the table view using reflection
     */
    private void initializeColumns() {
        List<Field> fields = Arrays.asList(BillEntry.class.getDeclaredFields());

        for (Field field : fields) {
            try {
                Method propertyMethod = BillEntry.class.getDeclaredMethod(field.getName() + "Property");
                Function<BillEntry, StringProperty> propertyFunction = instance -> {
                    try {
                        Object result = propertyMethod.invoke(instance);
                        if (result instanceof StringProperty) {
                            return (StringProperty) result;
                        } else if (result instanceof IntegerProperty) {
                            IntegerProperty intProp = (IntegerProperty) result;
                            StringProperty stringProperty = new SimpleStringProperty();
                            stringProperty.bind(Bindings.createStringBinding(
                                    () -> String.valueOf(intProp.get()),
                                    intProp
                            ));
                            return stringProperty;
                        }

                        return null;
                    } catch (Exception e) {
                        e.printStackTrace();
                        return null;
                    }
                };

                var column = createColumn(field, propertyFunction);
                billTableView.getColumns().add(column);

            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
        }
    }
}
