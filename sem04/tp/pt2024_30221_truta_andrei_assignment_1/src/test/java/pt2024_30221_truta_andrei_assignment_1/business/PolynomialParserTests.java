package pt2024_30221_truta_andrei_assignment_1.business;

import org.junit.jupiter.api.Test;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.PolynomialParser;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class PolynomialParserTests {
    @Test
    public void HavingParserInstance_WhenStringIsEmpty_ReturnsEmptyPolynomial() {
        PolynomialParser parser = new PolynomialParser();
        String polynomial = "";

        Polynomial result = parser.parseString(polynomial);

        assertEquals(0, result.getPolynomial().size());
    }

    @Test
    public void HavingParserInstance_WhenStringIsX_ReturnsPolynomialWithOneMonomial() {
        PolynomialParser parser = new PolynomialParser();
        String polynomial = "x";

        Polynomial result = parser.parseString(polynomial);

        assertEquals(1, result.getPolynomial().size());
        assertEquals(1, result.getPolynomial().get(1));
    }

    @Test
    public void HavingParserInstance_WhenStringIsValidated_ReturnPolynomial() {
        PolynomialParser parser = new PolynomialParser();
        String polynomial = "x^2 + 2x + 3";

        Polynomial result = parser.parseString(polynomial);

        assertEquals(3, result.getPolynomial().size());
        assertEquals(1, result.getPolynomial().get(2));
        assertEquals(2, result.getPolynomial().get(1));
        assertEquals(3, result.getPolynomial().get(0));
    }
}
