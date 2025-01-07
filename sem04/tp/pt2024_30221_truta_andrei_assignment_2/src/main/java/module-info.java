module org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_2 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires net.synedra.validatorfx;

    opens org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2 to javafx.fxml;
    exports org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2;
    exports org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business;
    opens org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business to javafx.fxml;
    exports org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model;
    opens org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model to javafx.fxml;
    exports org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.strategy;
    opens org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.strategy to javafx.fxml;
    exports org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.controller;
    opens org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.controller to javafx.fxml;
    exports org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service;
    opens org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service to javafx.fxml;
}