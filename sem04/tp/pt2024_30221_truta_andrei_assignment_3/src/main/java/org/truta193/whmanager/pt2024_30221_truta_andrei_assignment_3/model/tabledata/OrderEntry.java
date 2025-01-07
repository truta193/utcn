package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata;

import javafx.beans.property.DoubleProperty;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleIntegerProperty;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Order;

/**
 * Represents an entry for an order in the table, wrapping an {@link Order} object.
 */
public class OrderEntry {
    private IntegerProperty id;
    private IntegerProperty clientId;
    private IntegerProperty productId;
    private IntegerProperty quantity;
    private DoubleProperty price;

    /**
     * Constructs an OrderEntry object based on the provided {@link Order}.
     *
     * @param order The order object to wrap.
     */
    public OrderEntry(Order order) {
        this.id = new SimpleIntegerProperty(order.getId());
        this.clientId = new SimpleIntegerProperty(order.getClientId());
        this.productId = new SimpleIntegerProperty(order.getProductId());
        this.quantity = new SimpleIntegerProperty(order.getQuantity());
        this.price = new SimpleDoubleProperty(order.getPrice());
    }

    public IntegerProperty idProperty() {
        return id;
    }

    public IntegerProperty clientIdProperty() {
        return clientId;
    }

    public IntegerProperty productIdProperty() {
        return productId;
    }

    public IntegerProperty quantityProperty() {
        return quantity;
    }

    public DoubleProperty priceProperty() {
        return price;
    }

    public int getId() {
        return id.get();
    }

    public void setId(int id) {
        this.id.set(id);
    }

    public int getClientId() {
        return clientId.get();
    }

    public void setClientId(int clientId) {
        this.clientId.set(clientId);
    }

    public int getProductId() {
        return productId.get();
    }

    public void setProductId(int productId) {
        this.productId.set(productId);
    }

    public int getQuantity() {
        return quantity.get();
    }

    public void setQuantity(int quantity) {
        this.quantity.set(quantity);
    }

    public Double getPrice() {
        return price.get();
    }

    public void setPrice(int price) {
        this.price.set(price);
    }
}
