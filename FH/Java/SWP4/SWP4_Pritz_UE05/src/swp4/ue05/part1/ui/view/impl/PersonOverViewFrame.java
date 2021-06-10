package swp4.ue05.part1.ui.view.impl;

import swp4.ue05.part1.jdbc.domain.Person;
import swp4.ue05.part1.ui.controller.PersonController;
import swp4.ue05.part1.ui.model.PersonModel;
import swp4.ue05.part1.ui.view.BindableView;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

public class PersonOverViewFrame extends JFrame implements BindableView {

    private JButton btnAddPerson;
    private JTable tblPersons;

    private JDialog dlgAddPerson;
    private JTextField txtFirstName;
    private JTextField txtLastName;
    private JTextField txtCity;
    private JTextField txtZip;
    private JTextField txtAddress;
    private JTextField txtTel;

    private PersonController.PersonAddListener personAddListener;

    public PersonOverViewFrame() {initLayout();}

    public void setPersonAddListener(PersonController.PersonAddListener personAddListener) {
        this.personAddListener = personAddListener;
    }

    private void initLayout() {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setSize(600,200);
        this.setTitle("Person Application");

        this.getContentPane().setLayout(new BorderLayout(6,6));

        // HEADER
        JPanel pnlHeader = new JPanel();
        pnlHeader.setLayout(new FlowLayout(FlowLayout.LEFT));
        JLabel lblTitle = new JLabel("Person Overview");
        pnlHeader.add(lblTitle);

        this.getContentPane().add(pnlHeader, BorderLayout.NORTH);

        // CENTER
        JPanel pnlCenter = new JPanel();
        TitledBorder tb = new TitledBorder("Available Persons");
        pnlCenter.setBorder(tb);

        pnlCenter.setLayout(new BorderLayout(6,6));
        tblPersons = new JTable();
        JScrollPane scrollPane = new JScrollPane(tblPersons);
        pnlCenter.add(scrollPane, BorderLayout.CENTER);

        this.getContentPane().add(pnlCenter, BorderLayout.CENTER);

        //FOOTER
        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        btnAddPerson = new JButton("Add Person");
        btnAddPerson.addActionListener(e -> showPersonDialog());
        pnlFooter.add(btnAddPerson);

        this.getContentPane().add(pnlFooter, BorderLayout.SOUTH);
    }

    private void showPersonDialog() {
        dlgAddPerson = new JDialog(this, "Add Person", true);
        dlgAddPerson.setSize(new Dimension(400,150));
        dlgAddPerson.setLocationRelativeTo(btnAddPerson);
        dlgAddPerson.setResizable(false);

        JPanel pnlForm = new JPanel();
        TitledBorder tb = new TitledBorder("Add new employee");
        pnlForm.setBorder(tb);
        pnlForm.setLayout(new GridLayout(3,2));

        txtFirstName = new JTextField();
        txtLastName = new JTextField();
        txtCity = new JTextField();
        txtZip = new JTextField();
        txtAddress = new JTextField();
        txtTel = new JTextField();

        pnlForm.add(new JLabel("First Name: "));
        pnlForm.add(txtFirstName);
        pnlForm.add(new JLabel("Last Name: "));
        pnlForm.add(txtLastName);
        pnlForm.add(new JLabel("City: "));
        pnlForm.add(txtCity);
        pnlForm.add(new JLabel("ZIP: "));
        pnlForm.add(txtZip);
        pnlForm.add(new JLabel("Address: "));
        pnlForm.add(txtAddress);
        pnlForm.add(new JLabel("Tel.: "));
        pnlForm.add(txtTel);

        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        JButton btnSaveEmployee = new JButton("Save Person");
        btnSaveEmployee.addActionListener(personAddListener);
        pnlFooter.add(btnSaveEmployee);

        dlgAddPerson.getContentPane().add(pnlForm, BorderLayout.CENTER);
        dlgAddPerson.getContentPane().add(pnlFooter, BorderLayout.SOUTH);

        dlgAddPerson.setVisible(true);
        dlgAddPerson.pack();
    }

    public void closeEmployeeAddDialog() {
        txtFirstName.setText("");
        txtLastName.setText("");
        txtCity.setText("");
        txtZip.setText("");
        txtAddress.setText("");
        txtTel.setText("");
    }

    public void showError(String message) {
        JOptionPane.showMessageDialog(this, message, "Error", JOptionPane.ERROR_MESSAGE);
    }

    @Override
    public void bindModel(PersonModel model) {
        tblPersons.setModel(new PersonTableModel(model.getPersons()));
        btnAddPerson.setEnabled(true);
    }

    @Override
    public PersonModel fillModel(PersonModel model) {
        String firstName = txtFirstName.getText();
        String lastName = txtLastName.getText();
        String city = txtCity.getText();
        Long zip = Long.valueOf(txtZip.getText());
        String address = txtAddress.getText();
        String tel = txtTel.getText();

        model.setCurrentPerson(new Person(firstName,lastName,city,zip,address,tel));

        btnAddPerson.setEnabled(false);

        return model;
    }
}
