package pt2024_30221_truta_andrei_assignment_1.business.OperationServiceTests;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service.OperationService;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialMapValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import static org.junit.Assert.assertThrows;

public class OperationServiceMultiplyTests {
    @Test
    public void HavingTwoPolynomials_WhenOneIsNull_ThrowsException() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial1 = new Polynomial();
        Polynomial polynomial2 = null;

        assertThrows(IllegalArgumentException.class, () -> operationService.multiplyPolynomials(polynomial1, polynomial2));
    }

    @Test
    public void HavingTwoPolynomials_WhenValid_ReturnsResult() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial1 = new Polynomial();
        polynomial1.addMonomial(1, 1.0);
        Polynomial polynomial2 = new Polynomial();
        polynomial2.addMonomial(1, 1.0);

        Polynomial expected = new Polynomial();
        expected.addMonomial(2, 1.0);

        Polynomial result = operationService.multiplyPolynomials(polynomial1, polynomial2);

        Assertions.assertEquals(expected.toString(), result.toString());
    }

    @Test
    public void HavingTwoPolynomials_WhenOneIsZero_ReturnsZero() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial1 = new Polynomial();
        polynomial1.addMonomial(1, 1.0);
        Polynomial polynomial2 = new Polynomial();
        polynomial2.addMonomial(0, 0.0);

        Polynomial expected = new Polynomial();

        Polynomial result = operationService.multiplyPolynomials(polynomial1, polynomial2);

        Assertions.assertEquals(expected.toString(), result.toString());
    }
}
