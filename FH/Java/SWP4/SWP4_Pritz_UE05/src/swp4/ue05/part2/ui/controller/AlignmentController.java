package swp4.ue05.part2.ui.controller;

import swp4.ue05.part2.domain.AlignmentResult;
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
        this.view.setAlignmentComputeListener(new AlignmentComputeListener());
        this.view.setAlignmentRemoveListener(new AlignmentRemoveListener());
        this.view.setListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if(!e.getValueIsAdjusting() && !selectionBlocked) {
                    JList list = (JList) e.getSource();
                    AlignmentResult selectedValue = (AlignmentResult) list.getSelectedValue();
                    view.changeSelection(selectedValue);
                }
            }
        });
        this.view.bindModel(this.model);
    }

    public void show() {
        this.view.setVisible(true);
    }

    public class AlignmentRemoveListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            selectionBlocked = true;
            view.fillModelToDelete(model);
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

    public class AlignmentComputeListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            model = view.fillModel(model);
            new Thread(this::computeAlignment).start();
        }

        private void computeAlignment() {


            if(alignmentLogic.addAlignment(model)) {
                model = alignmentLogic.getAlignments(model);
                SwingUtilities.invokeLater(() -> view.bindModel(model));
            } else {
                SwingUtilities.invokeLater(() -> view.showError("Could not compute alignment."));
            }
        }
    }

}
