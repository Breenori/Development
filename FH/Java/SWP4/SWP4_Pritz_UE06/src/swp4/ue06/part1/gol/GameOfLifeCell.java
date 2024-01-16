package swp4.ue06.part1.gol;

import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.scene.shape.Rectangle;

public class GameOfLifeCell extends Rectangle {
    // Property to display the alive status
    private BooleanProperty aliveProperty = new SimpleBooleanProperty();

    // getter for alive property value
    public boolean isAlive() {
        return aliveProperty.get();
    }

    // set the alive property value
    public void setAlive(boolean alive) {
        aliveProperty.set(alive);
    }

    // get the alive property
    public BooleanProperty aliveProperty() {
        return aliveProperty;
    }
}
