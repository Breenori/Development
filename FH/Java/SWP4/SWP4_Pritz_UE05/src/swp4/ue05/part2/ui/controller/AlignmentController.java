package swp4.ue05.part2.ui.controller;

import swp4.ue05.part2.domain.AlignmentItem;
import swp4.ue05.part2.logic.AlignmentLogic;
import swp4.ue05.part2.logic.impl.AlignmentLogicImpl;
import swp4.ue05.part2.ui.model.AlignmentModel;
import swp4.ue05.part2.ui.view.impl.AlignmentOverViewFrame;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AlignmentController {
    private AlignmentOverViewFrame view;
    private AlignmentModel model;
    private AlignmentLogic alignmentLogic = new AlignmentLogicImpl();
    boolean selectionBlocked = false;

    public AlignmentController() {
        this.view = new AlignmentOverViewFrame();
        this.model = alignmentLogic.getAlignments(new AlignmentModel());
        // set the listeners in the view
        this.view.setAlignmentAddListener(new AlignmentAddListener());
        this.view.setAlignmentRemoveListener(new AlignmentRemoveListener());
        // add a selectionListener, which recognizes if selection has changed and sets the text fields accordingly
        this.view.setListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if(!e.getValueIsAdjusting() && !selectionBlocked) {
                    JList list = (JList) e.getSource();
                    AlignmentItem selectedValue = (AlignmentItem) list.getSelectedValue();
                    view.changeSelection(selectedValue);
                }
            }
        });
        this.view.bindModel(this.model);
    }

    public void show() {
        this.view.setVisible(true);
    }

    // add action listeners for remove and add process
    public class AlignmentAddListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            model = view.fillModel(model);
            new Thread(this::addAlignment).start();
        }

        private void addAlignment() {
            if(alignmentLogic.addAlignment(model)) {
                model = alignmentLogic.getAlignments(model);
                SwingUtilities.invokeLater(() -> view.bindModel(model));
            } else {
                SwingUtilities.invokeLater(() -> view.showError("Could not add alignment."));
            }
        }
    }

    public class AlignmentRemoveListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            selectionBlocked = true;
            // when removing, we get the object from the selection, not the input text fields!
            view.fillModelFromSelection(model);
            new Thread(this::removeAlignment).start();
        }

        private void removeAlignment() {
            if(alignmentLogic.removeAlignment(model)) {
                SwingUtilities.invokeLater(() -> view.bindModel(model));
            } else {
                SwingUtilities.invokeLater(() -> view.showError("Could not delete alignment."));
            }
            selectionBlocked = false;
        }
    }
}
