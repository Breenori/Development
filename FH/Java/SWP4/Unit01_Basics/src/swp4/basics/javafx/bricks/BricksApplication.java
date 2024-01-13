package swp4.basics.javafx.bricks;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.stage.Stage;


public class BricksApplication extends Application {
    @Override
    public void start(Stage stage) throws Exception {
        BricksGameBoard gameBoard = new BricksGameBoard();
        Scene scene = new Scene(gameBoard, 300, 300, Color.LIGHTBLUE);
        stage.setTitle("Bricks");
        stage.setScene(scene);
        gameBoard.initGameBoard();
        stage.show();

    }
}
