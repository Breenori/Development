package swp4.ue05.part1.jdbc.dao;


import swp4.ue05.part1.jdbc.dao.impl.PersonDaoJdbc;

public class DaoFactory {
    public static PersonDao createPersonDao() { return new PersonDaoJdbc(); }
}
