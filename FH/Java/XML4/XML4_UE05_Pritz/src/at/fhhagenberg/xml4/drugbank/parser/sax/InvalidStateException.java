package at.fhhagenberg.xml4.drugbank.parser.sax;

import at.fhhagenberg.xml4.drugbank.parser.ParserException;

public class InvalidStateException extends ParserException {

	private static final long serialVersionUID = 1L;

	public InvalidStateException() {
		super();
	}

	public InvalidStateException(String message, Throwable cause,
			boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

	public InvalidStateException(String message, Throwable cause) {
		super(message, cause);
	}

	public InvalidStateException(String message) {
		super(message);
	}

	public InvalidStateException(Throwable cause) {
		super(cause);
	}

}
