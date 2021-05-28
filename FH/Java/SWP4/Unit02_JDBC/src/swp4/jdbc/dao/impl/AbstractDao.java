package swp4.jdbc.dao.impl;

import swp4.jdbc.dao.Dao;

import java.lang.reflect.InvocationTargetException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public abstract class AbstractDao<T> implements Dao<T> {

    protected final String DATABASE_URL = "jdbc:derby://localhost:1527/swp4;user=user;password=user";
    private Connection connection;

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
