package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Client;

/**
 * Represents an entry for a client in the table, wrapping a {@link Client} object.
 */
public class ClientEntry {
    public IntegerProperty id;
    public StringProperty name;
    public StringProperty email;
    public StringProperty password;
    public StringProperty address;

    /**
     * Constructs a ClientEntry object based on the provided {@link Client}.
     *
     * @param client The client object to wrap.
     */
    public ClientEntry(Client client) {
        this.id = new SimpleIntegerProperty(client.getId());
        this.name = new SimpleStringProperty(client.getName());
        this.email = new SimpleStringProperty(client.getEmail());
        this.password = new SimpleStringProperty(client.getPassword());
        this.address = new SimpleStringProperty(client.getAddress());
    }

    public final IntegerProperty idProperty() {
        return this.id;
    }

    public final StringProperty nameProperty() {
        return this.name;
    }

    public final StringProperty emailProperty() {
        return this.email;
    }

    public final StringProperty passwordProperty() {
        return this.password;
    }

    public final StringProperty addressProperty() {
        return this.address;
    }

    public int getId() {
        return id.get();
    }

    public void setId(int id) {
        this.id.set(id);
    }

    public String getName() {
        return name.get();
    }

    public void setName(String name) {
        this.name.set(name);
    }

    public String getEmail() {
        return email.get();
    }

    public void setEmail(String email) {
        this.email.set(email);
    }

    public String getPassword() {
        return password.get();
    }

    public void setPassword(String password) {
        this.password.set(password);
    }

    public String getAddress() {
        return address.get();
    }

    public void setAddress(String address) {
        this.address.set(address);
    }
}
