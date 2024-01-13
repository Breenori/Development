package swp4.basics.javafx.bricks;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.geometry.Bounds;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Shape;
import javafx.util.Duration;

import java.sql.Time;
import java.util.concurrent.atomic.AtomicReference;

public class BricksGameBoard extends AnchorPane {

    private double dx = 7;
    private double dy = 4;
    private double ctrlDx = 10;

    public void initGameBoard(){
        Circle ball = new Circle(10, Color.CADETBLUE);
        ball.relocate(5,5);

        Rectangle controller = new Rectangle(100, 20);
        controller.setFill(Color.DARKRED);
        controller.setY(this.getHeight() - 30); // rectange always on same same height
        this.heightProperty().addListener(e -> controller.setY(this.getHeight() - 30)); // wird das fenster geändert (größe), bleibt das rechteck an der selben stelle

        this.getChildren().add(ball);
        this.getChildren().add(controller);

/*        //Version 1: using AtomicReference
        AtomicReference<Double> dx = new AtomicReference<>((double) 7); // delta x or velocity in x-direction, //atomic reference, damit wert geändert werden kann

        Timeline timeline = new Timeline(new KeyFrame(Duration.millis(20), event ->{
            //move the ball by dx
            ball.setLayoutX(ball.getLayoutX() + dx.get());

            Bounds bounds = BricksGameBoard.this.getBoundsInLocal();
            //if the ball reaches the left or right border make the step negative
            if (ball.getLayoutX() <= (bounds.getMinX() + ball.getRadius()) || ball.getLayoutX() >= (bounds.getMaxX() - ball.getRadius())){
               dx.set(dx.get() * -1);
            }

        }));*/

        //Version 2: using global Variables / class attributes
        Timeline timeline = new Timeline(new KeyFrame(Duration.millis(20), event ->{
            //move the ball by dx
            ball.setLayoutX(ball.getLayoutX() + dx);
            //move the ball by dy
            ball.setLayoutY(ball.getLayoutY() + dy);

            Bounds bounds = BricksGameBoard.this.getBoundsInLocal();
            //if the ball reaches the left or right border make the step negative
            if (ball.getLayoutX() <= (bounds.getMinX() + ball.getRadius()) || ball.getLayoutX() >= (bounds.getMaxX() - ball.getRadius())){
                dx = -dx;   // können hier auf globale Variable zugreifen
            }

            // if the ball reaches the top or bottom border make dy negative
            if (ball.getLayoutY() <= (bounds.getMinY() + ball.getRadius()) || ball.getLayoutY() >= (bounds.getMaxY() - ball.getRadius())){
                dy = -dy;
            }

            Shape intersection = Shape.intersect(ball, controller);
            if(intersection.getBoundsInLocal().getWidth() != -1 && intersection.getBoundsInLocal().getHeight() != -1) {
                dy = -dy;
            }

        }));

        timeline.setCycleCount(Timeline.INDEFINITE);    // unendlichlang laufen
        timeline.play();

        Timeline moveController = new Timeline(new KeyFrame( Duration.millis(20), event -> {
            controller.setLayoutX(controller.getLayoutX() + ctrlDx);
        }));
        moveController.setCycleCount(Timeline.INDEFINITE);

        this.getScene().addEventHandler(KeyEvent.KEY_PRESSED, event -> {
            switch(event.getCode()) {
                case RIGHT:
                    ctrlDx = Math.max(-ctrlDx, ctrlDx);
                    if(moveController.statusProperty().get().equals(Animation.Status.STOPPED)) {
                        moveController.play();
                    }
                    break;
                case LEFT:
                    ctrlDx = Math.min(-ctrlDx, ctrlDx);
                    if(moveController.statusProperty().get().equals(Animation.Status.STOPPED)) {
                        moveController.play();
                    }
                    break;
                default:
                    break;
            }
        });

        this.getScene().addEventHandler(KeyEvent.KEY_RELEASED, event -> {
            switch(event.getCode()) {
                case RIGHT:
                case LEFT:
                    moveController.stop();
                    break;
                default:
                    break;
            }
        });
    }
}
