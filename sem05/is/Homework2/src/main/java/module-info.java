module org.truta193.age_calculator_ocsf2 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.kordamp.bootstrapfx.core;

    opens org.truta193.age_calculator_ocsf2 to javafx.fxml;
    exports org.truta193.age_calculator_ocsf2;
}