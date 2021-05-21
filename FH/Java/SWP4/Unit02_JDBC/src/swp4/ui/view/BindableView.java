package swp4.ui.view;

import swp4.jdbc.domain.Employee;
import swp4.ui.model.EmployeeModel;

public interface BindableView {

    void bindModel(Employee model);

    EmployeeModel fillModel(EmployeeModel model);
}
