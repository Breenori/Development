package swp4.ui.view.impl;

import swp4.jdbc.domain.Employee;
import swp4.ui.controller.EmployeeController;
import swp4.ui.model.EmployeeModel;
import swp4.ui.view.BindableView;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDate;

public class EmployeeOverViewFrame extends JFrame implements BindableView {

    private JButton btnAddEmployee;
    private JTable tblEmployees;

    private JDialog dlgAddEmployee;
    private JTextField txtFirstName;
    private JTextField txtLastName;
    private JTextField txtDateOfBirth;

    private EmployeeController.EmployeeAddListener employeeAddListener;

    public EmployeeOverViewFrame() {
        initLayout();
    }

    public void setEmployeeAddListener(EmployeeController.EmployeeAddListener employeeAddListener) {
        this.employeeAddListener = employeeAddListener;
    }

    private void initLayout() {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setSize(600,200);
        this.setTitle("Employee Application");

        this.getContentPane().setLayout(new BorderLayout(6,6));

        // HEADER
        JPanel pnlHeader = new JPanel();
        pnlHeader.setLayout(new FlowLayout(FlowLayout.LEFT));
        JLabel lblTitle = new JLabel("Employee Overview");
        pnlHeader.add(lblTitle);

        this.getContentPane().add(pnlHeader, BorderLayout.NORTH);

        // CENTER
        JPanel pnlCenter = new JPanel();
        TitledBorder tb = new TitledBorder("Available Employees");
        pnlCenter.setBorder(tb);

        pnlCenter.setLayout(new BorderLayout(6,6));
        tblEmployees = new JTable();
        JScrollPane scrollPane = new JScrollPane(tblEmployees);
        pnlCenter.add(scrollPane, BorderLayout.CENTER);

        this.getContentPane().add(pnlCenter, BorderLayout.CENTER);

        //FOOTER
        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        btnAddEmployee = new JButton("AddEmployee");
        // Version 1: using anonymous class
        /*btnAddEmployee.addActionListener(
                new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        showEmployeeDialog();
                    }
                }
        );*/
        // Version 2: using lambdas | method references
        btnAddEmployee.addActionListener(e -> showEmployeeDialog());

        pnlFooter.add(btnAddEmployee);

        this.getContentPane().add(pnlFooter, BorderLayout.SOUTH);

    }

    private void showEmployeeDialog() {
        dlgAddEmployee = new JDialog(this, "Add Employee", true);
        dlgAddEmployee.setSize(new Dimension(400,150));
        dlgAddEmployee.setLocationRelativeTo(btnAddEmployee);
        dlgAddEmployee.setResizable(false);

        JPanel pnlForm = new JPanel();
        TitledBorder tb = new TitledBorder("Add new employee");
        pnlForm.setBorder(tb);
        pnlForm.setLayout(new GridLayout(3,2));

        txtFirstName = new JTextField();
        txtLastName = new JTextField();
        txtDateOfBirth = new JTextField();

        pnlForm.add(new JLabel("First Name: "));
        pnlForm.add(txtFirstName);
        pnlForm.add(new JLabel("Last Name: "));
        pnlForm.add(txtLastName);
        pnlForm.add(new JLabel("Date of Birth: "));
        pnlForm.add(txtDateOfBirth);

        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        JButton btnSaveEmployee = new JButton("Save Employee");
        btnSaveEmployee.addActionListener(employeeAddListener);
        pnlFooter.add(btnSaveEmployee);

        dlgAddEmployee.getContentPane().add(pnlForm, BorderLayout.CENTER);
        dlgAddEmployee.getContentPane().add(pnlFooter, BorderLayout.SOUTH);

        dlgAddEmployee.setVisible(true);
        dlgAddEmployee.pack();
    }

    public void closeEmployeeAddDialog() {
        txtFirstName.setText("");
        txtLastName.setText("");
        txtDateOfBirth.setText("");
        dlgAddEmployee.dispose();
    }

    public void showError(String message) {
        JOptionPane.showMessageDialog(this, message, "Error", JOptionPane.ERROR_MESSAGE);
    }

    @Override
    public void bindModel(EmployeeModel model) {
        tblEmployees.setModel(new EmployeeTableModel(model.getEmployees()));
        btnAddEmployee.setEnabled(true);
    }

    @Override
    public EmployeeModel fillModel(EmployeeModel model) {
        String firstName = txtFirstName.getText();
        String lastName = txtLastName.getText();
        LocalDate dob = LocalDate.parse(txtDateOfBirth.getText());
        model.setCurrentEmployee(new Employee(firstName, lastName, dob));

        btnAddEmployee.setEnabled(false);

        return model;
    }
}
