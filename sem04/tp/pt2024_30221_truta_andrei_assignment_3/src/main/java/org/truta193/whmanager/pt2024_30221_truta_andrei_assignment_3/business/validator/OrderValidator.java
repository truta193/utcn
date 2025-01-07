package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.validator;

import javafx.scene.control.*;

/**
 * Validator class for validating order creation.
 */
public class OrderValidator {
    /**
     * Validates the order creation.
     *
     * @param clientTable
     * @param productTable
     * @param quantity
     * @return true if the order is valid, false otherwise
     */
    public boolean validateOrder(TableView clientTable, TableView productTable, String quantity) {
        return clientTable.getSelectionModel().getSelectedItem() != null &&
                productTable.getSelectionModel().getSelectedItem() != null &&
                !quantity.isEmpty() &&
                Integer.parseInt(quantity) > 0;
    }
}
