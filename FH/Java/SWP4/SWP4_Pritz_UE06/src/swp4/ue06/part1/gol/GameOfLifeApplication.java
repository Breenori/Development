package swp4.ue06.part1.gol;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;


public class GameOfLifeApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        // create new vbox as root
        VBox vbox = new VBox();

        // create gameOfLIfeBoard with 100x100 grid
        GameOfLifeBoard board = new GameOfLifeBoard(50,50);
        // set min-dimensions to allow shrinking of board on resize
        board.setMinHeight(0);
        board.setMinWidth(0);
        // also allow it to fill the container
        VBox.setVgrow(board, Priority.ALWAYS);
        vbox.getChildren().add(board);

        // Button to make ONE step
        Button btnStep = new Button("Step");
        btnStep.setOnAction(a -> {
            // board::step makes changes to the UI --> Platform.runLater required!
            Platform.runLater(board::step);
        });

        // Run and stopButton to allow autonomous steps
        Button btnRun = new Button("Run");
        Button btnStop = new Button("Stop");
        btnStop.setDisable(true);
        btnRun.setOnAction(a -> {
            // upon running, start the Thread and disable the run button (and activate the stop button)
            board.startStepping();
            btnRun.setDisable(true);
            btnStop.setDisable(false);
        });
        btnStop.setOnAction(a -> {
            // stop the thread and reverse button disabling
            board.stopStepping();
            btnRun.setDisable(false);
            btnStop.setDisable(true);
        });

        // button to reset the state to the point before pressing the run button
        Button btnReset = new Button("Reset");
        btnReset.setOnAction(a -> {
            Platform.runLater(() -> board.reset());
        });

        // sets all cells to a dead state
        Button btnClear = new Button("Clear");
        btnClear.setOnAction(a -> {
            Platform.runLater(() -> board.clear());
        });

        // saves the current board
        Button btnSave = new Button("Save");
        btnSave.setOnAction(a -> {
            FileChooser fc = new FileChooser();
            FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter("GOL Files (*.gol)","*.gol");
            fc.getExtensionFilters().add(extFilter);
            fc.setTitle("Please save file destination");

            File file = fc.showSaveDialog(primaryStage);
            if(file != null) {
                board.save(file);
            }
        });

        // restores state from file
        Button btnOpen = new Button("Open");
        btnOpen.setOnAction(a -> {
            FileChooser fc = new FileChooser();
            FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter("GOL Files (*.gol)","*.gol");
            fc.getExtensionFilters().add(extFilter);
            fc.setTitle("Please pick savegame");

            File file = fc.showOpenDialog(primaryStage);
            if(file != null) {
                Platform.runLater(() -> {
                    if(!board.restore(file)) {
                        Alert alert = new Alert(Alert.AlertType.ERROR, "File couldn't be read.\nMake sure the file is well formed.", ButtonType.OK);
                        alert.setHeaderText("Error reading file");
                        alert.showAndWait();
                    }
                });
            }
        });


        // place all buttons in an hbox beneath board
        HBox hbox = new HBox();
        hbox.setSpacing(7);
        hbox.getChildren().add(btnStep);
        hbox.getChildren().add(btnRun);
        hbox.getChildren().add(btnStop);
        hbox.getChildren().add(btnReset);
        hbox.getChildren().add(btnClear);
        hbox.getChildren().add(btnSave);
        hbox.getChildren().add(btnOpen);
        vbox.getChildren().add(hbox);

        // initialize the scene, board and stage and display the stage
        Scene scene = new Scene(vbox, 500, 500);
        board.initialize();
        primaryStage.setMinHeight(350);
        primaryStage.setMinWidth(350);
        primaryStage.setTitle("Game of Life");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
