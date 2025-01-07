module org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3 {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.graphics;

    requires java.sql;
    requires org.xerial.sqlitejdbc;
    requires java.desktop;

    opens org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3 to javafx.fxml;
    exports org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3;
    opens org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.controller to javafx.fxml;
    opens org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata to javafx.base;
}