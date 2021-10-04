package swp4.ue06.part1.gol;

import javafx.application.Platform;
import javafx.beans.binding.When;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;


import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class GameOfLifeBoard extends AnchorPane {
    private final Map<Integer, List<GameOfLifeCell>> cells = new HashMap<>();
    private final Map<Integer, List<GameOfLifeCell>> backupCells = new HashMap<>();
    private final int cols;
    private final int rows;
    private boolean running = false;

    public GameOfLifeBoard(int cols, int rows) {
        this.cols = cols;
        this.rows = rows;
    }

    // deep copy the cells to avoid changing the same cells (references!)
    private void deepCopyCells(Map<Integer, List<GameOfLifeCell>> src, Map<Integer, List<GameOfLifeCell>> dst) {
        for(int col = 0; col < cols; col++) {
            for (int row = 0; row < rows; row++) {
                // create a new cell to avoid referencing the old one and copy the alive status
                GameOfLifeCell cell = new GameOfLifeCell();
                if(src.get(row).get(col).isAlive()) {
                    cell.setAlive(true);
                }

                // finally copy the cell to the new map
                dst.computeIfAbsent(row, k -> new ArrayList<>());
                dst.get(row).add(cell);
            }
        }
    }

    public void initialize() {
        // iterate through all positions
        for(int col = 0; col < cols; col++) {
            for(int row = 0; row < rows; row++) {
                // create cell for each position and set its color
                GameOfLifeCell cell = new GameOfLifeCell();
                cell.setFill(Color.LIGHTGRAY);

                // bind the fillProperty to the cells alive status and color it accordingly
                cell.fillProperty().bind(new When(cell.aliveProperty()).then(Color.VIOLET).otherwise(Color.LIGHTGRAY));
                // on mouseclick, call the mouseClicked function
                cell.setOnMouseClicked(this::mouseClicked);

                // set the cells userdata to easily read the coordinates later
                cell.setUserData(new Coordinates(col, row));

                // add the cells to a map and to the board as JavaFX components
                cells.computeIfAbsent(row, k -> new ArrayList<>());
                cells.get(row).add(cell);
                getChildren().add(cell);
            }
        }
        // initially "resize" the container so the cells width is determined correctly
        resizeContainer(this);
        // additionally bind a listener to widthproperty, so the resizing the window triggers the function
        this.widthProperty().addListener( (o, ov, nv) -> resizeContainer(this));
        this.heightProperty().addListener( (o, ov, nv) -> resizeContainer(this));
    }

    public void reset() {
        // delegate
        restoreFromMap(backupCells);
    }

    private void restoreFromMap(Map<Integer, List<GameOfLifeCell>> restoreCells) {
        // restore cells alive status using the given map
        for(int col = 0; col < cols; col++) {
            for(int row = 0; row < rows; row++) {
                cells.get(row).get(col).setAlive(restoreCells.get(row).get(col).isAlive());
            }
        }
    }

    public void clear() {
        // iterate over the map and set every cell as dead
        for(int col = 0; col < cols; col++) {
            for(int row = 0; row < rows; row++) {
                cells.get(row).get(col).setAlive(false);
            }
        }
    }

    public void save(File file) {
        // upon saving the current status, iterate over the map
        try (PrintWriter writer = new PrintWriter(file)) {
            for (int row = 0; row < rows; row++) {
                for(int col = 0; col < cols; col++) {
                    if(col > 0) {
                        // whitespace as delimiter
                        writer.print(" ");
                    }
                    // write the cells as zeroes and ones
                    writer.print(cells.get(row).get(col).isAlive() ? 1 : 0);
                }
                writer.print("\n");
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public boolean restore(File file) {
        // keep track of the read fields and their amount
        int readFields = 0;
        Map<Integer, List<GameOfLifeCell>> readCells = new HashMap<>();

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            // read the entire file line by line
            String s = "";
            int row = 0;
            while((s = br.readLine()) != null) {
                // split the line using whitespaces and create a new list inside the map
                String[] valList = s.split("\s");
                readCells.put(row, new ArrayList<>());
                // afterward, check if 0 or 1 has been read and accordingly add dead or alive cells for each value
                for(String val : valList) {
                    GameOfLifeCell cell = new GameOfLifeCell();
                    if(val.equals("0")) {
                        readCells.get(row).add(cell);
                    } else if(val.equals("1")) {
                        cell.setAlive(true);
                        readCells.get(row).add(cell);
                    }
                }
                readFields += readCells.get(row).size();
                row++;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // the amount of read cells needs to match the space in the grid
        if(readFields == rows*cols) {
            restoreFromMap(readCells);
            return true;
        } else {
            return false;
        }
    }

    private void mouseClicked(MouseEvent mouseEvent) {
        // upon mouseclick, find the right cell and print its coordinates
        GameOfLifeCell cell = (GameOfLifeCell) mouseEvent.getSource();
        Coordinates coordinates = (Coordinates)cell.getUserData();
        System.out.println(coordinates);

        // then, toggle its alive status
        Platform.runLater( () -> {
            cell.setAlive(!cell.isAlive()); // ensure that the code is executed on the ui thread
        });
    }

    private void resizeContainer(AnchorPane pane) {
        for(int col = 0; col < cols; col++) {
            for(int row = 0; row < rows; row++) {
                // calculate new positions and sizes for each cell upon resizing
                GameOfLifeCell cell = cells.get(row).get(col);
                cell.setX((pane.getWidth() / cols) * col + 1);
                cell.setY((pane.getHeight() / rows) * row + 1);
                cell.setWidth((pane.getWidth() / cols-1) - 1);
                cell.setHeight((pane.getHeight() / rows-1) - 1);
            }
        }
    }

    public void step() {
        // make a copy of the old cells, to avoid affecting the result with made changes
        Map<Integer, List<GameOfLifeCell>> oldCells = new HashMap<>();
        deepCopyCells(cells,oldCells);

        for(int col = 0; col < cols; col++) {
            for(int row = 0; row < rows; row++) {
                // get the status for each cell. -1 if they die, 0 if they continue to live, 1 if they come alive.
                // set the property accordingly
                if(getState(row, col, oldCells) == -1) {
                    cells.get(row).get(col).setAlive(false);
                } else if(getState(row, col, oldCells) == 1) {
                    cells.get(row).get(col).setAlive(true);
                }
            }
        }
    }

    private int getState(int row, int col, Map<Integer, List<GameOfLifeCell>> oldCells) {
        // count all neighbors in N8
        int neighbourCount = 0;
        for(int xOffset=-1; xOffset <= 1; xOffset++) {
            for(int yOffset=-1; yOffset <= 1; yOffset++) {
                // calculate neighbor coordinates
                int nbRow = row + xOffset;
                int nbCol = col + yOffset;
                // check if coordinates are inside bounds and different to the initial cells
                if(nbCol >= 0 && nbCol < cols && nbRow >= 0 && nbRow < rows && !(xOffset==0 && yOffset==0)) {
                    // if the cell is alive, increase the counter
                    if(oldCells.get(nbRow).get(nbCol).isAlive()) {
                        neighbourCount++;
                    }
                }
            }
        }

        // check if an alive cell has too much or too little neighbors ( = dies)
        if(oldCells.get(row).get(col).isAlive()) {
            if (neighbourCount <= 1 || neighbourCount >= 4) {
                return -1;
            }
        } else { // and check if a dead cell has 3 neighbors (= becomes alive)
            if(neighbourCount == 3) {
                return 1;
            }
        }
        return 0;
    }

    public void startStepping() {
        // make a new thread to avoid blocking the UI thread
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                // first, save the initial state to a map
                backupCells.clear();
                deepCopyCells(cells,backupCells);
                running = true;

                // unless stopped, make one step every 250ms
                while(running) {
                    Platform.runLater(() -> step());
                    try {
                        Thread.sleep(250);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        // set the thread as daemon to close it together with the UI
        t.setDaemon(true);
        t.start();
    }

    public void stopStepping() {
        running = false;
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
