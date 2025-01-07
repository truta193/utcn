package org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.controller;

import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.PolynomialParser;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service.OperationService;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialInputValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model.Polynomial;

public class ComplexOperationsController {

    private final OperationService operationService;
    private final PolynomialInputValidator polynomialInputValidator;
    private final PolynomialParser polynomialParser;

    private BooleanProperty isPolynomialValid = new SimpleBooleanProperty(false);

    @FXML
    public Label polynomialError;

    @FXML
    public Button integrationButton;

    @FXML
    public Label polynomialLabel;

    @FXML
    public TextField polynomialInput;

    @FXML
    public Button derivationButton;

    @FXML
    public Label resultLabel;

    @FXML
    public TextField resultField;

    public ComplexOperationsController(
            OperationService operationService,
            PolynomialInputValidator polynomialInputValidator,
            PolynomialParser polynomialParser
    ) {
        this.operationService = operationService;
        this.polynomialInputValidator = polynomialInputValidator;
        this.polynomialParser = polynomialParser;
    }

    public final Boolean getPolynomialValid() {
        return isPolynomialValid.get();
    }

    public final void setPolynomialValid(Boolean value) {
        isPolynomialValid.set(value);
    }

    public final BooleanProperty polynomialValidProperty() {
        return this.isPolynomialValid;
    }

    @FXML
    public void onPolynomialInputChanged() {
        String input = polynomialInput.getText();
        setPolynomialValid(polynomialInputValidator.validateInput(input));
    }

    @FXML
    public void onIntegrationButtonClick() {
        String input = polynomialInput.getText();
        Polynomial polynomial = polynomialParser.parseString(input);
        Polynomial result = operationService.integratePolynomial(polynomial);
        resultField.setText(result.toString());
    }

    @FXML
    public void onDerivationButtonClick() {
        String input = polynomialInput.getText();
        Polynomial polynomial = polynomialParser.parseString(input);
        Polynomial result = operationService.derivatePolynomial(polynomial);
        resultField.setText(result.toString());
    }

}
