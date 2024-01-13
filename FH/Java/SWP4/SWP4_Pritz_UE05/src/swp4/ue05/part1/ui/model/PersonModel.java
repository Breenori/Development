package swp4.ue05.part1.ui.model;

import swp4.ue05.part1.jdbc.domain.Person;

import java.util.ArrayList;
import java.util.List;

public class PersonModel {
    private Person currentPerson;
    private List<Person> persons;

    public PersonModel(Person currentPerson, List<Person> persons) {
        this.currentPerson = currentPerson;
        this.persons = persons;
    }

    public PersonModel() {
        currentPerson = null;
        persons = new ArrayList<>();
    }

    public Person getCurrentPerson() {
        return currentPerson;
    }

    public void setCurrentPerson(Person currentPerson) {
        this.currentPerson = currentPerson;
    }

    public List<Person> getPersons() {
        return persons;
    }

    public void setPersons(List<Person> persons) {
        this.persons = persons;
    }
}
