package swp4.ue05.part1.jdbc.domain;

public class Person {
    private Long id;
    private String firstName;
    private String lastName;
    private String city;
    private Long zip;
    private String address;
    private String tel;

    public Person(String firstName, String lastName, String city, Long zip, String address, String tel) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.city = city;
        this.zip = zip;
        this.address = address;
        this.tel = tel;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getCity() {
        return city;
    }

    public Long getZip() {
        return zip;
    }

    public String getAddress() {
        return address;
    }

    public String getTel() {
        return tel;
    }

    @Override
    public String toString() {
        return "Person{" +
                "id=" + id +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", city='" + city + '\'' +
                ", zip=" + zip +
                ", address='" + address + '\'' +
                ", tel='" + tel + '\'' +
                '}';
    }
}
