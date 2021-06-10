package swp4.ue05.part2.ui.view.impl;

import neobio.alignment.*;
import swp4.ue05.part2.domain.AlignmentResult;
import swp4.ue05.part2.ui.controller.AlignmentController;
import swp4.ue05.part2.ui.view.BindableView;
import swp4.ue05.part2.ui.model.AlignmentModel;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.io.IOException;
import java.io.StringReader;
import java.text.ParseException;

public class AlignmentOverViewFrame extends JFrame implements BindableView {

    //region UI-Elements
    JDialog dlgAbout;

    JMenuBar menuBar;
    JMenu menuHelp;
    JMenuItem menuHelpAbout;

    JList<AlignmentResult> listAlignments;
    JTextArea txaResult;
    JTextArea txaSeq1;
    JTextArea txaSeq2;
    JSpinner spnMatch;
    JSpinner spnMisMatch;
    JSpinner spnGap;
    JComboBox<String> cobAlgorithm;

    JButton btnNew;
    JButton btnRemove;
    JButton btnCompute;
    JButton btnSave;
    JButton btnLoad1;
    JButton btnLoad2;
    //endregion

    NeedlemanWunsch needlemanWunsch = new NeedlemanWunsch();
    SmithWaterman smithWaterman = new SmithWaterman();

    public AlignmentOverViewFrame() {
        initLayout();
    }

    public void setAlignmentComputeListener(AlignmentController.AlignmentComputeListener alignmentComputeListener) {
        this.btnCompute.addActionListener(alignmentComputeListener);
    }

    public void setAlignmentRemoveListener(AlignmentController.AlignmentRemoveListener alignmentRemoveListener) {
        this.btnRemove.addActionListener(alignmentRemoveListener);
    }

    public void setListSelectionListener(ListSelectionListener listSelectionListener) {
        this.listAlignments.addListSelectionListener(listSelectionListener);
    }

    private void initLayout() {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setSize(1280,720);
        this.setMinimumSize(new Dimension(800,600));
        this.setTitle("Alignments");
        this.getContentPane().setLayout(new BorderLayout(6,6));

        //region Menubar
        menuBar = new JMenuBar();
        menuHelp = new JMenu("Help");
        menuBar.add(menuHelp);
        menuHelpAbout = new JMenuItem("About");
        menuHelpAbout.addActionListener(e -> showAbout());
        menuHelp.add(menuHelpAbout);
        this.setJMenuBar(menuBar);
        //endregion

        //region TablePanel
        JPanel pnlTable = new JPanel();
        pnlTable.setLayout(new BorderLayout(6,6));
        TitledBorder tbTable = new TitledBorder("Alignments");
        pnlTable.setBorder(tbTable);

        listAlignments = new JList();
        JScrollPane scrollPane = new JScrollPane(listAlignments);
        pnlTable.add(scrollPane, BorderLayout.CENTER);

        // Buttons beneath table
        JPanel pnlTableButtons = new JPanel();
        pnlTableButtons.setLayout(new FlowLayout(FlowLayout.RIGHT));

        btnNew = new JButton("New");
        btnNew.addActionListener(e -> newAlignment());
        pnlTableButtons.add(btnNew);

        btnRemove = new JButton("Remove");
        pnlTableButtons.add(btnRemove);

        btnCompute = new JButton("Compute");
        pnlTableButtons.add(btnCompute);

        btnSave = new JButton("Save result...");
        btnSave.addActionListener(e -> saveAlignment());
        pnlTableButtons.add(btnSave);

        pnlTable.add(pnlTableButtons, BorderLayout.SOUTH);
        pnlTable.setPreferredSize(new Dimension(400,100));

        this.getContentPane().add(pnlTable, BorderLayout.LINE_START);
        //endregion

        //region InputPanel
        JPanel pnlInput = new JPanel();
        TitledBorder tbInput = new TitledBorder("Alignment Command");
        pnlInput.setBorder(tbInput);
        GridBagLayout gbl = new GridBagLayout();
        GridBagConstraints gbc = new GridBagConstraints();
        pnlInput.setLayout(gbl);

        //region Line 1 - Sequence 1
        gbc.insets = new Insets(3,3,3,3);
        gbc.fill = GridBagConstraints.BOTH;
        gbc.anchor = GridBagConstraints.WEST;

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 0;
        gbc.weighty = 0.5;
        JLabel lblSeq1 = new JLabel("Sequence 1");
        pnlInput.add(lblSeq1, gbc);

        gbc.gridx = 1;
        gbc.weightx = 1;

        txaSeq1 = new JTextArea("");
        txaSeq1.setLineWrap(true);
        JScrollPane scrollPaneSeq1 = new JScrollPane(txaSeq1);
        pnlInput.add(scrollPaneSeq1,gbc);

        gbc.gridx = 2;
        gbc.weightx = 0;
        btnLoad1 = new JButton("Load...");
        btnLoad1.setPreferredSize(new Dimension(100,100));
        pnlInput.add(btnLoad1,gbc);
        //endregion
        //region Line 2 - Sequence 2
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.weightx = 0;
        JLabel lblSeq2 = new JLabel("Sequence 2");
        pnlInput.add(lblSeq2, gbc);

        gbc.gridx = 1;
        gbc.weightx = 1;
        txaSeq2 = new JTextArea("");
        txaSeq2.setLineWrap(true);
        JScrollPane scrollPaneSeq2 = new JScrollPane(txaSeq2);
        pnlInput.add(scrollPaneSeq2,gbc);

        gbc.gridx = 2;
        gbc.weightx = 0;
        btnLoad2 = new JButton("Load...");
        btnLoad2.setPreferredSize(new Dimension(100,100));
        pnlInput.add(btnLoad2,gbc);
        gbc.weighty = 0;
        //endregion
        //region Line 3 - Match
        gbc.gridx = 0;
        gbc.gridy = 2;
        JLabel lblMatch = new JLabel("Match");
        pnlInput.add(lblMatch, gbc);

        gbc.gridx = 1;
        gbc.weightx = 1;
        gbc.gridwidth = 2;
        spnMatch = new JSpinner(new SpinnerNumberModel(1,0,100,1));
        pnlInput.add(spnMatch,gbc);
        //endregion
        //region Line 4 - Mismatch
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.weightx = 0;
        JLabel lblMismatch = new JLabel("Mismatch");
        pnlInput.add(lblMismatch, gbc);

        gbc.gridx = 1;
        gbc.weightx = 1;
        gbc.gridwidth = 2;
        spnMisMatch = new JSpinner(new SpinnerNumberModel(-1,-100,0,1));
        pnlInput.add(spnMisMatch,gbc);
        //endregion
        //region Line 5 - Gap
        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.weightx = 0;
        JLabel lblGap = new JLabel("Gap");
        pnlInput.add(lblGap, gbc);

        gbc.gridx = 1;
        gbc.weightx = 1;
        gbc.gridwidth = 2;
        spnGap = new JSpinner(new SpinnerNumberModel(-1,-100,0,1));
        pnlInput.add(spnGap,gbc);
        //endregion
        //region Line 6 - Mismatch
        gbc.gridx = 0;
        gbc.gridy = 5;
        gbc.weightx = 0;
        JLabel lblAlgorithm = new JLabel("Algorithm");
        pnlInput.add(lblAlgorithm, gbc);

        gbc.gridx = 1;
        gbc.weightx = 1;
        gbc.gridwidth = 2;
        cobAlgorithm = new JComboBox<>();
        cobAlgorithm.addItem("NeedlemanWunsch");
        cobAlgorithm.addItem("SmithWaterman");
        pnlInput.add(cobAlgorithm,gbc);
        //endregion

        this.getContentPane().add(pnlInput, BorderLayout.CENTER);
        //endregion

        //region ResultPanel
        JPanel pnlResult = new JPanel();
        pnlResult.setLayout(new BorderLayout(6,6));
        TitledBorder tbResult = new TitledBorder("Result");
        pnlResult.setBorder(tbResult);

        txaResult = new JTextArea();
        txaResult.setFont(new Font("monospaced", Font.PLAIN, 12));
        txaResult.setEditable(false);
        txaResult.setLineWrap(true);
        JScrollPane scrollPaneRes = new JScrollPane(txaResult);
        pnlResult.add(scrollPaneRes, BorderLayout.CENTER);
        scrollPaneRes.setPreferredSize(new Dimension(200,200));
        this.getContentPane().add(pnlResult, BorderLayout.SOUTH);
        //endregion
    }

    public void changeSelection(AlignmentResult alignmentResult) {
        if(alignmentResult != null) {
            txaSeq1.setText(alignmentResult.getSequence1());
            txaSeq2.setText(alignmentResult.getSequence2());
            spnMatch.setValue(alignmentResult.getMatch());
            spnMisMatch.setValue(alignmentResult.getMismatch());
            spnGap.setValue(alignmentResult.getGap());
            cobAlgorithm.setSelectedIndex(alignmentResult.getAlgorithm());

            txaResult.setText(alignmentResult.getPairwiseAlignment().toString());
        }
    }

    public void showAbout() {
        dlgAbout = new JDialog(this, "About", true);
        dlgAbout.setSize(new Dimension(400,150));
        dlgAbout.setLocationRelativeTo(menuHelpAbout);
        dlgAbout.setResizable(false);

        JPanel pnlAbout = new JPanel();
        TitledBorder tb = new TitledBorder("What is this program?");
        pnlAbout.setBorder(tb);
        pnlAbout.setLayout(new BorderLayout(6,6));

        JTextArea lblInfo = new JTextArea("This program offers a visual interface for computing biological alignments. It was done as a part of the 5th homework in the SWP4 course.");
        lblInfo.setEditable(false);
        lblInfo.setWrapStyleWord(true);
        lblInfo.setLineWrap(true);
        pnlAbout.add(lblInfo);

        dlgAbout.getContentPane().add(pnlAbout, BorderLayout.CENTER);

        dlgAbout.setVisible(true);
        dlgAbout.pack();
    }

    public void showError(String message) {
        JOptionPane.showMessageDialog(this, message, "Error", JOptionPane.ERROR_MESSAGE);
    }

    private void newAlignment() {
        txaSeq1.setText("");
        txaSeq2.setText("");
        spnMatch.setValue(1);
        spnMisMatch.setValue(-1);
        spnGap.setValue(-1);
        txaResult.setText("");
        txaSeq1.requestFocus();
    }

    public AlignmentModel fillModelToDelete(AlignmentModel model) {
        model.setCurrentAlignment(listAlignments.getSelectedValue());
        txaResult.setText("");

        return model;
    }

    private void saveAlignment() {

    }

    @Override
    public void bindModel(AlignmentModel model) {
        listAlignments.setModel(new AlignmentListModel(model.getAlignments()));
        AlignmentResult result = model.getCurrentAlignment();
        if(result != null) {
            txaResult.setText(new StringBuilder()
                    .append("##############################\n")
                    .append("Algorithm: "+(result.getAlgorithm() == 0 ? "NeedlemanWunsch" : "SmithWaterman")+"\n")
                    .append("Score: "+result.getPairwiseAlignment().getScore()+"\n")
                    .append("##############################\n")
                    .append("\n")
                    .append(result.getPairwiseAlignment())
                    .toString()
            );
        } else {
            txaResult.setText("");
        }
        btnCompute.setEnabled(true);
    }

    @Override
    public AlignmentModel fillModel(AlignmentModel model) {
        String seq1 = txaSeq1.getText();
        String seq2 = txaSeq2.getText();
        // commit changes for manually entered values
        try {
            spnMatch.commitEdit();
            spnMisMatch.commitEdit();
            spnGap.commitEdit();
        } catch (ParseException e) {
            e.printStackTrace();
        }
        int match = (int)spnMatch.getValue();
        int mismatch = (int)spnMisMatch.getValue();
        int gap = (int)spnGap.getValue();
        int algorithm = cobAlgorithm.getSelectedIndex();

        BasicScoringScheme scoringScheme = new BasicScoringScheme(match, mismatch, gap);
        try {
            switch(algorithm) {
                case 0:
                    needlemanWunsch.setScoringScheme(scoringScheme);
                    needlemanWunsch.loadSequences(new StringReader(seq1),new StringReader(seq2));
                    model.setCurrentAlignment(new AlignmentResult(needlemanWunsch.getPairwiseAlignment(), seq1, seq2, match, mismatch, gap, algorithm));
                    break;
                case 1:
                    smithWaterman.setScoringScheme(scoringScheme);
                    smithWaterman.loadSequences(new StringReader(seq1),new StringReader(seq2));
                    model.setCurrentAlignment(new AlignmentResult(smithWaterman.getPairwiseAlignment(), seq1, seq2, match, mismatch, gap, algorithm));
                    break;
            }

            btnCompute.setEnabled(false);
        } catch (IOException | InvalidSequenceException e) {
            e.printStackTrace();
        } catch (IncompatibleScoringSchemeException e) {
            e.printStackTrace();
        }

        return model;
    }
}
