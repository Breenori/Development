package swp4.basics.javafx.task;

import javafx.application.Application;
import javafx.concurrent.Task;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ProgressBar;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class TaskApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        Button btnRun = new Button("Run");
        ProgressBar prgStatus = new ProgressBar();

        final Task<Integer> task = new Task<Integer>() {

            @Override
            protected Integer call() throws Exception {
                int iterations;
                for(iterations=0; iterations < 100; iterations++) {
                    Thread.sleep(100);
                    if(isCancelled()) {
                        updateMessage("Task abgebrochen!");
                        break;
                    }
                    updateProgress(iterations+1, 100);
                }
                return null;
            }
        };

        prgStatus.setPrefWidth(330);
        prgStatus.progressProperty().bind(task.progressProperty());

        btnRun.setPrefWidth(100);
        btnRun.setOnAction(event -> {
            if(task.isRunning()) {
                task.cancel();
                btnRun.setText("Cancelled");
                btnRun.setDisable(true);
            } else {
                btnRun.setText("Stop");
                Thread thread = new Thread(task);
                thread.start();
            }
        });

        VBox root = new VBox(10, prgStatus, btnRun);
        root.setAlignment(Pos.CENTER);

        primaryStage.setScene(new Scene(root, 400, 80));
        primaryStage.show();
    }
}
