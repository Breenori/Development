package swp4.ue05.part2.ui.view;

import swp4.ue05.part2.ui.model.AlignmentModel;

public interface BindableView {
    void bindModel(AlignmentModel model);

    AlignmentModel fillModel(AlignmentModel model);
}
