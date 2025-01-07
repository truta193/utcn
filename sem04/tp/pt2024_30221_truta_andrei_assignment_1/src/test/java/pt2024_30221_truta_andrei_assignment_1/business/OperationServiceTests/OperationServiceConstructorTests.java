package pt2024_30221_truta_andrei_assignment_1.business.OperationServiceTests;

import org.junit.jupiter.api.Test;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service.OperationService;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialMapValidator;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class OperationServiceConstructorTests {
    @Test
    public void HavingOperationServiceInstance_WhenPolynomialMapValidatorIsNull_ThrowsException() {
        PolynomialMapValidator polynomialMapValidator = null;
        assertThrows(IllegalArgumentException.class, () -> new OperationService(polynomialMapValidator));
    }
}
