package swp4.ue05.part1.logic.impl;

import swp4.ue05.part1.jdbc.dao.DaoFactory;
import swp4.ue05.part1.jdbc.dao.PersonDao;
import swp4.ue05.part1.jdbc.dao.impl.PersonDaoJdbc;
import swp4.ue05.part1.logic.PersonLogic;
import swp4.ue05.part1.ui.model.PersonModel;

public class PersonLogicImpl implements PersonLogic {

    private PersonDao personDao = DaoFactory.createPersonDao();

    @Override
    public boolean savePerson(PersonModel model) {
        // insert only if model and currentPerson aren't NULL
        return model != null && model.getCurrentPerson() != null && personDao.create(model.getCurrentPerson());
    }

    @Override
    public PersonModel readAllPersons(PersonModel model) {
        return new PersonModel(model.getCurrentPerson(), personDao.readAll());
    }

    @Override
    public boolean deletePerson(PersonModel model) {
        return model != null && model.getCurrentPerson() != null && personDao.delete(model.getCurrentPerson().getId());
    }

    @Override
    public PersonModel updatePerson(PersonModel model) {
        if(personDao.update(model.getCurrentPerson())) {
            return new PersonModel(personDao.readForIdentity(model.getCurrentPerson().getId()), model.getPersons());
        }
        return null;
    }
}
