package swp4.test;

import swp4.test.annotation.TestClass;
import swp4.test.annotation.TestMethod;
import swp4.test.assertion.TestAssertion;
import swp4.test.exception.TestRunnerException;

@TestClass(createdBy = "Pritzi", description = "Sample test class")
public class TestRunnerTest {
    @TestMethod
    public void testSuccessful() {
        System.out.println("Executing testSuccessful");
    }

    @TestMethod
    public void testFailure() {
        System.out.println("Executing testFailure");
        throw new RuntimeException();
    }

    @TestMethod(enabled = false)
    public void testIgnore() {
        System.out.println("Executing testIgnore");
    }

    @TestMethod
    public void testAddition() {
        // GIVEN
        int x = 1;
        int y = 41;
        // WHEN
        int sum = x + y;
        // THEN
        TestAssertion.assertTrue(sum == 42);
    }

    public static void main(String[] args) throws TestRunnerException {
        TestRunner.run(TestRunnerTest.class, String.class, TestRunnerTest.class);
    }
}
