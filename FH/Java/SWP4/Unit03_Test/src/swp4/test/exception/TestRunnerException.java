package swp4.test.exception;

public class TestRunnerException extends Exception {

    public TestRunnerException(String message) {
        super(message);
    }

    public TestRunnerException(String message, Throwable throwable) {
        super(message, throwable);
    }

}
