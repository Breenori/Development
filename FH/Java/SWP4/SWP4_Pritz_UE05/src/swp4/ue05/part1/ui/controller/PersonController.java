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
        this.view.setPersonAddListener(new PersonAddListener());
        this.view.bindModel(this.model);
    }

    public void show() {
        view.setVisible(true);
    }

    public class PersonAddListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            model = view.fillModel(model);
            new Thread(this::addPerson).start();
            view.closeEmployeeAddDialog();
        }

        private void addPerson() {
            if(personLogic.savePerson(model)) {
                model = personLogic.readAllPersons(model);
                SwingUtilities.invokeLater(() -> view.bindModel(model));
            } else {
                SwingUtilities.invokeLater(() -> view.showError("Could not save person."));
            }
        }
    }
}
