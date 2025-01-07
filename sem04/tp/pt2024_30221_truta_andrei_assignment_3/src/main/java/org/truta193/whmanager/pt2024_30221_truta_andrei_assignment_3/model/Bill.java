package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model;

/**
 * Represents a bill associated with an order.
 */
public record Bill(int id, int orderId) {
    public Bill(int orderId) {
        this(-1, orderId);
    }
}
