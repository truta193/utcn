package org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator;

import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import java.util.Map;

public class PolynomialMapValidator {
    public void validatePolynomial(Polynomial polynomial) {
        if (polynomial.getPolynomial().isEmpty()) {
            throw new IllegalArgumentException("Polynomial is empty");
        }

        Map<Integer, Double> polynomialMap = polynomial.getPolynomial();
        polynomialMap.entrySet().removeIf(entry -> entry.getValue().equals(0.0));
    }
}
