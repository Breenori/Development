package swp4.ui.view.impl;

import swp4.jdbc.domain.Employee;

import javax.swing.table.AbstractTableModel;
import java.util.List;

public class EmployeeTableModel extends AbstractTableModel {

    private List<Employee> employees;
    private static final String[] COLUMN_NAMES = { "#", "First Name", "Last Name", "Date of Birth" };

    public EmployeeTableModel(List<Employee> employees) {
        this.employees = employees;
    }

    @Override
    public String getColumnName(int column) {
        return COLUMN_NAMES[column];
    }

    @Override
    public int getRowCount() {
        return employees != null ? employees.size() : 0;
    }

    @Override
    public int getColumnCount() {
        return COLUMN_NAMES.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        if(employees != null) {
            Employee employee = employees.get(rowIndex);
            if(employee != null) {
                switch(columnIndex) {
                    case 0:
                        return employee.getId();
                    case 1:
                        return employee.getFirstName();
                    case 2:
                        return employee.getLastName();
                    case 3:
                        return employee.getDateOfBirth();
                    default:
                        return null;
                }
            }
        }
        return null;
    }
}
