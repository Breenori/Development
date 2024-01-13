package swp4.ue05.part2.ui.view.impl;

import chrriis.dj.nativeswing.swtimpl.NativeInterface;
import chrriis.dj.nativeswing.swtimpl.components.JWebBrowser;
import neobio.alignment.*;
import swp4.ue05.part2.domain.AlignmentItem;
import swp4.ue05.part2.ui.controller.AlignmentController;
import swp4.ue05.part2.ui.view.BindableView;
import swp4.ue05.part2.ui.model.AlignmentModel;


import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.io.*;
import java.text.ParseException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class AlignmentOverViewFrame extends JFrame implements BindableView {

    //region UI-Elements
    JDialog dlgUserguide;

    JMenuBar menuBar;
    JMenu menuHelp;
    JMenuItem menuHelpAbout;
    JMenuItem menuHelpUserguide;

    JList<AlignmentItem> listAlignments;
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

    public void setAlignmentAddListener(AlignmentController.AlignmentAddListener alignmentAddListener) {
        this.btnNew.addActionListener(alignmentAddListener);
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
        menuHelpUserguide = new JMenuItem("User-Guide");
        menuHelpUserguide.addActionListener(e -> showUserGuide());
        menuHelp.add(menuHelpUserguide);
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
        pnlTableButtons.add(btnNew);

        btnRemove = new JButton("Remove");
        pnlTableButtons.add(btnRemove);

        btnCompute = new JButton("Compute");
        btnCompute.addActionListener(e -> computeResult());
        pnlTableButtons.add(btnCompute);

        btnSave = new JButton("Save result...");
        btnSave.addActionListener(e -> showSaveDialog());
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

        // used GridBagLayout --> specify grid coordinates, weight (for scaling) and other settings for each element
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
        btnLoad1.addActionListener(e -> showFileDialog(1));
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
        btnLoad2.addActionListener(e -> showFileDialog(2));
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
        // set monospaced font to allow proper display for alignments
        txaResult.setFont(new Font("monospaced", Font.PLAIN, 12));
        txaResult.setEditable(false);
        txaResult.setLineWrap(true);
        JScrollPane scrollPaneRes = new JScrollPane(txaResult);
        pnlResult.add(scrollPaneRes, BorderLayout.CENTER);
        scrollPaneRes.setPreferredSize(new Dimension(200,200));
        this.getContentPane().add(pnlResult, BorderLayout.SOUTH);
        //endregion
    }

    public void changeSelection(AlignmentItem alignmentItem) {
        // when the selection changes, fill in all the fields to the items settings
        if(alignmentItem != null) {
            txaSeq1.setText(alignmentItem.getSequence1());
            txaSeq2.setText(alignmentItem.getSequence2());
            spnMatch.setValue(alignmentItem.getMatch());
            spnMisMatch.setValue(alignmentItem.getMismatch());
            spnGap.setValue(alignmentItem.getGap());
            cobAlgorithm.setSelectedIndex(alignmentItem.getAlgorithm());
            computeResult();
        }
    }

    private void showAbout() {
        JOptionPane.showMessageDialog(this, "This program allows the computation of alignments using a graphical interface.", "About", JOptionPane.INFORMATION_MESSAGE);
    }

    private void showUserGuide() {
        //region userGuide
        NativeInterface.open();
        dlgUserguide = new JDialog(this, "User Guide", true);
        dlgUserguide.setSize(new Dimension(720,480));
        dlgUserguide.setLocationRelativeTo(menuHelpUserguide);
        dlgUserguide.setResizable(false);

        JPanel pnlGuide = new JPanel();
        TitledBorder tb = new TitledBorder("User guide");
        pnlGuide.setBorder(tb);
        pnlGuide.setLayout(new BorderLayout(6,6));

        JWebBrowser wb = new JWebBrowser();
        pnlGuide.add(wb, BorderLayout.CENTER);
        wb.setBarsVisible(false);
        wb.navigate("https://www.youtube.com/watch?v=dQw4w9WgXcQ,");

        dlgUserguide.getContentPane().add(pnlGuide);
        dlgUserguide.setVisible(true);
        NativeInterface.close();
        //endregion
    }

    public void showError(String message) {
        JOptionPane.showMessageDialog(this, message, "Error", JOptionPane.ERROR_MESSAGE);
    }

    private void showFileDialog(int fieldNum) {
        JFileChooser jfc = new JFileChooser();
        if(jfc.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            // if the filechoosers action was approved, get the filepath
            String filePath = jfc.getSelectedFile().toPath().toString();

            try(BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
                String line;
                StringBuilder sb = new StringBuilder();
                // use the filepath and get file content
                while((line = reader.readLine()) != null) {
                    sb.append(line);
                }

                // finally, set the file content as text of the sequences
                if(fieldNum == 1) {
                    txaSeq1.setText(sb.toString());
                } else {
                    txaSeq2.setText(sb.toString());
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void showSaveDialog() {
        JFileChooser jfc = new JFileChooser();
        if(jfc.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            // if a location and name have been picked, get the path.
            String filePath = jfc.getSelectedFile().toPath().toString();

            // and write the result into the file
            try(FileWriter writer = new FileWriter(filePath)) {
                writer.write(txaResult.getText());
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


    public void computeResult() {
        // fetch all necessary values
        String seq1 = txaSeq1.getText();
        String seq2 = txaSeq2.getText();
        Pattern pattern = Pattern.compile("[^a-zA-Z]");
        Matcher matcherSeq1 = pattern.matcher(seq1);
        Matcher matcherSeq2 = pattern.matcher(seq2);

        // if sequences are malformed throw an error and stop
        if(matcherSeq1.find()) {
            showError("Sequence 1 contains invalid characters.");
        } else if (seq1.isEmpty()) {
            showError("Sequence 1 is empty.");
        } else if (matcherSeq2.find()) {
            showError("Sequence 2 contains invalid characters.");
        } else if (seq2.isEmpty()) {
            showError("Sequence 2 is empty.");
        } else {
            // if sequences are okay, get the scoring scheme
            try {
                spnMatch.commitEdit();
                spnMisMatch.commitEdit();
                spnGap.commitEdit();
            } catch (ParseException e) {
                e.printStackTrace();
            }
            BasicScoringScheme scoringScheme = new BasicScoringScheme((int)spnMatch.getValue(), (int)spnMisMatch.getValue(), (int)spnGap.getValue());
            PairwiseAlignment pairwiseAlignment = null;

            btnCompute.setEnabled(false);
            // finally, start the desired algorithm based on the combobox selection
            try {
                switch (cobAlgorithm.getSelectedIndex()) {
                    case 0:
                        needlemanWunsch.setScoringScheme(scoringScheme);
                        needlemanWunsch.loadSequences(new StringReader(seq1), new StringReader(seq2));
                        pairwiseAlignment = needlemanWunsch.getPairwiseAlignment();
                        break;
                    case 1:
                        smithWaterman.setScoringScheme(scoringScheme);
                        smithWaterman.loadSequences(new StringReader(txaSeq1.getText()), new StringReader(txaSeq2.getText()));
                        pairwiseAlignment = needlemanWunsch.getPairwiseAlignment();
                        break;
                }

            } catch (IOException | InvalidSequenceException e) {
                e.printStackTrace();
            } catch (IncompatibleScoringSchemeException e) {
                e.printStackTrace();
            }

            // if the algorithm finished successfully, fill in the result
            if (pairwiseAlignment != null) {
                txaResult.setText(new StringBuilder()
                        .append("##############################\n")
                        .append("Algorithm: " + (cobAlgorithm.getSelectedIndex() == 0 ? "NeedlemanWunsch" : "SmithWaterman") + "\n")
                        .append("Score: " + pairwiseAlignment.getScore() + "\n")
                        .append("##############################\n")
                        .append("\n")
                        .append(pairwiseAlignment)
                        .toString()
                );
            } else {
                txaResult.setText("PairwiseAlignment couldn't be computed.");
            }
            btnCompute.setEnabled(true);
        }
    }

    public AlignmentModel fillModelFromSelection(AlignmentModel model) {
        // get the selected alignmentItem from the List
        model.setCurrentAlignment(listAlignments.getSelectedValue());
        return model;
    }


    @Override
    public void bindModel(AlignmentModel model) {
        listAlignments.setModel(new AlignmentListModel(model.getAlignments()));
    }

    @Override
    public AlignmentModel fillModel(AlignmentModel model) {
        // fetch all values
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

        Pattern pattern = Pattern.compile("[^a-zA-Z]");
        Matcher matcherSeq1 = pattern.matcher(seq1);
        Matcher matcherSeq2 = pattern.matcher(seq2);

        // check if sequences contain letters only and arent empty
        if(matcherSeq1.find()) {
            showError("Sequence 1 contains invalid characters.");
        } else if (seq1.isEmpty()) {
            showError("Sequence 1 is empty.");
        } else if (matcherSeq2.find()) {
            showError("Sequence 2 contains invalid characters.");
        } else if (seq2.isEmpty()) {
            showError("Sequence 2 is empty.");
        } else {
            // if requirements are met, set the data
            model.setCurrentAlignment(new AlignmentItem(seq1, seq2, match, mismatch, gap, algorithm));
        }

        return model;
    }
}
