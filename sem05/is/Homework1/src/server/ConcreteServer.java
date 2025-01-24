package server;

import model.Person;

import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

public class ConcreteServer extends AbstractServer {

    public ConcreteServer(int port) {
        super(port);
    }

    @Override
    protected void handleMessageFromClient(Object msg, ConnectionToClient client) {
        String response;
        String dateStr = (String) msg;

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
            System.out.println("Sending: " + response);
            client.sendToClient(response);
        } catch (IOException e) {
            System.out.println("[ERROR] Error sending response to client: " + e.getMessage());
        }

    }

    public static void main(String[] args) {
        ConcreteServer server = new ConcreteServer(8080);

        try {
            server.listen();
            System.out.println("Server is listening on port 8080");
        } catch (IOException e) {
            System.out.println("[ERROR] Error starting server: " + e.getMessage());
        }
    }
}
