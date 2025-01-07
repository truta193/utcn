package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Bill;

/**
 * Represents a row in the bill table view.
 */
public class BillEntry {
    public IntegerProperty id;
    public IntegerProperty orderId;

    public BillEntry(Bill bill) {
        this.id = new SimpleIntegerProperty(bill.id());
        this.orderId = new SimpleIntegerProperty(bill.orderId());
    }

    public final IntegerProperty idProperty() {
        return this.id;
    }

    public final IntegerProperty orderIdProperty() {
        return this.orderId;
    }

    public int getId() {
        return id.get();
    }

    public void setId(int id) {
        this.id.set(id);
    }

    public int getOrderId() {
        return orderId.get();
    }

    public void setOrderId(int orderId) {
        this.orderId.set(orderId);
    }
}
