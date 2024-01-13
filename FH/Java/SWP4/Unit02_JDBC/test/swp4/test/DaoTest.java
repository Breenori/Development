package swp4.test;


import org.testng.Assert;
import org.testng.annotations.*;
import swp4.jdbc.dao.Dao;
import swp4.jdbc.dao.impl.EmployeeDaoJdbc;
import swp4.jdbc.domain.Employee;
import swp4.jdbc.util.ScriptRunner;

import java.time.LocalDate;
import java.util.List;

@Test
public class DaoTest {

    private static final String CONNECTION_STR = "jdbc:derby://localhost:1527/swp4;user=user;password=user";

    @BeforeClass
    public void setup() {
        System.out.println("-------------- Setup ------------------");
        ScriptRunner.runSqlScript("resources/create_db.sql", CONNECTION_STR);
    }

    @BeforeMethod
    public void setupmethod() {
        System.out.println("-------------setup method---------------");
    }

    @Test
    public void testCreate() {
        // GIVEN
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("--------- testCreate ---------");
        Employee employee = new Employee("John", "Doe", LocalDate.of(1984, 1, 2));
        // WHEN
        boolean result = employeeDao.create(employee);
        // THEN
        Assert.assertNotNull(employee.getId());
        Assert.assertEquals(employee.getFirstName(), "John");
        Assert.assertEquals(employee.getLastName(), "Doe");
        Assert.assertEquals((long) employee.getId(), 1L);
        System.out.println(employee);
    }

    // DONT BUILD UNITTESTS LIKES THIS
    @Ignore
    @Test
    public void testCreateFalse() {
        // GIVEN
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("--------- testCreateFalse ---------");
        Employee employee = new Employee("John", "Doe", LocalDate.of(1984, 1, 2));
        // WHEN
        boolean result = employeeDao.create(employee);
        // THEN
        // bad structure because of missing asserts
    }

    // usually unitTests should be standalone (not depend, and implement behaviour inside)
    // to make it easier: make dependencies:
    @Test(dependsOnMethods = {"testCreate"})
    public void testReadAll() {
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("--------- testReadAll ---------");
        List<Employee> employeeList = employeeDao.readAll();
        Assert.assertNotNull(employeeList);
        Assert.assertEquals(employeeList.size(), 1);

        for(Employee employee : employeeList) {
            System.out.println(employee);
        }
    }


    @Test(dependsOnMethods = {"testCreate"})
    public void testReadForIdentity() {
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("---------- testReadForIdentity ----------");
        Employee employee = employeeDao.readForIdentity(1L);
        Assert.assertNotNull(employee);
        System.out.println(employee);
    }

    @Test(dependsOnMethods = {"testCreate"})
    public void testUpdate() {
        // GIVEN
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("---------testUpdate-------------");
        Employee employee = new Employee("Why", "Doe", LocalDate.of(1984, 1, 2));
        employee.setId(1L);
        // WHEN
        boolean result = employeeDao.update(employee);
        // THEN
        Assert.assertTrue(result);
        System.out.println(employee);
    }

    @Test(dependsOnMethods = {"testUpdate","testCreate"})
    public void testDelete() {
        Dao<Employee> employeeDao = new EmployeeDaoJdbc();
        System.out.println("-------------testDelete-------------");
        boolean result = employeeDao.delete(1L);
        Assert.assertTrue(result);
    }

    @AfterMethod
    public void afterMethod() {
        System.out.println("------------ after method ---------");
    }

    @AfterClass
    public void tearDown() {
        System.out.println("------------ end ---------------");
    }

}
