package swp4.basics.javafx.binding;

import javafx.beans.binding.Bindings;
import javafx.collections.ObservableMap;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import java.util.Set;

public class SimpleBarChart extends VBox {
    private ObservableMap<String, Double> dataModel;

    public SimpleBarChart(ObservableMap<String, Double> dataModel) {
        super(10);
        this.dataModel = dataModel;
        initComponent();
    }

    private void initComponent() {
        setPadding(new Insets(20));
        Set<String> keys = dataModel.keySet();
        int i = 0;
        for(String key : keys) {
            Rectangle rectangle = new Rectangle(0,0, dataModel.get(key), 20);
            rectangle.setFill(Color.GREENYELLOW);
            rectangle.widthProperty().bind(Bindings.doubleValueAt(dataModel,key));

            getChildren().add(new HBox(10, rectangle, new Label(key)));
        }
    }
}
