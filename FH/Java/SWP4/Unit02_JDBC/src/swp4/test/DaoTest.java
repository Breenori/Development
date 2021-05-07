package swp4.test;

import swp4.jdbc.dao.Dao;
import swp4.jdbc.dao.impl.EmployeeDaoJdbc;
import swp4.jdbc.domain.Employee;

import java.time.LocalDate;
import java.util.List;

public class DaoTest {
    public static void main(String[] args) {
        //testCreate();
        testReadAll();
    }

    public static void testCreate() {
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("--------- testCreate ---------");
        employeeDao.create(new Employee("John", "Doe", LocalDate.of(1984, 1, 2)));
    }

    public static void testReadAll() {
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("--------- testReadAll ---------");
        List<Employee> employeeList = employeeDao.readAll();
        for(Employee employee : employeeList) {
            System.out.println(employee);
        }
    }

}
