package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata;

import javafx.beans.property.*;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Product;

/**
 * Represents an entry for a product in the table, wrapping a {@link Product} object.
 */
public class ProductEntry {
    public IntegerProperty id;
    public StringProperty name;
    public DoubleProperty price;
    public IntegerProperty quantity;

    /**
     * Constructs a ProductEntry object based on the provided {@link Product}.
     *
     * @param product The product object to wrap.
     */
    public ProductEntry(Product product) {
        this.id = new SimpleIntegerProperty(product.getId());
        this.name = new SimpleStringProperty(product.getName());
        this.price = new SimpleDoubleProperty(product.getPrice());
        this.quantity = new SimpleIntegerProperty(product.getQuantity());
    }

    public final IntegerProperty idProperty() {
        return this.id;
    }

    public final StringProperty nameProperty() {
        return this.name;
    }

    public final DoubleProperty priceProperty() {
        return this.price;
    }

    public final IntegerProperty quantityProperty() {
        return this.quantity;
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

    public double getPrice() {
        return price.get();
    }

    public void setPrice(double price) {
        this.price.set(price);
    }

    public int getQuantity() {
        return quantity.get();
    }

    public void setQuantity(int quantity) {
        this.quantity.set(quantity);
    }
}
