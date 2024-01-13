package swp4.ue04.part1.dao.impl;

import swp4.ue04.part1.dao.PersonDao;
import swp4.ue04.part1.domain.Person;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class PersonDaoJdbc extends AbstractDao<Person> implements PersonDao {
    private static final String TABLE_NAME = "person";
    @Override
    public Person readForIdentity(Long identity) {
        String selectSql = "SELECT * FROM "+TABLE_NAME+" WHERE id = ?";
        try(Connection connection = createConnection();
            // create statement, add parameter and execute it
            PreparedStatement statement = connection.prepareStatement(selectSql)) {
            statement.setLong(1, identity);
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()) {
                // if the resultset is filled, fetch all columns...
                long id = resultSet.getLong(1);
                String firstName = resultSet.getString(2);
                String lastName = resultSet.getString(3);
                String city = resultSet.getString(4);
                long zip = resultSet.getLong(5);
                String address = resultSet.getString(6);
                String tel = resultSet.getString(7);

                // and create a person
                Person person = new Person(firstName, lastName, city, zip, address, tel);
                person.setId(id);
                return person;
            }
        } catch (SQLException throwables) {
            System.err.println("Failed to fetch person with id = "+identity);
            throwables.printStackTrace();
            return null;
        }
        return null;
    }

    @Override
    public List<Person> readAll() {
        // Similar to read by identity, but with multiple Persons
        String selectSql = "SELECT * FROM "+TABLE_NAME;
        try(Connection connection = createConnection();
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(selectSql)) {

            List<Person> personList = new ArrayList<>();
            while(resultSet.next()){
                long id = resultSet.getLong(1);
                String firstName = resultSet.getString(2);
                String lastName = resultSet.getString(3);
                String city = resultSet.getString(4);
                long zip = resultSet.getLong(5);
                String address = resultSet.getString(6);
                String tel = resultSet.getString(7);

                // instead of returning the person, create new persons and add them to the list
                Person person = new Person(firstName, lastName, city, zip, address, tel);
                person.setId(id);
                personList.add(person);
            }

            return personList;
        } catch (SQLException throwables) {
            System.err.println("Failed to fetch all persons.");
            throwables.printStackTrace();
            return null;
        }
    }

    @Override
    public boolean create(Person entity) {
        // Create sql with parameters for user creation
        String createSql = "INSERT INTO "+TABLE_NAME+"(firstname, lastname, city, zip, address, tel) VALUES(?, ?, ?, ?, ?, ?)";
        PreparedStatement ps = null;
        try {
            Connection connection = createConnection();
            // prepare a statement and tell the database to return the generated keys
            ps = connection.prepareStatement(createSql, Statement.RETURN_GENERATED_KEYS);

            // fill parameters
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.setString(3, entity.getCity());
            ps.setLong(4, entity.getZip());
            ps.setString(5, entity.getAddress());
            ps.setString(6, entity.getTel());

            // execute the update
            int result = ps.executeUpdate();

            // check if keys have been generated (successful creation)
            try(ResultSet generatedKeys = ps.getGeneratedKeys()) {
                if(generatedKeys.next()) {
                    entity.setId(generatedKeys.getLong(1));
                } else {
                    throw new SQLException("Setting person.id failed, no ID contained.");
                }
            }

            return result > 0;
        } catch (SQLException throwables) {
            System.err.println("Failed to create new person.");
            throwables.printStackTrace();
            return false;
        }
    }

    @Override
    public boolean delete(long identity) {
        String deleteSql = "DELETE FROM "+TABLE_NAME+" WHERE ID = ?";
        try(Connection connection = createConnection();
        PreparedStatement preparedStatement = connection.prepareStatement(deleteSql)) {
            preparedStatement.setLong(1, identity);

            int result = preparedStatement.executeUpdate();

            // check if something has been deleted
            return result > 0;
        } catch (SQLException throwables) {
            System.err.println("Failed to remove person with id = "+identity);
            throwables.printStackTrace();
            return false;
        }
    }

    @Override
    public boolean update(Person entity) {
        // similar to create
        String updateSql = "UPDATE "+TABLE_NAME+" SET FIRSTNAME=?, LASTNAME=?, CITY=?, ZIP=?, ADDRESS=?, TEL=? WHERE ID=?";
        try(Connection connection = createConnection();
        PreparedStatement preparedStatement = connection.prepareStatement(updateSql)) {
            // again, set all the parameters
            preparedStatement.setString(1, entity.getFirstName());
            preparedStatement.setString(2, entity.getLastName());
            preparedStatement.setString(3, entity.getCity());
            preparedStatement.setLong(4, entity.getZip());
            preparedStatement.setString(5, entity.getAddress());
            preparedStatement.setString(6, entity.getTel());
            preparedStatement.setLong(7, entity.getId());

            // but this time execute an update and check how many rows have been altered
            int result = preparedStatement.executeUpdate();
            return result > 0;
        } catch (SQLException throwables) {
            System.err.println("Failed to update person with id = "+entity.getId());
            throwables.printStackTrace();
            return false;
        }
    }
}
