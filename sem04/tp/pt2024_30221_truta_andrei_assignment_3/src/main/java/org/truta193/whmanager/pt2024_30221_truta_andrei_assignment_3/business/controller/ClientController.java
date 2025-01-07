package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller;

import javafx.beans.binding.Bindings;
import javafx.beans.property.*;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.validator.ClientValidator;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.ClientRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Client;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.ClientEntry;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.EditCell;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.math.BigInteger;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import java.util.function.Function;

public class ClientController implements Initializable {
    @FXML
    public TableView<ClientEntry> clientTableView;
    @FXML
    public TextField clientNameTextField;
    @FXML
    public TextField clientEmailTextField;
    @FXML
    public TextField clientAddressTextField;
    @FXML
    public TextField clientPasswordTextField;
    public Button addClientButton;

    private ClientRepository clientRepository;
    private ObservableList<ClientEntry> clientEntries;
    private ClientValidator validator;

    /**
     * Initializes a new instance of the ClientController class.
     *
     * @param clientRepository The client repository.
     */
    public ClientController(ClientRepository clientRepository) {
        this.clientRepository = clientRepository;
        clientEntries = clientRepository.clientEntries;
        validator = new ClientValidator();
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
        clientTableView.setItems(clientEntries);
        initializeContextMenu();
        clientTableView.getItems().addListener((ListChangeListener.Change<? extends ClientEntry> change) -> {
            while (change.next()) {
                if (change.wasUpdated()) {
                    for (var x : change.getList().subList(change.getFrom(), change.getTo())) {
                        clientRepository.update(x.getId(), new Client(x.getId(), x.getName(), x.getEmail(), x.getPassword(), x.getAddress()));
                    }
                }
            }
        });

        clientTableView.setOnKeyPressed(event -> {
            TablePosition<ClientEntry, ?> pos = clientTableView.getFocusModel().getFocusedCell();
            if (pos != null) {
                clientTableView.edit(pos.getRow(), pos.getTableColumn());
            }
        });
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
     * Initializes the context menu for the table view with a delete button.
     */
    private void initializeContextMenu() {
        ContextMenu contextMenu = new ContextMenu();
        MenuItem deleteItem = new MenuItem("Delete");
        deleteItem.setOnAction(event -> {
            ClientEntry selectedItem = clientTableView.getSelectionModel().getSelectedItem();
            clientRepository.delete(selectedItem.getId());
        });
        contextMenu.getItems().add(deleteItem);
        clientTableView.setContextMenu(contextMenu);
    }

    /**
     * Initializes the columns for the table view using reflection
     */
    private void initializeColumns() {
        clientTableView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        clientTableView.getSelectionModel().setCellSelectionEnabled(true);
        clientTableView.setEditable(true);

        List<Field> fields = Arrays.asList(ClientEntry.class.getDeclaredFields());

        for (Field field : fields) {
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
                clientTableView.getColumns().add(column);

            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Adds a new client to the repository.
     */
    public void onAddClient() {
        var client = new Client(
                clientNameTextField.getText(),
                clientEmailTextField.getText(),
                clientPasswordTextField.getText(),
                clientAddressTextField.getText()
        );
        if (!validator.validateClient(client)) {
            return;
        }

        try {
            SecureRandom random = new SecureRandom();
            byte[] salt = new byte[16];
            random.nextBytes(salt);
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(client.getPassword().getBytes(StandardCharsets.UTF_8));

            client.setPassword(toHexString(hashedPassword));
            clientRepository.insert(client);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }


    /**
     * Converts a byte array to a hexadecimal string.
     *
     * @param hash The byte array to convert.
     * @return The hexadecimal string.
     */
    public static String toHexString(byte[] hash)
    {
        BigInteger number = new BigInteger(1, hash);
        StringBuilder hexString = new StringBuilder(number.toString(16));

        while (hexString.length() < 64)
        {
            hexString.insert(0, '0');
        }

        return hexString.toString();
    }
}


