package swp4.ue05.part2.logic;

import swp4.ue05.part2.ui.model.AlignmentModel;

public interface AlignmentLogic {
    boolean addAlignment(AlignmentModel model);
    AlignmentModel getAlignments(AlignmentModel model);
    boolean removeAlignment(AlignmentModel model);
}
