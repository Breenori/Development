package swp4.ue05.part1.ui.view;

import swp4.ue05.part1.ui.model.PersonModel;

public interface BindableView {

    void bindModel(PersonModel model);

    PersonModel fillModel(PersonModel model);
}
