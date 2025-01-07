package org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.PolynomialParser;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service.OperationService;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialInputValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator.PolynomialMapValidator;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.controller.ComplexOperationsController;
import org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.controller.SimpleOperationsController;

import java.io.IOException;

public class AppEntryPoint extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        PolynomialMapValidator polynomialMapValidator = new PolynomialMapValidator();
        OperationService operationService = new OperationService(polynomialMapValidator);
        PolynomialInputValidator polynomialInputValidator = new PolynomialInputValidator();
        PolynomialParser polynomialParser = new PolynomialParser();

        FXMLLoader fxmlLoader = new FXMLLoader(AppEntryPoint.class.getResource("HomeView.fxml"));

        fxmlLoader.setControllerFactory((Class<?> controllerClass) -> {
            if (controllerClass == ComplexOperationsController.class) {
                return new ComplexOperationsController(
                        operationService,
                        polynomialInputValidator,
                        polynomialParser);
            } else if (controllerClass == SimpleOperationsController.class) {
                return new SimpleOperationsController(
                        operationService,
                        polynomialInputValidator,
                        polynomialParser);
            } else {
                try {
                    return controllerClass.getDeclaredConstructor().newInstance();
                } catch (Exception e) {
                    throw new RuntimeException("Failed to create controller", e);
                }
            }
        });
        Scene scene = new Scene(fxmlLoader.load(), 300, 450);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}