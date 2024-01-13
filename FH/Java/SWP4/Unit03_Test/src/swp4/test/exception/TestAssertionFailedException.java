package swp4.test.exception;

public class TestAssertionFailedException extends RuntimeException{ //unchecked Exception
    public static void assertTrue(boolean exp){
        if (!exp){
            throw new TestAssertionFailedException();
        }
    }
}
