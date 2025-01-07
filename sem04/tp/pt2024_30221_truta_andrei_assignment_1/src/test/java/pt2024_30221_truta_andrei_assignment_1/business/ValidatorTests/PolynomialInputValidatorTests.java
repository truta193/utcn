package pt2024_30221_truta_andrei_assignment_1.business.ValidatorTests;

import org.junit.jupiter.api.Test;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialInputValidator;

import static org.junit.jupiter.api.Assertions.*;

public class PolynomialInputValidatorTests {
    private String polynomial1 = "2x^2 + 3x^3 + 4x^4 + 5x^5";
    private String polynomial2 = "2x - 3x^3 - 4x - 5x^5";
    private String polynomial3 = "    x    +-     56";
    private String polynomial4 = "x^2 + 3x^3 + 4x^4 + 5x^^5";
    private String polynomial5 = "x^2 + 3.x^3 + 4x^4 + 5x^5";
    private String polynomial6 = "x^2 -+  3x^3 + 4x^4 + 5x^5";
    private String polynomial7 = "+-";
    private String polynomial8 = "    ";
    private String polynomial9 = "x2";
    private String polynomial10 = "xx";

    @Test
    public void HavingValidatorInstance_WhenPolynomialIsValidated_ReturnsTrue() {
        PolynomialInputValidator polynomialInputValidator = new PolynomialInputValidator();
        boolean result = polynomialInputValidator.validateInput(polynomial1);
        assertEquals(true, result);
    }

    @Test
    public void HavingValidatorInstance_WhenTestStrings_Assert() {
        PolynomialInputValidator polynomialInputValidator = new PolynomialInputValidator();
        assertTrue(polynomialInputValidator.validateInput(polynomial2));
        assertFalse(polynomialInputValidator.validateInput(polynomial3));
        assertFalse(polynomialInputValidator.validateInput(polynomial4));
        assertFalse(polynomialInputValidator.validateInput(polynomial5));
        assertFalse(polynomialInputValidator.validateInput(polynomial6));
        assertFalse(polynomialInputValidator.validateInput(polynomial7));
        assertFalse(polynomialInputValidator.validateInput(polynomial8));
        assertFalse(polynomialInputValidator.validateInput(polynomial9));
        assertFalse(polynomialInputValidator.validateInput(polynomial10));
    }
}
