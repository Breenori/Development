package swp4.ui.view.impl;

import swp4.jdbc.domain.Employee;
import swp4.ui.model.EmployeeModel;
import swp4.ui.view.BindableView;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

public class EmployeeOverViewFrame extends JFrame implements BindableView {

    private JButton btnAddEmployee;
    private JTable tblEmployees;

    public EmployeeOverViewFrame() {
        initLayout();
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
        pnlFooter.add(btnAddEmployee);

        this.getContentPane().add(pnlFooter, BorderLayout.SOUTH);

    }

    @Override
    public void bindModel(Employee model) {

    }

    @Override
    public EmployeeModel fillModel(EmployeeModel model) {
        return null;
    }
}
