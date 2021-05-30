package swp4.ue04.part1.dao.impl;

import swp4.ue04.part1.dao.Dao;

import java.lang.reflect.InvocationTargetException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public abstract class AbstractDao<T> implements Dao<T> {
    // set database connection string
    protected final String DATABASE_URL = "jdbc:derby://localhost:1527/swp4;user=user;password=user";
    private Connection connection;

    // Check if driver is installed
    static {
        try {
            Class.forName("org.apache.derby.jdbc.ClientDriver").getConstructor(new Class[]{}).newInstance();
        } catch (ClassNotFoundException
                | InvocationTargetException
                | InstantiationException
                | IllegalAccessException
                | NoSuchMethodException e) {
            e.printStackTrace();
        }
    }

    // returns a new connection using the drivermanager
    protected Connection createConnection() throws SQLException {
        connection = DriverManager.getConnection(DATABASE_URL);
        return connection;
    }

    protected void closeConnection() {
        try {
            if(connection != null) {
                connection.close();
                connection = null;
            }
        } catch(SQLException e) {
            e.printStackTrace();
        }
    }
}
