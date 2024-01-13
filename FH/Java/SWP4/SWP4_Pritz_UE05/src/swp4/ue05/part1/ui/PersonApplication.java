package swp4.ue05.part1.ui;

import swp4.ue05.part1.ui.controller.PersonController;

import javax.swing.*;

public class PersonApplication {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                PersonController controller = new PersonController();
                controller.show();
            }
        });
    }
}
