package swp4.ui.model;

import swp4.jdbc.domain.Employee;

import java.util.ArrayList;
import java.util.List;

public class EmployeeModel {
    private Employee currentEmployee;
    private List<Employee> employees;

    public EmployeeModel(Employee currentEmployee, List<Employee> employees) {
        this.currentEmployee = currentEmployee;
        this.employees = employees;
    }

    public EmployeeModel() {
        currentEmployee = null;
        employees = new ArrayList<>();
    }

    public Employee getCurrentEmployee() {
        return currentEmployee;
    }

    public void setCurrentEmployee(Employee currentEmployee) {
        this.currentEmployee = currentEmployee;
    }

    public List<Employee> getEmployees() {
        return employees;
    }

    public void setEmployees(List<Employee> employees) {
        this.employees = employees;
    }
}
