package swp4.jdbc.dao;


import java.sql.SQLOutput;
import java.util.List;


public interface Dao<T>  {
    T readForIdentity(Long identity);
    List<T> readAll();
    boolean create(T entity);

    boolean delete(long identity);

    boolean update(T entity);
}
