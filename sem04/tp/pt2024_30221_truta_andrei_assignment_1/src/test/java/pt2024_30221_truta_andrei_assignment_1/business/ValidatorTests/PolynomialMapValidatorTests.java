package pt2024_30221_truta_andrei_assignment_1.business.ValidatorTests;

import org.junit.jupiter.api.Test;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialMapValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class PolynomialMapValidatorTests {
    @Test
    public void HavingValidatorInstance_WhenCoefficientIsZero_RemoveMonomial() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();

        Polynomial polynomial = new Polynomial();
        polynomial.addMonomial(1, 0.0);
        polynomial.addMonomial(2, 1.0);

        Polynomial expected = new Polynomial();
        expected.addMonomial(2, 1.0);

        polynomialMapValidator.validatePolynomial(polynomial);

        assertEquals(expected.toString(), polynomial.toString());
    }
}
