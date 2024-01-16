package swp4.logic;

import swp4.ui.model.EmployeeModel;

public interface EmployeeLogic {
    boolean saveEmployee(EmployeeModel model);
    EmployeeModel readAllEmployees(EmployeeModel model);
    boolean deleteEmployee(EmployeeModel model);
    EmployeeModel updateEmployee(EmployeeModel model);
}
