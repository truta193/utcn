module org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;

    opens org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1 to javafx.fxml;
    exports org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1;
    exports org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model;
    opens org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.model to javafx.fxml;
    exports org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator;
    opens org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.validator to javafx.fxml;
    exports org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.controller;
    opens org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.controller to javafx.fxml;
    exports org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service;
    opens org.truta193.polynomialcalculator.pt2024_30221_truta_andrei_assignment_1.business.service to javafx.fxml;
}