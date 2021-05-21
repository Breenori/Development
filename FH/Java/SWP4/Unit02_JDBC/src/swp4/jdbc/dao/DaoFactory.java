package swp4.jdbc.dao;

import swp4.jdbc.dao.impl.EmployeeDaoJdbc;

public class DaoFactory {

    public static EmployeeDao createEmployeeDao() {
        return new EmployeeDaoJdbc();
    }
}
