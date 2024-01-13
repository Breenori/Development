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
    private JButton btnUpdatePerson;
    private JButton btnRemovePerson;
    private JTable tblPersons;

    private JDialog dlgAddPerson;
    private JDialog dlgUpdatePerson;
    private JDialog dlgRemovePerson;

    private JTextField txtFirstName;
    private JTextField txtLastName;
    private JTextField txtCity;
    private JTextField txtZip;
    private JTextField txtAddress;
    private JTextField txtTel;

    private PersonController.PersonAddListener personAddListener;
    private PersonController.PersonUpdateListener personUpdateListener;
    private PersonController.PersonRemoveListener personRemoveListener;

    private boolean removing;

    public PersonOverViewFrame() {initLayout();}

    public void setPersonAddListener(PersonController.PersonAddListener personAddListener) {
        this.personAddListener = personAddListener;
    }

    public void setPersonUpdateListener(PersonController.PersonUpdateListener personUpdateListener) {
        this.personUpdateListener = personUpdateListener;
    }

    public void setPersonRemoveListener(PersonController.PersonRemoveListener personRemoveListener) {
        this.personRemoveListener = personRemoveListener;
    }

    private void initLayout() {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setSize(600,200);
        this.setTitle("Person Application");

        this.getContentPane().setLayout(new BorderLayout(6,6));

        //region Header
        JPanel pnlHeader = new JPanel();
        pnlHeader.setLayout(new FlowLayout(FlowLayout.LEFT));
        JLabel lblTitle = new JLabel("Person Overview");
        pnlHeader.add(lblTitle);

        this.getContentPane().add(pnlHeader, BorderLayout.NORTH);
        //endregion

        //region Center - Table
        JPanel pnlCenter = new JPanel();
        TitledBorder tb = new TitledBorder("Available Persons");
        pnlCenter.setBorder(tb);

        pnlCenter.setLayout(new BorderLayout(6,6));
        tblPersons = new JTable();
        JScrollPane scrollPane = new JScrollPane(tblPersons);
        pnlCenter.add(scrollPane, BorderLayout.CENTER);

        this.getContentPane().add(pnlCenter, BorderLayout.CENTER);
        //endregion

        //region Footer
        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        btnAddPerson = new JButton("Add Person");
        btnAddPerson.addActionListener(e -> showAddPersonDialog());
        pnlFooter.add(btnAddPerson);

        btnUpdatePerson = new JButton("Update Person");
        btnUpdatePerson.addActionListener(e -> showUpdatePersonDialog());
        pnlFooter.add(btnUpdatePerson);

        btnRemovePerson = new JButton("Remove Person");
        btnRemovePerson.addActionListener(e -> showRemovePersonDialog());
        pnlFooter.add(btnRemovePerson);

        this.getContentPane().add(pnlFooter, BorderLayout.SOUTH);
        //endregion
    }

    private void showAddPersonDialog() {
        removing = false;

        // Initialize Dialog
        dlgAddPerson = new JDialog(this, "Add Person", true);
        dlgAddPerson.setSize(new Dimension(400,150));
        dlgAddPerson.setLocationRelativeTo(btnAddPerson);
        dlgAddPerson.setResizable(false);

        JPanel pnlForm = new JPanel();
        TitledBorder tb = new TitledBorder("Add new person");
        pnlForm.setBorder(tb);
        pnlForm.setLayout(new GridLayout(3,2));

        // Initialize fields and add them to the panel
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

        // add the button to the bottom of the panel
        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        JButton btnSavePErson = new JButton("Save Person");
        btnSavePErson.addActionListener(personAddListener);
        pnlFooter.add(btnSavePErson);

        // finally, add the panel to the dialog
        dlgAddPerson.getContentPane().add(pnlForm, BorderLayout.CENTER);
        dlgAddPerson.getContentPane().add(pnlFooter, BorderLayout.SOUTH);

        dlgAddPerson.setVisible(true);
        dlgAddPerson.pack();
    }
    public void closeAddPersonDialog() {
        clearFields();
        dlgAddPerson.setVisible(false);
    }

    private void showUpdatePersonDialog() {
        removing = false;
        int row = tblPersons.getSelectedRow();
        if(row < 0) {
            showError("Please select a person to update.");
            return;
        }

        // dialog initialization
        dlgUpdatePerson = new JDialog(this, "Update Person", true);
        dlgUpdatePerson.setSize(new Dimension(400,150));
        dlgUpdatePerson.setLocationRelativeTo(btnUpdatePerson);
        dlgUpdatePerson.setResizable(false);

        JPanel pnlForm = new JPanel();
        TitledBorder tb = new TitledBorder("Update person");
        pnlForm.setBorder(tb);
        pnlForm.setLayout(new GridLayout(3,2));

        // get data from table
        Long id = (Long) tblPersons.getValueAt(row, 0);
        txtFirstName = new JTextField(tblPersons.getValueAt(row, 1).toString());
        txtLastName = new JTextField(tblPersons.getValueAt(row, 2).toString());
        txtCity = new JTextField(tblPersons.getValueAt(row, 3).toString());
        txtZip = new JTextField(tblPersons.getValueAt(row, 4).toString());
        txtAddress = new JTextField(tblPersons.getValueAt(row, 5).toString());
        txtTel = new JTextField(tblPersons.getValueAt(row, 6).toString());


        // show Labels and prefilled textboxes
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

        // add footer with button
        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        JButton btnSavePerson = new JButton("Save Person");
        btnSavePerson.addActionListener(personUpdateListener);
        pnlFooter.add(btnSavePerson);

        dlgUpdatePerson.getContentPane().add(pnlForm, BorderLayout.CENTER);
        dlgUpdatePerson.getContentPane().add(pnlFooter, BorderLayout.SOUTH);

        dlgUpdatePerson.setVisible(true);
        dlgUpdatePerson.pack();
    }
    public void closeUpdatePersonDialog() {
        clearFields();
        dlgUpdatePerson.setVisible(false);
    }

    private void showRemovePersonDialog() {
        int row = tblPersons.getSelectedRow();
        if(row < 0) {
            showError("Please select a person to remove.");
            return;
        }
        removing = true;
        // init dialog
        dlgRemovePerson = new JDialog(this, "Remove Person", true);
        dlgRemovePerson.setSize(new Dimension(400,150));
        dlgRemovePerson.setLocationRelativeTo(btnRemovePerson);
        dlgRemovePerson.setResizable(false);

        JPanel pnlForm = new JPanel();
        TitledBorder tb = new TitledBorder("Remove person");
        pnlForm.setBorder(tb);
        pnlForm.setLayout(new GridLayout(3,2));

        // add removal info and button
        JLabel lblRemovePerson = new JLabel("Do you really want to remove the selected person?");
        pnlForm.add(lblRemovePerson);

        JPanel pnlFooter = new JPanel();
        pnlFooter.setLayout(new FlowLayout(FlowLayout.RIGHT));
        JButton btnRemovePerson = new JButton("Remove Person");
        btnRemovePerson.addActionListener(personRemoveListener);
        pnlFooter.add(btnRemovePerson);

        dlgRemovePerson.getContentPane().add(pnlForm, BorderLayout.CENTER);
        dlgRemovePerson.getContentPane().add(pnlFooter, BorderLayout.SOUTH);

        dlgRemovePerson.setVisible(true);
        dlgRemovePerson.pack();
    }
    public void closeRemovePersonDialog() {
        dlgRemovePerson.setVisible(false);
    }

    private void clearFields() {
        txtFirstName.setText("");
        txtLastName.setText("");
        txtCity.setText("");
        txtZip.setText("");
        txtAddress.setText("");
        txtTel.setText("");
    }

    public void showError(String message) {
        // show a delegated error
        JOptionPane.showMessageDialog(this, message, "Error", JOptionPane.ERROR_MESSAGE);
    }

    @Override
    public void bindModel(PersonModel model) {
        // set new model as data and siplay it
        tblPersons.setModel(new PersonTableModel(model.getPersons()));
    }

    @Override
    public PersonModel fillModel(PersonModel model) {

        Long id = null;
        String firstName = "";
        String lastName = "";
        String city = "";
        Long zip = null;
        String address = "";
        String tel = "";

        // if a row is selected in the table, get the persons index for removal
        int rowIndex = tblPersons.getSelectedRow();
        if(rowIndex >= 0) {
            id = (Long)tblPersons.getValueAt(rowIndex,0);
        }

        // fill model from dialog fields if mode is not "removing"
        if(!removing) {
            firstName = txtFirstName.getText();
            lastName = txtLastName.getText();
            city = txtCity.getText();
            try {
                zip = Long.parseLong(txtZip.getText());
            } catch(NumberFormatException e) {
                zip = null;
            }
            address = txtAddress.getText();
            tel = txtTel.getText();
        }

        // check for false inputs and show errors
        if(removing && id == null) {
            showError("Error removing person. Please select an entry.");
        } else if (!removing && firstName.isEmpty()) {
            showError("Invalid firstname.");
        } else if (!removing && lastName.isEmpty()) {
            showError("Invalid lastname.");
        } else if (!removing && city.isEmpty()) {
            showError("Invalid city.");
        } else if (!removing && zip == null) {
            showError("Invalid zip code.");
        } else if (!removing && address.isEmpty()) {
            showError("Invalid address.");
        }else if (!removing && tel.isEmpty()) {
            showError("Invalid telephone number.");
        } else {
            // if no errors are present, create a new person using the read data
            Person newPerson = new Person(firstName,lastName,city,zip,address,tel);
            newPerson.setId(id);

            // ... and set the currentPerson and return the model
            model.setCurrentPerson(newPerson);
        }

        return model;
    }
}
