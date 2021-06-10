package swp4.basics.javafx.binding;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class SimpleBindingApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        EmployeeBean employeeBean = new EmployeeBean();
        Label lblFirstName = new Label("Insert First Name");
        Label lblOutput = new Label();

        lblOutput.textProperty().bind(employeeBean.firstNameProperty());

        TextField textField = new TextField();
        employeeBean.firstNameProperty().bind(textField.textProperty());

        VBox root = new VBox(lblFirstName, textField, lblOutput);
        root.setPadding(new Insets(10,10,10,10)); // 10 px distance from outer window
        root.setAlignment(Pos.CENTER);
        Scene scene = new Scene(root, 400, 400);
        primaryStage.setTitle("Simple Binding");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
