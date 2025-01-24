package org.truta193.age_calculator_ocsf2;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import org.truta193.age_calculator_ocsf2.client.ConcreteClient;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.regex.Pattern;

public class ClientController {
    @FXML
    private TextArea eventLog;

    @FXML
    private VBox menuContainer;

    private final ConcreteClient client;
    private boolean isConnected = false;

    private static final String IP_PORT_REGEX =
            "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}" +
                    "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9]):" +
                    "(6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5]?[0-9]{1,4})$";

    private static final Pattern IP_PORT_PATTERN = Pattern.compile(IP_PORT_REGEX);

    public ClientController(ConcreteClient client) {
        this.client = client;

        this.client.setMessageCallback(this::logEvent);
        this.client.setDisconnectCallback(this::disconnect);
    }

    @FXML
    private void initialize() {
        updateMenu();
    }

    private void updateMenu() {
        Platform.runLater(() -> {
            menuContainer.getChildren().clear();

            if (isConnected) {
                Button disconnectButton = new Button("Disconnect");
                disconnectButton.setOnAction(event -> disconnectBtn());

                TextField messageField = new TextField();
                messageField.setPromptText("Enter message");

                Button sendButton = new Button("Send");
                sendButton.setOnAction(event -> {
                    String message = messageField.getText();
                    if (!message.isEmpty()) {
                        sendMessage(message);
                        messageField.clear();
                    } else {
                        logEvent("[WARNING] Message cannot be empty.");
                    }
                });

                menuContainer.getChildren().addAll(disconnectButton, messageField, sendButton);
            } else {
                TextField ipPortField = new TextField();
                ipPortField.setPromptText("Ip:Port");

                Button connectButton = new Button("Connect");
                connectButton.setOnAction(event -> connect(ipPortField.getText()));

                menuContainer.getChildren().addAll(ipPortField, connectButton);
            }
        });
    }

    private void logEvent(String message) {
        Platform.runLater(() -> eventLog.appendText(message + "\n"));
    }

    public void connect(String ipPort) {
        if (!IP_PORT_PATTERN.matcher(ipPort).matches()) {
            logEvent("[ERROR] Invalid Ip:Port format. Please use format: 127.0.0.1:12345");
            return;
        }

        logEvent("[INFO] Attempting to connect...");

        Thread connectionThread = new Thread(() -> {
            try {
                String[] parts = ipPort.split(":");
                String ip = parts[0];
                int port = Integer.parseInt(parts[1]);

                client.setHost(ip);
                client.setPort(port);
                client.openConnection();

                Platform.runLater(() -> {
                    isConnected = true;
                    logEvent("[INFO] Connected to server at " + ipPort + ".");
                    updateMenu();
                });
            } catch (Exception e) {
                Platform.runLater(() -> logEvent("[ERROR] Failed to connect: " + e.getMessage()));
            }
        });

        connectionThread.start();

        new Thread(() -> {
            try {
                Thread.sleep(5000);
                if (connectionThread.isAlive()) {
                    connectionThread.interrupt();
                    Platform.runLater(() -> {
                        logEvent("[ERROR] Connection attempt timed out.");
                    });
                }
            } catch (InterruptedException ignored) {
            }
        }).start();
    }

    public void disconnect() {
        logEvent("[INFO] Disconnected from the server.");
        isConnected = false;
        updateMenu();
    }

    public void disconnectBtn() {
        try {
            client.closeConnection();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void sendMessage(String message) {
        if (message.isEmpty()) {
            logEvent("[ERROR] Message cannot be empty.");
            return;
        }

        if (!isValidDate(message)) {
            logEvent("[ERROR] Message is not a valid date in the format dd/MM/yyyy.");
            return;
        }

        logEvent("[INFO] Sending: " + message);
        new Thread(() -> {
            try {
                client.sendToServer(message);
            } catch (Exception e) {
                logEvent("[ERROR] Failed to send message: " + e.getMessage());
            }
        }).start();
    }

    private boolean isValidDate(String date) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        dateFormat.setLenient(false);
        try {
            dateFormat.parse(date);
            return true;
        } catch (ParseException e) {
            return false;
        }
    }
}