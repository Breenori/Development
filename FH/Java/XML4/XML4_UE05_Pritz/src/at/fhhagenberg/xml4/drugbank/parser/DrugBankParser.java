package at.fhhagenberg.xml4.drugbank.parser;

import java.io.File;
import java.util.function.Consumer;

import at.fhhagenberg.xml4.drugbank.domain.Drug;

public interface DrugBankParser {

	public void parse(File file, Consumer<Drug> drugConsumer) throws ParserException;
	
}
