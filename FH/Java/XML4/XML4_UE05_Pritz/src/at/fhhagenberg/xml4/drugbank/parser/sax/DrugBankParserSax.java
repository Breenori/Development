package at.fhhagenberg.xml4.drugbank.parser.sax;

import java.io.File;
import java.io.IOException;
import java.util.function.Consumer;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.SAXException;

import at.fhhagenberg.xml4.drugbank.domain.Drug;
import at.fhhagenberg.xml4.drugbank.parser.DrugBankParser;
import at.fhhagenberg.xml4.drugbank.parser.ParserException;

public class DrugBankParserSax implements DrugBankParser {

	@Override
	public void parse(File file, Consumer<Drug> drugConsumer) throws ParserException {
		try {
			newSaxParser().parse(file, new DrugBankContentHandler(drugConsumer));
		} catch (SAXException | IOException | ParserConfigurationException e) {
			throw new ParserException(e);
		}
	}

	private SAXParser newSaxParser() throws ParserConfigurationException, SAXException {
		return SAXParserFactory.newInstance().newSAXParser();
	}

}
