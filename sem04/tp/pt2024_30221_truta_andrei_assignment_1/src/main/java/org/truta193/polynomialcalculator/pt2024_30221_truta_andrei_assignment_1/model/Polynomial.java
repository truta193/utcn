package org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model;
import java.util.Collections;
import java.util.Map;
import java.util.TreeMap;

import static java.lang.Math.abs;

public class Polynomial {
    private Map<Integer, Double> polynomial = new TreeMap<>();

    public Map<Integer, Double> getPolynomial() {
        return polynomial;
    }

    public void setPolynomial(Map<Integer, Double> polynomial) {
        this.polynomial = polynomial;
    }

    public void addMonomial(int degree, double coefficient) {
        if (polynomial.containsKey(degree)) {
            polynomial.put(degree, polynomial.get(degree) + coefficient);
        } else {
            polynomial.put(degree, coefficient);
        }
    }

    public int getDegree() {
        return polynomial.isEmpty() ? 0 : Collections.max(polynomial.keySet());
    }

    @Override
    public String toString() {
        TreeMap<Integer, Double> polynomial = new TreeMap<>(this.polynomial);
        StringBuilder result = new StringBuilder();
        boolean isFirstTerm = true;

        for (int degree : polynomial.descendingKeySet()) {
            Double coefficient = polynomial.get(degree);

            if (coefficient < 0) {
                if (isFirstTerm) {
                    result.append("-");
                } else {
                    result.append(" -");
                }
            } else {
                if (!isFirstTerm) {
                    result.append(" +");
                }
            }

            if (!(abs(abs(coefficient) - 1.0) < Math.ulp(1.0)) || degree == 0) {
                int truncatedCoefficient = (int) Math.floor(abs(coefficient));
                if (abs(abs(coefficient) - truncatedCoefficient) < Math.ulp(1.0)){
                    result.append(truncatedCoefficient);
                } else {
                    result.append(String.format("%.2f", abs(coefficient)));
                }
            }

            if (degree == 0) {
                result.append("");
            } else if (degree == 1) {
                result.append("x");
            } else {
                result.append("x^").append(degree);
            }

            isFirstTerm = false;
        }

        if (isFirstTerm) {
            result.append("0");
        }
        return result.toString();
    }
}
