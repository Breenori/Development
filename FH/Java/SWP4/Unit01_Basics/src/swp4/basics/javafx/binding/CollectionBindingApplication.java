package swp4.basics.javafx.binding;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableMap;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class CollectionBindingApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {

        Map<String, Double> values = new HashMap<>();
        values.put("give you up", 20.0);
        values.put("let you down", 10.0);
        values.put("turn around", 20.0);
        values.put("and desert you", 27.0);
        values.put("make you cry", 13.0);
        values.put("say goodbye", 10.0);
        values.put("hurt you", 10.0);

        ObservableMap<String, Double> dataModel = FXCollections.observableMap(values);

        SimpleBarChart barChart = new SimpleBarChart(dataModel);
        VBox root = new VBox(new Label("Rick Astley would never..."), barChart);
        root.setPadding(new Insets(6));

        Button btnCompute = new Button("Compute");
        btnCompute.setOnAction((action -> {
            for(String key : dataModel.keySet()) {
                dataModel.put(key, new Random().nextInt(100) + 0.0);
            }
        }));
        root.getChildren().add(btnCompute);

        Scene scene = new Scene(root, 300, 270);
        primaryStage.setTitle("Collection Binding");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
