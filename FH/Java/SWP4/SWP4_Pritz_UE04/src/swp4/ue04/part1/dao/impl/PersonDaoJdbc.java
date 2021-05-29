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
            PreparedStatement statement = connection.prepareStatement(selectSql)) {
            statement.setLong(1, identity);
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()) {
                long id = resultSet.getLong(1);
                String firstName = resultSet.getString(2);
                String lastName = resultSet.getString(3);
                String city = resultSet.getString(4);
                long zip = resultSet.getLong(5);
                String address = resultSet.getString(6);
                String tel = resultSet.getString(7);

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
        String createSql = "INSERT INTO "+TABLE_NAME+"(firstname, lastname, city, zip, address, tel) VALUES(?, ?, ?, ?, ?, ?)";
        PreparedStatement ps = null;
        try {
            Connection connection = createConnection();
            ps = connection.prepareStatement(createSql, Statement.RETURN_GENERATED_KEYS);
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.setString(3, entity.getCity());
            ps.setLong(4, entity.getZip());
            ps.setString(5, entity.getAddress());
            ps.setString(6, entity.getTel());

            int result = ps.executeUpdate();

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

            return result > 0;
        } catch (SQLException throwables) {
            System.err.println("Failed to remove person with id = "+identity);
            throwables.printStackTrace();
            return false;
        }
    }

    @Override
    public boolean update(Person entity) {
        String updateSql = "UPDATE "+TABLE_NAME+" SET FIRSTNAME=?, LASTNAME=?, CITY=?, ZIP=?, ADDRESS=?, TEL=? WHERE ID=?";
        try(Connection connection = createConnection();
        PreparedStatement preparedStatement = connection.prepareStatement(updateSql)) {
            preparedStatement.setString(1, entity.getFirstName());
            preparedStatement.setString(2, entity.getLastName());
            preparedStatement.setString(3, entity.getCity());
            preparedStatement.setLong(4, entity.getZip());
            preparedStatement.setString(5, entity.getAddress());
            preparedStatement.setString(6, entity.getTel());
            preparedStatement.setLong(7, entity.getId());

            int result = preparedStatement.executeUpdate();
            return result > 0;
        } catch (SQLException throwables) {
            System.err.println("Failed to update person with id = "+entity.getId());
            throwables.printStackTrace();
            return false;
        }
    }
}
