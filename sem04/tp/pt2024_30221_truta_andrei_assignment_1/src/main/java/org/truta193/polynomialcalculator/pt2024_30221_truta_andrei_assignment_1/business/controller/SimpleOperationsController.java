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

public class SimpleOperationsController {
    private final OperationService operationService;
    private final PolynomialInputValidator polynomialInputValidator;
    private final PolynomialParser polynomialParser;

    private BooleanProperty isFirstPolynomialValid = new SimpleBooleanProperty(false);
    private BooleanProperty isSecondPolynomialValid = new SimpleBooleanProperty(false);

    private BooleanProperty isInputValid = new SimpleBooleanProperty(false);

    @FXML
    public Label firstPolynomialLabel;

    @FXML
    public TextField firstPolynomialInput;

    @FXML
    public Label secondPolynomialLabel;

    @FXML
    public TextField secondPolynomialInput;

    @FXML
    public Button addButton;

    @FXML
    public Button subtractButton;

    @FXML
    public Button multiplyButton;

    @FXML
    public Button divideButton;

    @FXML
    public Label resultLabel;

    @FXML
    public TextField resultField;

    @FXML
    public Label secondPolynomialError;

    @FXML
    public Label firstPolynomialError;


    public SimpleOperationsController(
            OperationService operationService,
            PolynomialInputValidator polynomialInputValidator,
            PolynomialParser polynomialParser
    ) {
        this.operationService = operationService;
        this.polynomialInputValidator = polynomialInputValidator;
        this.polynomialParser = polynomialParser;
    }

    public final Boolean getFirstPolynomialValid() {
        return isFirstPolynomialValid.get();
    }

    public final void setFirstPolynomialValid(Boolean value) {
        isFirstPolynomialValid.set(value);
        setInputValid(getFirstPolynomialValid() && getSecondPolynomialValid());
    }

    public final BooleanProperty firstPolynomialValidProperty() {
        return this.isFirstPolynomialValid;
    }

    public final Boolean getSecondPolynomialValid() {
        return isSecondPolynomialValid.get();
    }

    public final void setSecondPolynomialValid(Boolean value) {
        isSecondPolynomialValid.set(value);
        setInputValid(getFirstPolynomialValid() && getSecondPolynomialValid());
    }

    public final BooleanProperty secondPolynomialValidProperty() {
        return this.isSecondPolynomialValid;
    }

    public final Boolean getInputValid() {
        return isInputValid.get();
    }

    public final void setInputValid(Boolean value) {
        isInputValid.set(value);
    }

    public final BooleanProperty inputValidProperty() {
        return this.isInputValid;
    }

    @FXML
    public void onFirstPolynomialInputChanged() {
        String input = firstPolynomialInput.getText();
        setFirstPolynomialValid(polynomialInputValidator.validateInput(input));
    }

    @FXML
    public void onSecondPolynomialInputChanged() {
        String input = secondPolynomialInput.getText();
        setSecondPolynomialValid(polynomialInputValidator.validateInput(input));
    }

    @FXML
    public void onAddButtonClick() {
        String firstInput = firstPolynomialInput.getText();
        String secondInput = secondPolynomialInput.getText();
        Polynomial firstPolynomial = polynomialParser.parseString(firstInput);
        Polynomial secondPolynomial = polynomialParser.parseString(secondInput);
        resultField.setText(operationService.addPolynomials(firstPolynomial, secondPolynomial).toString());
    }

    @FXML
    public void onSubtractButtonClick() {
        String firstInput = firstPolynomialInput.getText();
        String secondInput = secondPolynomialInput.getText();
        Polynomial firstPolynomial = polynomialParser.parseString(firstInput);
        Polynomial secondPolynomial = polynomialParser.parseString(secondInput);
        resultField.setText(operationService.subtractPolynomials(firstPolynomial, secondPolynomial).toString());
    }

    @FXML
    public void onMultiplyButtonClick() {
        String firstInput = firstPolynomialInput.getText();
        String secondInput = secondPolynomialInput.getText();
        Polynomial firstPolynomial = polynomialParser.parseString(firstInput);
        Polynomial secondPolynomial = polynomialParser.parseString(secondInput);
        resultField.setText(operationService.multiplyPolynomials(firstPolynomial, secondPolynomial).toString());
    }

    @FXML
    public void onDivideButtonClick() {
        String firstInput = firstPolynomialInput.getText();
        String secondInput = secondPolynomialInput.getText();
        Polynomial firstPolynomial = polynomialParser.parseString(firstInput);
        Polynomial secondPolynomial = polynomialParser.parseString(secondInput);
        try {
            var result = operationService.dividePolynomials(firstPolynomial, secondPolynomial);
            resultField.setText(result.getKey() + " rem: " + result.getValue());
        } catch (IllegalArgumentException | NullPointerException e) {
            resultField.setText("Error");
        }
    }
}
