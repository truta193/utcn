package org.truta193.age_calculator_ocsf2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.truta193.age_calculator_ocsf2.client.ConcreteClient;

import java.io.IOException;

public class ClientApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        ConcreteClient concreteClient = new ConcreteClient("192.168.1.8", 12345);

        FXMLLoader fxmlLoader = new FXMLLoader(ClientApplication.class.getResource("client-view.fxml"));
        fxmlLoader.setControllerFactory(controllerClass -> {
            if (controllerClass == ClientController.class) {
                return new ClientController(concreteClient);
            } else {
                try {
                    return controllerClass.getDeclaredConstructor().newInstance();
                } catch (Exception e) {
                    throw new RuntimeException("Failed to create controller", e);
                }
            }
        });

        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
        stage.setTitle("Client Application");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}