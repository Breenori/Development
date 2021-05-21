package swp4.jdbc.dao.impl;

import swp4.jdbc.dao.EmployeeDao;
import swp4.jdbc.domain.Employee;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class EmployeeDaoJdbc extends AbstractDao<Employee> implements EmployeeDao {
    private static final String TABLE_NAME = "EMPLOYEE";

    @Override
    public Employee readForIdentity(Long identity) {
        String selectSql = "SELECT * FROM "+ TABLE_NAME + " WHERE ID = ?";
        try(Connection connection = createConnection();
            PreparedStatement statement = connection.prepareStatement(selectSql)) {

            statement.setLong(1, identity);
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()) {
                long id = resultSet.getLong(1);
                String firstName = resultSet.getString(2);
                String lastName = resultSet.getString(3);
                Timestamp tsDob = resultSet.getTimestamp(4);
                LocalDate dob = tsDob != null ? tsDob.toLocalDateTime().toLocalDate() : null;

                Employee employee = new Employee(firstName, lastName, dob);
                employee.setId(id);
                return employee;
            }
        } catch (SQLException e) {
            System.err.println("Failed to fetch all Employees");
            e.printStackTrace();
            return null;
        }

        return null;
    }

    @Override
    public List<Employee> readAll() {
        String selectSql = "SELECT * FROM "+ TABLE_NAME;
        try(Connection connection = createConnection();
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(selectSql) ) {

            List<Employee> employees = new ArrayList<>();
            while(resultSet.next()) {
                long id = resultSet.getLong(1);
                String firstName = resultSet.getString(2);
                String lastName = resultSet.getString(3);
                Timestamp tsDob = resultSet.getTimestamp(4);

                LocalDate dob = tsDob != null ? tsDob.toLocalDateTime().toLocalDate() : null;
                Employee employee = new Employee(firstName, lastName, dob);
                employee.setId(id);
                employees.add(employee);
            }
            return employees;

        } catch (SQLException e) {
            System.err.println("Failed to fetch all Employees");
            e.printStackTrace();
            return null;
        }
    }

    public boolean create(Employee entity) {
        String insertSQL = "INSERT INTO "+TABLE_NAME +"(FIRSTNAME, LASTNAME, DATEOFBIRTH) VALUES (?,?,?)";
        PreparedStatement ps = null;
        try{
            Connection connection = createConnection();
            ps = connection.prepareStatement(insertSQL, Statement.RETURN_GENERATED_KEYS);
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.setTimestamp(3, Timestamp.valueOf(entity.getDateOfBirth().atStartOfDay()));

            int result = ps.executeUpdate();

            try (ResultSet generatedKeys = ps.getGeneratedKeys()) {
                if(generatedKeys.next()) {
                    entity.setId(generatedKeys.getLong(1));
                } else {
                    throw new SQLException("Setting employee.id failed, no Id contained.");
                }
            }

            return result > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    @Override
    public boolean delete(long identity) {
        String sql = "DELETE FROM "+ TABLE_NAME + " WHERE ID = ?";
        try(    Connection connection = createConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(sql) ) {
            preparedStatement.setLong(1, identity);
            int result = preparedStatement.executeUpdate();

            return result > 0;
        } catch (SQLException e) {
            System.err.println("Failed to delete employee with id "+identity);
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public boolean update(Employee entity) {
        String sql = "UPDATE "+ TABLE_NAME + " SET FIRSTNAME=?, LASTNAME=?, DATEOFBIRTH=? WHERE ID=?";
        try(    Connection connection = createConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(sql) ) {
            preparedStatement.setString(1, entity.getFirstName());
            preparedStatement.setString(2, entity.getLastName());
            preparedStatement.setTimestamp(3, Timestamp.valueOf(entity.getDateOfBirth().atStartOfDay()));
            preparedStatement.setLong(4, entity.getId());
            int result = preparedStatement.executeUpdate();

            return result > 0;
        } catch (SQLException e) {
            System.err.println("Failed to update employee with id "+entity.getId());
            e.printStackTrace();
        }

        return false;
    }
}
