package swp4.ue04.part1.test;

import org.testng.Assert;
import org.testng.annotations.*;
import swp4.ue04.part1.dao.Dao;
import swp4.ue04.part1.dao.impl.PersonDaoJdbc;
import swp4.ue04.part1.domain.Person;
import swp4.ue04.part1.util.ScriptRunner;

import java.util.ArrayList;
import java.util.List;

@Test
public class PersonDaoTest {

    private static final String CONNECTION_STR = "jdbc:derby://localhost:1527/swp4;user=user;password=user";

     @BeforeClass
     public void setup() {
         System.out.println("-------- Resetting database ---------");
         ScriptRunner.runSqlScript("sql/create_db.sql", CONNECTION_STR);
     }

     @Test
    public void testCreate() {
         // GIVEN
         Dao<Person> personDao = new PersonDaoJdbc();
         System.out.println("----------- testCreate ------------");
         Person person = new Person("Andrea", "Maschendrahtzaun", "Knallerbsenstadt", 1337L, "Zaungasse 4", "+43 123456789");

         // WHEN
         boolean result = personDao.create(person);

         // THEN
         Assert.assertNotNull(person);
         Assert.assertEquals(person.getFirstName(), "Andrea");
         Assert.assertEquals(person.getLastName(), "Maschendrahtzaun");
         Assert.assertEquals(person.getCity(), "Knallerbsenstadt");
         Assert.assertEquals((long)person.getZip(), 1337L);
         Assert.assertEquals(person.getAddress(), "Zaungasse 4");
         Assert.assertEquals(person.getTel(), "+43 123456789");
         Assert.assertEquals((long)person.getId(), 1L);

         System.out.println(person);
     }

     @Test(dependsOnMethods = {"testCreate"})
    public void testReadAll() {
         //GIVEN
         Dao<Person> personDao = new PersonDaoJdbc();
         System.out.println("----------- testReadAll ------------");

         // THEN
         List<Person> personList = personDao.readAll();

         // WHEN
         Assert.assertNotNull(personList);
         Assert.assertEquals(personList.size(), 1);

         for(Person person : personList) {
             System.out.println(person);
         }
     }

     @Test(dependsOnMethods = {"testCreate"})
    public void testReadForIdentity() {
         // GIVEN
         Dao<Person> personDao = new PersonDaoJdbc();
         System.out.println("---------- testReadForIdentity ------------");

         // WHEN
         Person person = personDao.readForIdentity(1L);

         // THEN
         Assert.assertNotNull(person);
         System.out.println(person);
     }

     @Test(dependsOnMethods = {"testCreate"})
    public void testUpdate() {
         // GIVEN
         Dao<Person> personDao = new PersonDaoJdbc();
         System.out.println("----------- testUpdate ------------");
         Person person = new Person("Peter", "Maschendrahtzaun", "Knallerbsenstadt", 1337L, "Zaungasse 4", "+43 123456789");
        person.setId(1L);

         // WHEN
         boolean result = personDao.update(person);

         // THEN
         Assert.assertTrue(result);
         System.out.println(person);
     }

     @Test(dependsOnMethods = {"testCreate", "testUpdate"})
    public void testDelete() {
         // GIVEN
         Dao<Person> personDao = new PersonDaoJdbc();
         System.out.println("----------- testDelete ------------");

         // WHEN
         boolean result = personDao.delete(1L);

         // THEN
         Assert.assertTrue(result);
     }
}
