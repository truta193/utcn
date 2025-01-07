package pt2024_30221_truta_andrei_assignment_1.business.OperationServiceTests;

import org.junit.jupiter.api.Test;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service.OperationService;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialMapValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

import static org.junit.Assert.assertThrows;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class OperationServiceDivideTests {
    @Test
    public void HavingTwoPolynomials_WhenOneIsNull_ThrowsException() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial1 = new Polynomial();
        Polynomial polynomial2 = null;

        assertThrows(IllegalArgumentException.class, () -> operationService.dividePolynomials(polynomial1, polynomial2));
    }

    @Test
    public void HavingTwoPolynomials_WhenDivisorIsZero_ShowsError() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial1 = new Polynomial();
        polynomial1.addMonomial(1, 1.0);
        Polynomial polynomial2 = new Polynomial();
        polynomial2.addMonomial(0, 0.0);

        assertThrows(NullPointerException.class, () -> operationService.dividePolynomials(polynomial1, polynomial2));
    }

    @Test
    public void HavingTwoPolynomials_WhenDivisorIsBiggerThanDividend_ReturnsZeroWithDividendAsRemainder() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial1 = new Polynomial();
        polynomial1.addMonomial(1, 1.0);
        Polynomial polynomial2 = new Polynomial();
        polynomial2.addMonomial(2, 1.0);

        Polynomial expectedVal = new Polynomial();
        expectedVal.addMonomial(0, 0.0);
        Polynomial expectedRem = new Polynomial();
        expectedRem.addMonomial(1, 1.0);


        var result = operationService.dividePolynomials(polynomial1, polynomial2);

        assertEquals(expectedVal.toString(), result.getKey().toString());
        assertEquals(expectedRem.toString(), result.getValue().toString());
    }

    @Test
    public void HavingTwoPolynomials_WhenDivisorIsEqualToDividend_ReturnsOneWithZeroRemainder() {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);

        Polynomial polynomial1 = new Polynomial();
        polynomial1.addMonomial(1, 1.0);
        Polynomial polynomial2 = new Polynomial();
        polynomial2.addMonomial(1, 1.0);

        Polynomial expectedVal = new Polynomial();
        expectedVal.addMonomial(0, 1.0);
        Polynomial expectedRem = new Polynomial();
        expectedRem.addMonomial(0, 0.0);

        var result = operationService.dividePolynomials(polynomial1, polynomial2);

        assertEquals(expectedVal.toString(), result.getKey().toString());
        assertEquals(expectedRem.toString(), result.getValue().toString());
    }
}
