package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.validator;

/**
 * Validator class for validating product creation.
 */
public class ProductValidator {
    /**
     * Validates the product creation.
     *
     * @param name
     * @param price
     * @param quantity
     * @return true if the product is valid, false otherwise
     */
    public boolean validateProduct(String name, String price, String quantity) {
        return !name.isEmpty() &&
                !price.isEmpty() &&
                !quantity.isEmpty() &&
                Double.parseDouble(price) > 0 &&
                Integer.parseInt(quantity) > 0;
    }
}
