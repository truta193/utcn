package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model;

/**
 * Represents an order.
 */
public class Order {
    private int id;
    private int clientId;
    private int productId;
    private int quantity;
    private Double price;

    public Order() {
    }

    public Order(int id, int clientId, int productId, int quantity, Double price) {
        this.id = id;
        this.clientId = clientId;
        this.productId = productId;
        this.quantity = quantity;
        this.price = price;
    }

    public Order(int clientId, int productId, int quantity, Double price) {
        this.clientId = clientId;
        this.productId = productId;
        this.quantity = quantity;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getClientId() {
        return clientId;
    }

    public void setClientId(int clientId) {
        this.clientId = clientId;
    }

    public int getProductId() {
        return productId;
    }

    public void setProductId(int productId) {
        this.productId = productId;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }
}
