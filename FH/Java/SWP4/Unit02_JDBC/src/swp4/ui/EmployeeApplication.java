package swp4.ui;

import swp4.ui.controller.EmployeeController;
import swp4.ui.view.impl.EmployeeOverViewFrame;

import javax.swing.*;

public class EmployeeApplication {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {

            @Override
            public void run() {
                //EmployeeOverViewFrame frame = new EmployeeOverViewFrame();
                //frame.setVisible(true);
                EmployeeController controller = new EmployeeController();
                controller.show();
            }
        });
    }
}
