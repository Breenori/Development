package swp4.basics.javafx.gol;

import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.scene.shape.Rectangle;

public class GameOfLifeCell extends Rectangle {
    private BooleanProperty aliveProperty = new SimpleBooleanProperty();

    public boolean isAlive() {
        return aliveProperty.get();
    }

    public void setAlive(boolean alive) {
        aliveProperty.set(alive);
    }

    public BooleanProperty aliveProperty() {
        return aliveProperty;
    }
}
