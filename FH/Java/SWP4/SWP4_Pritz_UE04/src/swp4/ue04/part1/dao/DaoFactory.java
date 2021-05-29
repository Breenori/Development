package swp4.ue04.part1.dao;


import swp4.ue04.part1.dao.impl.PersonDaoJdbc;

public class DaoFactory {
    public static PersonDao createPersonDao() { return new PersonDaoJdbc(); }
}
