package swp4.basics.javafx.gol;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class GameOfLifeApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        GameOfLifeBoard board = new GameOfLifeBoard(48,27);
        Scene scene = new Scene(board, 500, 500);
        board.initialize();
        primaryStage.setTitle("Game of Life");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
