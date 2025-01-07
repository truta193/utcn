package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service.FileService;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.FormValidator;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.controller.ParametersController;

import java.io.IOException;

public class AppEntryPoint extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        //ParametersController parametersController = new ParametersController();
        FormValidator formValidator = new FormValidator();
        FileService fileService = new FileService();

        FXMLLoader fxmlLoader = new FXMLLoader(AppEntryPoint.class.getResource("parameters-view.fxml"));
        fxmlLoader.setControllerFactory((Class<?> controllerClass) -> {
            if (controllerClass == ParametersController.class) {
                return new ParametersController(formValidator, fileService);
            } else {
                try {
                    return controllerClass.getDeclaredConstructor().newInstance();
                } catch (Exception e) {
                    throw new RuntimeException("Failed to create controller", e);
                }
            }
        });

        Scene scene = new Scene(fxmlLoader.load(), 320, 360);
        stage.setTitle("Parameters");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}