package client;

import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ConcreteClient extends AbstractClient {

    public ConcreteClient(String host, int port) {
        super(host, port);
    }

    @Override
    protected void handleMessageFromServer(Object msg) {
        System.out.println("[RESPONSE] " + (String)msg);
    }

    public static void main(String[] args) {
        ConcreteClient concreteClient = new ConcreteClient("10.132.98.174", 8080); //192.168.1.5
        String leapYearRegex = "^(?:(?:31(\\/|-|\\.)(?:0?[13578]|1[02]))\\1|(?:(?:29|30)(\\/|-|\\.)(?:0?[1,3-9]|1[0-2])\\2))(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$|^(?:29(\\/|-|\\.)0?2\\3(?:(?:(?:1[6-9]|[2-9]\\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\\d|2[0-8])(\\/|-|\\.)(?:(?:0?[1-9])|(?:1[0-2]))\\4(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$";
        Pattern pattern = Pattern.compile(leapYearRegex);

        try {
            concreteClient.openConnection();

            Scanner scanner = new Scanner(System.in);
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

            System.out.println("Client is running. Enter a date (dd/MM/yyyy) or type 'exit' to quit");

            while (true) {
                Thread.sleep(1000);
                System.out.print("Enter date (or 'exit' to quit): ");
                String input = scanner.nextLine();

                if (input.equalsIgnoreCase("exit")) {
                    System.out.println("Exiting client...");
                    break;
                }

                Matcher matcher = pattern.matcher(input);
                if (!matcher.matches()) {
                    System.out.println("[ERROR] Invalid date format or invalid date. Please ensure the format is dd/MM/yyyy and the date is valid.");
                    continue;
                }

                try {
                    LocalDate parsedDate = LocalDate.parse(input, formatter);

                    concreteClient.sendToServer(input);
                } catch (DateTimeParseException e) {
                    System.out.println("[ERROR] Invalid date format. Please enter a date in the format dd/MM/yyyy.");
                }
            }
        } catch (IOException e) {
            System.out.println("[ERROR] Unable to connect to the server.");
        } catch (InterruptedException e) {
            System.out.println("[ERROR] Failed to sleep");
            throw new RuntimeException(e);
        } finally {
            try {
                concreteClient.closeConnection();
            } catch (IOException e) {
                System.out.println("[ERROR] Unable to close the connection.");
            }
        }
    }
}
