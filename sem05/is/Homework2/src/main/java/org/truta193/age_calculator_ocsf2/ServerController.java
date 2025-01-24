package org.truta193.age_calculator_ocsf2;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.VBox;
import org.truta193.age_calculator_ocsf2.server.ConcreteServer;

public class ServerController {
    @FXML
    private TextArea eventLog;

    @FXML
    private VBox menuContainer;

    private ConcreteServer server;
    private ServerState currentState = ServerState.OFF;

    @FXML
    private void initialize() {
        updateMenu();
    }

    private void updateMenu() {
        Platform.runLater(() -> {
            menuContainer.getChildren().clear();

            switch (currentState) {
                case OFF:
                    Button startServerButton = new Button("Start Server");
                    startServerButton.setOnAction(event -> startServer());
                    menuContainer.getChildren().add(startServerButton);
                    break;

                case ON_NOT_LISTENING:
                    Button startListeningButton = new Button("Start Listening");
                    startListeningButton.setOnAction(event -> startListening());

                    Button stopServerButton = new Button("Stop Server");
                    stopServerButton.setOnAction(event -> stopServer());

                    menuContainer.getChildren().addAll(startListeningButton, stopServerButton);
                    break;

                case ON_LISTENING:
                    Button stopListeningButton = new Button("Stop Listening");
                    stopListeningButton.setOnAction(event -> stopListening());

                    Button stopServerWhileListeningButton = new Button("Stop Server");
                    stopServerWhileListeningButton.setOnAction(event -> stopServer());

                    menuContainer.getChildren().addAll(stopListeningButton, stopServerWhileListeningButton);
                    break;
            }
        });
    }

    private void logEvent(String message) {
        Platform.runLater(() -> eventLog.appendText(message + "\n"));
    }

    private void startServer() {
        logEvent("[INFO] Starting server");
        try {
            server = new ConcreteServer(12345);
            server.setMessageCallback(this::logEvent);

            currentState = ServerState.ON_NOT_LISTENING;
            updateMenu();
        } catch (Exception e) {
            logEvent("[ERROR] Failed to start server: " + e.getMessage());
        }
    }

    private void stopServer() {
        logEvent("[INFO] Stopping server");
        try {
            if (server != null) {
                server.close();
                server = null;
            }
            currentState = ServerState.OFF;
            updateMenu();
        } catch (Exception e) {
            logEvent("[ERROR] Failed to stop server: " + e.getMessage());
        }
    }

    private void startListening() {
        logEvent("[INFO] Starting to listen for connections...");
        try {
            server.listen();
            currentState = ServerState.ON_LISTENING;
            logEvent("[INFO] Listening for client connections.");
            updateMenu();
        } catch (Exception e) {
            logEvent("[ERROR] Failed to start listening: " + e.getMessage());
        }
    }

    private void stopListening() {
        logEvent("[INFO] Stopping listening...");
        try {
            server.stopListening();
            currentState = ServerState.ON_NOT_LISTENING;
            logEvent("[INFO] No longer listening for connections.");
            updateMenu();
        } catch (Exception e) {
            logEvent("[ERROR] Failed to stop listening: " + e.getMessage());
        }
    }

    private enum ServerState {
        OFF, ON_NOT_LISTENING, ON_LISTENING
    }
}
