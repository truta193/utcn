package org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator;

public class PolynomialInputValidator {
    public boolean validateInput(String input) {
        String trimmedInput = input.trim().replaceAll("\\s+", "");
        if (trimmedInput.isEmpty()) {
            return false;
        }

        String[] monomials = trimmedInput.split("(?=[+-])");

        for (String monomial : monomials) {
            monomial = monomial.replaceAll("\\+", "");
            if (!isMonomialValid(monomial)) {
                return false;
            }
        }

        return true;
    }

    public Boolean isMonomialValid(String monomial) {
        System.out.println(monomial);
        if (monomial.isEmpty()) {
            return false;
        }
        if (monomial.equals("-"))
            return false;

        return monomial.matches("([+-]?\\d*)(x(\\^\\d+)?)?");
    }
}
