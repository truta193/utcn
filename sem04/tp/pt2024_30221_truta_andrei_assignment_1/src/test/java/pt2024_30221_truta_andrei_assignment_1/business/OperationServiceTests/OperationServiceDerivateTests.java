package pt2024_30221_truta_andrei_assignment_1.business.OperationServiceTests;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service.OperationService;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialMapValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class OperationServiceDerivateTests {
    @Test
    public void HavingAPolynomial_WhenNull_ThrowsException() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial = null;

        assertThrows(IllegalArgumentException.class, () -> operationService.derivatePolynomial(polynomial));
    }

    @Test
    public void HavingAPolynomial_WhenValid_ReturnsResult() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial = new Polynomial();
        polynomial.addMonomial(1, 1.0);
        polynomial.addMonomial(2, 2.0);
        polynomial.addMonomial(3, 3.0);

        Polynomial expected = new Polynomial();
        expected.addMonomial(0, 1.0);
        expected.addMonomial(1, 4.0);
        expected.addMonomial(2, 9.0);

        Polynomial result = operationService.derivatePolynomial(polynomial);

        Assertions.assertEquals(expected.toString(), result.toString());
    }

    @Test
    public void HavingAPolynomial_WhenConstant_ReturnsZero() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial = new Polynomial();
        polynomial.addMonomial(0, 1.0);

        Polynomial expected = new Polynomial();
        expected.addMonomial(0, 0.0);

        Polynomial result = operationService.derivatePolynomial(polynomial);

        Assertions.assertEquals(expected.toString(), result.toString());
    }

}
