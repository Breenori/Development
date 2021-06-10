package swp4.basics.javafx.gol;

import javafx.application.Platform;
import javafx.beans.binding.When;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GameOfLifeBoard extends AnchorPane {
    private final Map<Integer, List<GameOfLifeCell>> cells = new HashMap<>();
    private final int cols;
    private final int rows;

    public GameOfLifeBoard(int cols, int rows) {
        this.cols = cols;
        this.rows = rows;
    }

    public void initialize() {
        for(int col = 0; col < cols; col++) {
            for(int row = 0; row < rows; row++) {
                GameOfLifeCell cell = new GameOfLifeCell();
                cell.setFill(Color.LIGHTGRAY);
                cell.setUserData(new Coordinates(col, row));
                cell.fillProperty().bind(new When(cell.aliveProperty()).then(Color.LEMONCHIFFON).otherwise(Color.LIGHTGRAY));
                cell.setOnMouseClicked(this::mouseClicked);
                cells.computeIfAbsent(row, k -> new ArrayList<>());
                cells.get(row).add(cell);
                getChildren().add(cell);
            }
        }
        resizeContainer(this);
        this.widthProperty().addListener( (o, ov, nv) -> resizeContainer(this));
        this.heightProperty().addListener( (o, ov, nv) -> resizeContainer(this));
    }

    private void mouseClicked(MouseEvent mouseEvent) {
        GameOfLifeCell cell = (GameOfLifeCell) mouseEvent.getSource();
        Coordinates coordinates = (Coordinates)cell.getUserData();
        System.out.println(coordinates);

        Platform.runLater( () -> {
            cell.setAlive(!cell.isAlive()); // ensure that the code is executed on the ui thread
        });
        cell.setAlive(!cell.isAlive());
    }

    public void resizeContainer(AnchorPane pane) {
        for(int col = 0; col < cols; col++) {
            for(int row = 0; row < rows; row++) {
                GameOfLifeCell cell = cells.get(row).get(col);
                cell.setX((pane.getWidth() / cols) * col + 1);
                cell.setY((pane.getHeight() / rows) * row + 1);
                cell.setWidth((pane.getWidth() / cols) - 1);
                cell.setHeight((pane.getHeight() / rows) - 1);
            }
        }
    }

    public class Coordinates {
        int column;
        int row;

        public Coordinates(int column, int row) {
            this.column = column;
            this.row = row;
        }

        @Override
        public String toString() {
            return "Coordinates{" +
                    "row=" + row +
                    ", column=" + column +
                    '}';
        }
    }
}
