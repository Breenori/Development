package swp4.ue05.part1.ui.view.impl;

import swp4.ue05.part1.jdbc.domain.Person;

import javax.swing.table.AbstractTableModel;
import java.util.List;

public class PersonTableModel extends AbstractTableModel {

    private List<Person> persons;
    private static final String[] COLUMN_NAMES = {"#","First Name","Last Name","City","ZIP","Address","Telephone"};

    public PersonTableModel(List<Person> persons) {
        this.persons = persons;
    }

    @Override
    public String getColumnName(int column) {
        return COLUMN_NAMES[column];
    }

    @Override
    public int getRowCount() {
        return persons != null ? persons.size() : 0;
    }

    @Override
    public int getColumnCount() {
        return COLUMN_NAMES.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        if(persons != null) {
            Person person = persons.get(rowIndex);
            if(person != null){
                switch(columnIndex) {
                    case 0:
                        return person.getId();
                    case 1:
                        return person.getFirstName();
                    case 2:
                        return person.getLastName();
                    case 3:
                        return person.getCity();
                    case 4:
                        return person.getZip();
                    case 5:
                        return person.getAddress();
                    case 6:
                        return person.getTel();
                    default:
                        return null;
                }
            }
        }
        return null;
    }
}
