package at.fhhagenberg.util;

public class CheckedExceptionWrapper extends RuntimeException {

	private static final long serialVersionUID = 1L;

	public CheckedExceptionWrapper(Throwable cause) {
		super(cause);
	}
	
}
