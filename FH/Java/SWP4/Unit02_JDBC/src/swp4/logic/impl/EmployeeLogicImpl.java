package swp4.logic.impl;

import swp4.jdbc.dao.DaoFactory;
import swp4.jdbc.dao.EmployeeDao;
import swp4.logic.EmployeeLogic;
import swp4.ui.model.EmployeeModel;

public class EmployeeLogicImpl implements EmployeeLogic {

    private EmployeeDao employeeDao = DaoFactory.createEmployeeDao();

    @Override
    public boolean saveEmployee(EmployeeModel model) {
        return model != null && model.getCurrentEmployee() != null && employeeDao.create(model.getCurrentEmployee());
    }

    @Override
    public EmployeeModel readAllEmployees(EmployeeModel model) {
        return new EmployeeModel(model.getCurrentEmployee(), employeeDao.readAll());
    }

    @Override
    public boolean deleteEmployee(EmployeeModel model) {
        return model != null && model.getCurrentEmployee() != null && employeeDao.delete(model.getCurrentEmployee().getId());
    }

    @Override
    public EmployeeModel updateEmployee(EmployeeModel model) {
        if(employeeDao.update(model.getCurrentEmployee())) {
            return new EmployeeModel(employeeDao.readForIdentity(model.getCurrentEmployee().getId()), model.getEmployees());
        }
        return null;
    }
}
