package org.truta193.age_calculator_ocsf2.server;

import org.truta193.age_calculator_ocsf2.model.Person;

import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.function.Consumer;

public class ConcreteServer extends AbstractServer {
    private Consumer<String> messageCallback;

    public ConcreteServer(int port) {
        super(port);
    }

    public void setMessageCallback(Consumer<String> callback) {
        this.messageCallback = callback;
    }

    @Override
    protected void clientConnected(ConnectionToClient client) {
        messageCallback.accept("[INFO] Client connected: " + client.toString());
    }

    @Override
    protected void listeningException(Throwable exception) {
        messageCallback.accept("[ERROR] Listening exception: " + exception.getMessage());
    }

    @Override
    protected void serverStarted() {
        messageCallback.accept("[INFO] Server started");

    }

    @Override
    protected void serverStopped() {
        //this.close();
        messageCallback.accept("[INFO] Server stopped");
    }

    @Override
    protected void serverClosed() {
        messageCallback.accept("[INFO] Server closed");

    }

    @Override
    protected void handleMessageFromClient(Object msg, ConnectionToClient client) {
        String response;
        String dateStr = (String) msg;
        messageCallback.accept("[INFO] [" + client.toString() + "] Received: " + dateStr);
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
            LocalDate birthDate = LocalDate.parse(dateStr, formatter);

            if (birthDate.isAfter(LocalDate.now())) {
                response = "[ERROR] Date cannot be in the future.";
            } else {
                Person person = new Person(birthDate);
                int age = person.Age();
                response = "Age: " + age;
            }
        } catch (DateTimeParseException e) {
            response = "[ERROR] Invalid date format. Please use MM/dd/yyyy.";
        }

        try {
            messageCallback.accept("[INFO] Sending: " + response);
            client.sendToClient(response);
        } catch (IOException e) {
            messageCallback.accept("[ERROR] Error sending response to client: " + e.getMessage());
        }
    }

    @Override
    synchronized protected void clientDisconnected(ConnectionToClient client) {
        messageCallback.accept("[INFO] Client disconnected: " + client.toString());
    }

    @Override
    synchronized protected void clientException(ConnectionToClient client, Throwable exception) {
        messageCallback.accept("[INFO] Client disconnected: " + client.toString());
    }
}
