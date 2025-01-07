package org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service;

import javafx.util.Pair;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialMapValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import java.util.Collections;
import java.util.List;
import java.util.TreeMap;

public class OperationService {

    private final PolynomialMapValidator polynomialMapValidator;

    public OperationService(PolynomialMapValidator polynomialMapValidator) {
        if (polynomialMapValidator == null) {
            throw new IllegalArgumentException("PolynomialMapValidator cannot be null");
        }

        this.polynomialMapValidator = polynomialMapValidator;
    }

    public Polynomial addPolynomials(Polynomial p1, Polynomial p2) {
        if (p1 == null || p2 == null) {
            throw new IllegalArgumentException("Polynomials cannot be null");
        }

        Polynomial result = new Polynomial();

        for (int degree : p1.getPolynomial().keySet()) {
            result.addMonomial(degree, p1.getPolynomial().get(degree));
        }

        for (int degree : p2.getPolynomial().keySet()) {
            result.addMonomial(degree, p2.getPolynomial().get(degree));
        }

        polynomialMapValidator.validatePolynomial(result);

        return result;
    }

    public Polynomial subtractPolynomials(Polynomial p1, Polynomial p2) {
        if (p1 == null || p2 == null) {
            throw new IllegalArgumentException("Polynomials cannot be null");
        }

        Polynomial result = new Polynomial();

        for (int degree : p1.getPolynomial().keySet()) {
            result.addMonomial(degree, p1.getPolynomial().get(degree));
        }

        for (int degree : p2.getPolynomial().keySet()) {
            result.addMonomial(degree, -p2.getPolynomial().get(degree));
        }

        polynomialMapValidator.validatePolynomial(result);

        return result;
    }

    public Polynomial multiplyPolynomials(Polynomial p1, Polynomial p2) {
        if (p1 == null || p2 == null) {
            throw new IllegalArgumentException("Polynomials cannot be null");
        }

        Polynomial result = new Polynomial();

        for (int degree1 : p1.getPolynomial().keySet()) {
            for (int degree2 : p2.getPolynomial().keySet()) {
                int degree = degree1 + degree2;
                double coefficient = p1.getPolynomial().get(degree1) * p2.getPolynomial().get(degree2);
                result.addMonomial(degree, coefficient);
            }
        }

        polynomialMapValidator.validatePolynomial(result);

        return result;
    }

    public Pair<Polynomial, Polynomial> dividePolynomials(Polynomial dividend, Polynomial divisor) {
        if (dividend == null || divisor == null) {
            throw new IllegalArgumentException("Polynomials cannot be null");
        }

        polynomialMapValidator.validatePolynomial(divisor);
        Polynomial quotient = new Polynomial();
        Polynomial remainder = new Polynomial();

        Polynomial dividendCopy = new Polynomial();
        dividendCopy.setPolynomial(dividend.getPolynomial());

        int dividendDegree = dividendCopy.getDegree();
        int divisorDegree = divisor.getDegree();

        if (dividendDegree < divisorDegree) {
            quotient.addMonomial(0, 0.0);
            return new Pair<>(quotient, dividend);
        }

        if (dividendDegree == divisorDegree) {
            double currentCoefficient =
                    dividendCopy.getPolynomial().get(dividendDegree) / divisor.getPolynomial().get(divisorDegree);
            quotient.addMonomial(0, currentCoefficient);
            return new Pair<>(quotient, remainder);
        }

        while (dividendDegree >= divisorDegree && dividendDegree != 0) {
            int currentDegree = dividendDegree - divisorDegree;
            double currentCoefficient =
                    dividendCopy.getPolynomial().get(dividendDegree) / divisor.getPolynomial().get(divisorDegree);

            quotient.addMonomial(currentDegree, currentCoefficient);

            Polynomial temp = new Polynomial();
            temp.addMonomial(currentDegree, currentCoefficient);
            temp = multiplyPolynomials(temp, divisor);

            dividendCopy = subtractPolynomials(dividendCopy, temp);
            dividendDegree = dividendCopy.getDegree();
        }

        remainder.setPolynomial(dividendCopy.getPolynomial());
        polynomialMapValidator.validatePolynomial(quotient);
        polynomialMapValidator.validatePolynomial(remainder);
        return new Pair<>(quotient, remainder);
    }

    public Polynomial integratePolynomial(Polynomial p1) {
        if (p1 == null) {
            throw new IllegalArgumentException("Polynomials cannot be null");
        }
        Polynomial result = new Polynomial();
        TreeMap<Integer, Double> polynomial = new TreeMap<>(p1.getPolynomial());

        for (int degree : polynomial.descendingKeySet()) {
            int newDegree = degree + 1;
            double newCoefficient = p1.getPolynomial().get(degree) / newDegree;
            result.addMonomial(newDegree, newCoefficient);
        }

        polynomialMapValidator.validatePolynomial(result);

        return result;
    }

    public Polynomial derivatePolynomial(Polynomial p1) {
        if (p1 == null) {
            throw new IllegalArgumentException("Polynomials cannot be null");
        }

        Polynomial result = new Polynomial();
        TreeMap<Integer, Double> polynomial = new TreeMap<>(p1.getPolynomial());
        List<Integer> reversedKeys = new java.util.ArrayList<>(polynomial.descendingKeySet().stream().toList());
        Collections.reverse(reversedKeys);

        for (int degree : reversedKeys) {
            if (degree != 0) {
                int newDegree = degree - 1;
                double newCoefficient = degree * p1.getPolynomial().get(degree);
                result.addMonomial(newDegree, newCoefficient);
            }
        }

        try {
            polynomialMapValidator.validatePolynomial(result);
        } catch (IllegalArgumentException e) {
            result.addMonomial(0, 0.0);
        }

        return result;
    }
}