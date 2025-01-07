package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.controller;

import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.AppEntryPoint;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.SelectionPolicy;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service.FileService;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.FormValidator;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.ParamState;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service.StatisticsService;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class ParametersController implements Initializable {
    public TextField numberOfServers;
    public TextField numberOfClients;
    public TextField timeLimit;
    public TextField maxProcessingTime;
    public TextField minProcessingTime;
    public TextField maxArrivalTime;
    public TextField minArrivalTime;
    public ComboBox strategySelect;
    public SelectionPolicy selectionPolicy = SelectionPolicy.NONE;
    FormValidator formValidator;
    FileService fileService;
    StatisticsService statisticsService;
    private final BooleanProperty isFormValid = new SimpleBooleanProperty(false);

    public ParametersController(
            FormValidator formValidator,
            FileService fileService
    ) {
        this.formValidator = formValidator;
        this.fileService = fileService;
    }

    public final Boolean getFormValid() {
        return isFormValid.get();
    }

    public final void setFormValid(Boolean value) {
        isFormValid.set(value);
    }

    public final void onFormChange() {
        boolean formValid = formValidator.validateForm(
                numberOfServers.getText(),
                numberOfClients.getText(),
                timeLimit.getText(),
                maxProcessingTime.getText(),
                minProcessingTime.getText(),
                maxArrivalTime.getText(),
                minArrivalTime.getText(),
                selectionPolicy
        );
        isFormValid.set(formValid);
        System.out.println(numberOfServers.getText() +
                numberOfClients.getText() +
                timeLimit.getText() +
                maxProcessingTime.getText() +
                minProcessingTime.getText() + isFormValid.get());
    }

    public final void startSimulation() throws IOException {
        System.out.println(selectionPolicy);
        if (!isFormValid.get()) {
            return;
        }

        FXMLLoader fxmlLoader = new FXMLLoader(AppEntryPoint.class.getResource("simulation-view.fxml"));
        fxmlLoader.setControllerFactory((Class<?> controllerClass) -> {
            if (controllerClass == SimulationController.class) {
                return new SimulationController(new ParamState(
                        Integer.parseInt(numberOfServers.getText()),
                        Integer.parseInt(numberOfClients.getText()),
                        Integer.parseInt(timeLimit.getText()),
                        Integer.parseInt(maxProcessingTime.getText()),
                        Integer.parseInt(minProcessingTime.getText()),
                        Integer.parseInt(maxArrivalTime.getText()),
                        Integer.parseInt(minArrivalTime.getText()),
                        selectionPolicy
                ), fileService);
            } else {
                try {
                    return controllerClass.getDeclaredConstructor().newInstance();
                } catch (Exception e) {
                    throw new RuntimeException("Failed to create controller", e);
                }
            }
        });

        Scene scene = new Scene(fxmlLoader.load(), 1280, 720);
        Stage secondStage = new Stage();
        secondStage.setScene(scene);
        secondStage.show();
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        strategySelect.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
                if (t1 != null) {
                    System.out.println(s + " " + t1);
                    if (t1.equals("Shortest Queue")) {
                        selectionPolicy = SelectionPolicy.SHORTEST_QUEUE;
                    } else {
                        selectionPolicy = SelectionPolicy.SHORTEST_TIME;
                    }
                    onFormChange();
                }
            }
        });
    }
}
