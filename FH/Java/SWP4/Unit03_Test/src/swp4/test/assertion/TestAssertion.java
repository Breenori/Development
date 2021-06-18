package swp4.test.assertion;

import swp4.test.exception.TestAssertionFailedException;

public class TestAssertion {

    public static void assertTrue(boolean exp) {
        if(!exp) {
            throw new TestAssertionFailedException();
        }
    }
}
