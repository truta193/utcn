package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.controller;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service.FileService;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.ParamState;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Server;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Task;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.SimulationManager;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

public class SimulationController implements Initializable {
    @FXML public FlowPane waitingPane;
    @FXML public FlowPane queuePane;

    private final List<VBox> queueBoxes = new ArrayList<>();
    public Label timeLabel;

    SimulationManager simulationManager;
    FileService fileService;
    ParamState paramState;

    public SimulationController(
            ParamState paramState,
            FileService fileService
    ) {
        this.fileService = fileService;
        this.paramState = paramState;
        simulationManager = new SimulationManager(paramState, this, fileService);
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        this.refresh();
        Thread t = new Thread(simulationManager);
        t.start();
    }

    public void refresh() {
        Platform.runLater(() -> {
            waitingPane.getChildren().clear();
            queueBoxes.clear();
            queuePane.getChildren().clear();

            for (Task task : simulationManager.getGeneratedTasks()) {
                Text text = new Text(task.toString());
                text.setText(task.toString());
                waitingPane.getChildren().add(text);
            }

            VBox mainBox = new VBox();
            for (Server server : simulationManager.getScheduler().getServers()) {
                VBox serverBox = new VBox();
                HBox serverTasksBox = new HBox();
                Text serverText = new Text("Queue " + ((Integer)server.getId()));
                serverBox.getChildren().add(serverText);
                for (Task task : server.getTasks()) {
                    Text text = new Text(task.toString());
                    serverTasksBox.getChildren().add(text);
                }
                serverBox.getChildren().add(serverTasksBox);
                queueBoxes.add(serverBox);
            }

            timeLabel.setText("Time: " + (simulationManager.getCurrentTime() - 1) + "/" + paramState.getTimeLimit());
            mainBox.getChildren().addAll(queueBoxes);
            queuePane.getChildren().add(mainBox);
        });
    }
}
