package swp4.ue05.part1.ui.controller;

import swp4.ue05.part1.logic.PersonLogic;
import swp4.ue05.part1.logic.impl.PersonLogicImpl;
import swp4.ue05.part1.ui.model.PersonModel;
import swp4.ue05.part1.ui.view.impl.PersonOverViewFrame;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PersonController {
    private PersonOverViewFrame view;
    private PersonModel model;
    private PersonLogic personLogic = new PersonLogicImpl();

    public PersonController() {
        this.view = new PersonOverViewFrame();
        this.model = personLogic.readAllPersons(new PersonModel());
        // add all button action listeners
        this.view.setPersonAddListener(new PersonAddListener());
        this.view.setPersonUpdateListener(new PersonUpdateListener());
        this.view.setPersonRemoveListener(new PersonRemoveListener());
        this.view.bindModel(this.model);
    }

    public void show() {
        view.setVisible(true);
    }

    public class PersonAddListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            // get infos from view
            model = view.fillModel(model);
            new Thread(this::addPerson).start();
            view.closeAddPersonDialog();
        }

        private void addPerson() {
            // save the person in the db, if successful read all persons and return them
            if(personLogic.savePerson(model)) {
                model = personLogic.readAllPersons(model);
                SwingUtilities.invokeLater(() -> view.bindModel(model));
            } else {
                SwingUtilities.invokeLater(() -> view.showError("Could not save person to database."));
            }
        }
    }

    public class PersonUpdateListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            model = view.fillModel(model);
            new Thread(this::updatePerson).start();
            view.closeUpdatePersonDialog();
        }

        private void updatePerson() {
            // if updating the person was successful, update the view
            if(personLogic.updatePerson(model) != null) {
                model = personLogic.readAllPersons(model);
                SwingUtilities.invokeLater(() -> view.bindModel(model));
            } else {
                SwingUtilities.invokeLater(() -> view.showError("Could not update person in database."));
            }
        }
    }

    public class PersonRemoveListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            model = view.fillModel(model);
            new Thread(this::removePerson).start();
            view.closeRemovePersonDialog();
        }

        private void removePerson() {
            // if removing the person was successful, update the view
            if(personLogic.deletePerson(model)) {
                model = personLogic.readAllPersons(model);
                SwingUtilities.invokeLater(() -> view.bindModel(model));
            } else {
                SwingUtilities.invokeLater(() -> view.showError("Could not remove person from database."));
            }
        }
    }
}
