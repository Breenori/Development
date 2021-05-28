package swp4.ui.controller;

import swp4.jdbc.domain.Employee;
import swp4.logic.EmployeeLogic;
import swp4.logic.impl.EmployeeLogicImpl;
import swp4.ui.model.EmployeeModel;
import swp4.ui.view.impl.EmployeeOverViewFrame;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class EmployeeController {
    private EmployeeOverViewFrame view;
    private EmployeeModel model;
    private EmployeeLogic employeeLogic = new EmployeeLogicImpl();

    public EmployeeController() {
        this.view = new EmployeeOverViewFrame();
        this.model = employeeLogic.readAllEmployees(new EmployeeModel());
        this.view.setEmployeeAddListener(new EmployeeAddListener());
        this.view.bindModel(this.model);
    }

    public void show() {
        view.setVisible(true);
    }

    public class EmployeeAddListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            // 1) fill model from UI
            model = view.fillModel(model);
            // Version 1: using anonymous class
            /*new Thread(new Runnable() {
                @Override
                public void run() {
                    addEmployee();
                }
            }).start();*/
            // Version 2 using lambdas | method references
            new Thread(this::addEmployee).start();

            // or using lambdas
            //new Thread( () -> addEmployee()).start();
            view.closeEmployeeAddDialog();
        }

        private void addEmployee() {
            // 2) Save employee via business logic
            if(employeeLogic.saveEmployee(model)) {
                // 3) notify UI rebind new data
                model = employeeLogic.readAllEmployees(model);
                try {
                    Thread.sleep(10000);
                } catch (InterruptedException interruptedException) {
                    interruptedException.printStackTrace();
                }
                SwingUtilities.invokeLater( () -> view.bindModel(model));
            } else {
                // error
                SwingUtilities.invokeLater( () -> view.showError("Could not save employee."));
            }
        }
    }
}
