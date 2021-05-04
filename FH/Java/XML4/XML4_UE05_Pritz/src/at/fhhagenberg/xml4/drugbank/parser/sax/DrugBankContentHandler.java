package at.fhhagenberg.xml4.drugbank.parser.sax;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import at.fhhagenberg.xml4.drugbank.domain.Drug;
import at.fhhagenberg.xml4.drugbank.domain.Product;
import at.fhhagenberg.xml4.drugbank.domain.Type;
import at.fhhagenberg.xml4.drugbank.parser.ParserException;

public class DrugBankContentHandler extends DefaultHandler {

	private Consumer<Drug> drugConsumer;

	private List<String> path = new ArrayList<String>();
	private StringBuilder characterBuffer = null;
	private boolean captureCharacters = false;

	private Drug currentDrug = null;
	private Boolean currentDrugAccessionPrimary = false;

	private Product currentProduct = null;
	private Boolean currentProductOverTheCounter = null;

	public DrugBankContentHandler(Consumer<Drug> drugConsumer) {
		this.drugConsumer = drugConsumer;
	}

	@Override
	public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
		path.add(qName);
		try {
			process(attributes, true);
		} catch (ParserException e) {
			throw new SAXException(e);
		}
	}

	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {
		try {
			process(null, false);
		} catch (ParserException e) {
			throw new SAXException(e);
		}
		path.remove(path.size() - 1);
	}

	@Override
	public void characters(char[] ch, int start, int length) throws SAXException {
		if (captureCharacters) {
			characterBuffer.append(ch, start, length);
		}
	}

	private void process(Attributes attributes, boolean start) throws ParserException {
		if (checkPath("drugbank", "drug")) {
			handleDrug(attributes, start);
		} else if (checkPath("drugbank", "drug", "drugbank-id")) {
			handleDrugAccession(attributes, start);
		} else if (checkPath("drugbank", "drug", "name")) {
			handleDrugName(attributes, start);
		} else if (checkPath("drugbank", "drug", "atc-code")) {
			handleDrugATC(attributes, start);
		} else if (checkPath("drugbank", "drug", "group")) {
			handleDrugGroup(attributes, start);
		} else if (checkPath("drugbank", "drug", "description")) {
			handleDrugDesc(attributes, start);
		} else if (checkPath("drugbank", "drug", "indication")) {
			handleDrugIndication(attributes, start);
		} else if (checkPath("drugbank", "drug", "synonym")) {
			handleDrugSynonym(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product" })) {
			handleProduct(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product", "name" })) {
			handleProductName(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product", "dosage-form" })) {
			handleProductDosageForm(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product", "over-the-counter" })) {
			handleProductOverTheCounter(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "target" })) {
			handleProductOverTheCounter(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "target", "id" })) {
			handleProductOverTheCounter(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "target", "id" })) {
			handleProductOverTheCounter(attributes, start);
		}

		// TODO remaining properties
	}

	private void handleDrug(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			if (currentDrug == null) {
				currentDrug = new Drug();
				currentDrug.setType(handleDrugTypeAttribute(attributes));
			} else {
				throw new InvalidStateException();
			}
		} else {
			if (currentDrug != null) {
				drugConsumer.accept(currentDrug);
			} else {
				throw new InvalidStateException();
			}

			currentDrug = null;
		}
	}

	private Type handleDrugTypeAttribute(Attributes attributes) throws ParserException {
		String value = attributes.getValue("type");
		switch (value) {
		case "biotech":
			return Type.BIOTECH;
		case "small molecule":
			return Type.SMALL_MOLECULE;
		default:
			throw new ParserException(String.format("drug type value %s not known", value));
		}
	}

	private void handleDrugAccession(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
			if (attributes.getValue("primary") != null && Boolean.parseBoolean(attributes.getValue("primary"))) {
				currentDrugAccessionPrimary = true;
			} else {
				currentDrugAccessionPrimary = false;
			}
		} else {
			String value = getCharacters();
			setCaptureCharacters(false);
			if(currentDrug == null) {
				throw new InvalidStateException();
			}
			
			if (currentDrugAccessionPrimary.booleanValue()) {
				if (currentDrug.getAccession() == null) {
					currentDrug.setAccession(value);
				} else {
					throw new InvalidStateException("primary accession for current drug has already been set");
				}
			} else {
				currentDrug.addSecondaryAccessions(value);
			}

			currentDrugAccessionPrimary = null;
		}
	}

	private void handleProduct(Attributes attributes, boolean start) throws InvalidStateException {
		if (start) {
			if (currentProduct == null) {
				currentProduct = new Product();
			} else {
				throw new InvalidStateException();
			}
		} else {
			if (currentProductOverTheCounter.booleanValue()) {
				currentDrug.addOverTheCounterProduct(currentProduct);
			} else {
				currentDrug.addPrescriptionProduct(currentProduct);
			}

			currentProduct = null;
			currentProductOverTheCounter = null;
		}
	}

	private void handleProductName(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String name = getCharacters();
			setCaptureCharacters(false);
			if (currentProduct != null && currentProduct.getName() == null) {
				currentProduct.setName(name);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleProductOverTheCounter(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String value = getCharacters();
			setCaptureCharacters(false);
			if (currentProductOverTheCounter == null) {
				currentProductOverTheCounter = Boolean.parseBoolean(value);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private String getCharacters() {
		return characterBuffer.toString().trim();
	}

	private void setCaptureCharacters(boolean active) {
		captureCharacters = active;
		if (captureCharacters) {
			characterBuffer = new StringBuilder();
		} else {
			characterBuffer = null;
		}
	}

	private boolean checkPath(String... expectedPath) {
		if (path.size() != expectedPath.length) {
			return false;
		}

		for (int i = path.size() - 1; i >= 0; --i) {
			if (!path.get(i).equals(expectedPath[i])) {
				return false;
			}
		}

		return true;
	}
}
