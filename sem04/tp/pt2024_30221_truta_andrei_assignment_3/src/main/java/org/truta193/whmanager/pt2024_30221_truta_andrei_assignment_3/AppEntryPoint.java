package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller.BillController;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller.ClientController;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller.OrderController;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller.ProductController;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.Database;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.BillRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.ClientRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.OrderRepository;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository.ProductRepository;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

/**
 * Entry point for the application.
 * Launches the JavaFX application and initializes necessary repositories and controllers.
 */
public class AppEntryPoint extends Application {

    /**
     * Start method to initialize the JavaFX application.
     *
     * @param stage The primary stage for the application.
     * @throws IOException If an error occurs while loading the FXML file.
     */
    @Override
    public void start(Stage stage) throws IOException {
        ClientRepository clientRepository = new ClientRepository();
        ProductRepository productRepository = new ProductRepository();
        BillRepository billRepository = new BillRepository();
        OrderRepository orderRepository = new OrderRepository(billRepository);

        FXMLLoader fxmlLoader = new FXMLLoader(AppEntryPoint.class.getResource("main-view.fxml"));
        fxmlLoader.setControllerFactory((Class<?> controllerClass) -> {
            if (controllerClass == ClientController.class) {
                return new ClientController(clientRepository);
            } else if (controllerClass == ProductController.class) {
                return new ProductController(productRepository);
            } else if (controllerClass == OrderController.class) {
                return new OrderController(orderRepository, clientRepository, productRepository);
            } else if (controllerClass == BillController.class) {
                return new BillController(billRepository);
            } else {
                try {
                    return controllerClass.getDeclaredConstructor().newInstance();
                } catch (Exception e) {
                    throw new RuntimeException("Failed to create controller", e);
                }
            }
        });

        Scene scene = new Scene(fxmlLoader.load(), 720, 480);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    /**
     * Main method to launch the application.
     *
     * @param args The command-line arguments.
     */
    public static void main(String[] args) {
        try {
            Class.forName("org.sqlite.JDBC");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        Properties prop = new Properties();
        String fileName = "src/app.config";
        try (FileInputStream fis = new FileInputStream(fileName)) {
            prop.load(fis);
        } catch (IOException ex) {
            ex.printStackTrace();
        }

        String dbUrl = prop.getProperty("db.url");
        Database.initDatabase(dbUrl);

        launch();
    }
}