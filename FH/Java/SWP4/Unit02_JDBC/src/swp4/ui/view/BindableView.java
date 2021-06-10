package swp4.ui.view;

import swp4.ui.model.EmployeeModel;

public interface BindableView {

    void bindModel(EmployeeModel model);

    EmployeeModel fillModel(EmployeeModel model);
}
