package swp4.ue05.part1.logic;

import swp4.ue05.part1.ui.model.PersonModel;

public interface PersonLogic {
    boolean savePerson(PersonModel model);
    PersonModel readAllPersons(PersonModel model);
    boolean deletePerson(PersonModel model);
    PersonModel updatePerson(PersonModel model);
}
