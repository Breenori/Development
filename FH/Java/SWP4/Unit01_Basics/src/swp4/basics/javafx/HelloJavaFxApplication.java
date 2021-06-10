package swp4.basics.javafx;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class HelloJavaFxApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        Label label = new Label("Hello JavaFX!");
        StackPane root = new StackPane();
        root.getChildren().add(label);
        Scene scene = new Scene(root, 500, 100);
        primaryStage.setTitle("Hello, JavaFX!");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
