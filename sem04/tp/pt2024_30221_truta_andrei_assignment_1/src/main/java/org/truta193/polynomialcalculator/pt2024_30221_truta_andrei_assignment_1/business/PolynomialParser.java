package org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business;

import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PolynomialParser {
    public Polynomial parseString(String polynomial) {
        Polynomial result = new Polynomial();

        String polynomialStr = polynomial.replaceAll("\\s+", "");
        Pattern pattern = Pattern.compile("(-?\\d*)(x(\\^\\d+)?)?");
        Matcher matcher = pattern.matcher(polynomialStr);

        while (matcher.find()) {

            if (matcher.group(0).isEmpty() || matcher.group(0) == null) {
                continue;
            }

            String coefficientStr = matcher.group(1);
            String degreeStr = matcher.group(3);

            int coefficient = 1;
            int degree = 0;

            if (coefficientStr != null && !coefficientStr.isEmpty()) {
                if (coefficientStr.equals("-")) {
                    coefficient = -1;
                } else {
                    coefficient = Integer.parseInt(coefficientStr);
                }
            }

            if (degreeStr != null && !degreeStr.isEmpty()) {
                degree = Integer.parseInt(degreeStr.substring(1)); // Removing "^" character
            } else if (matcher.group(0).contains("x")) {
                degree = 1;
            }

            result.addMonomial(degree, coefficient);
        }

        return result;
    }
}