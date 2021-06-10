package swp4.ue05.part2;

import swp4.ue05.part1.ui.controller.PersonController;
import swp4.ue05.part2.ui.controller.AlignmentController;

import javax.swing.*;

public class AlignmentApplication {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                AlignmentController controller = new AlignmentController();
                controller.show();
            }
        });
    }
}
