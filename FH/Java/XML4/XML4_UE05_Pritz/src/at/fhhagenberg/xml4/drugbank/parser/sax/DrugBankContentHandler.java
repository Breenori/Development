package at.fhhagenberg.xml4.drugbank.parser.sax;

import java.lang.annotation.Target;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.function.Consumer;

import at.fhhagenberg.xml4.drugbank.domain.*;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

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

	private DrugTarget currentDrugTarget = null;
	private TargetEntity currentTargetEntity = null;

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
		} else if (checkPath("drugbank", "drug", "atc-codes", "atc-code")) {
			handleDrugATC(attributes, start);
		} else if (checkPath("drugbank", "drug", "groups", "group")) {
			handleDrugGroup(attributes, start);
		} else if (checkPath("drugbank", "drug", "description")) {
			handleDrugDesc(attributes, start);
		} else if (checkPath("drugbank", "drug", "indication")) {
			handleDrugIndication(attributes, start);
		} else if (checkPath("drugbank", "drug", "synonyms", "synonym")) {
			handleDrugSynonym(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product" })) {
			handleProduct(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product", "name" })) {
			handleProductName(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product", "dosage-form" })) {
			handleProductDosageForm(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "products", "product", "over-the-counter" })) {
			handleProductOverTheCounter(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "targets", "target" })) {
			handleTarget(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "targets", "target", "id" })) {
			handleTargetId(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "targets", "target", "name" })) {
			handleTargetName(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "targets", "target", "organism" })) {
			handleTargetOrganism(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "targets", "target", "actions", "action" })) {
			handleTargetAction(attributes, start);
		} else if (checkPath(new String[] { "drugbank", "drug", "targets", "target", "known-action" })) {
			handleTargetKnownAction(attributes, start);
		}

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

	private void handleDrugName(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String name = getCharacters();
			setCaptureCharacters(false);
			if (currentDrug != null && currentDrug.getName() == null) {
				currentDrug.setName(name);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleDrugATC(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			String atc = attributes.getValue("code");
			if (currentDrug != null) {
				currentDrug.addAtcCode(atc);
			} else {
				throw new InvalidStateException();
			}
		}

	}

	private Group handleDrugGroupConversion(String group) throws ParserException {
		switch (group.toLowerCase()) {
			case "approved":
				return Group.APPROVED;
			case "experimental":
				return Group.EXPERIMENTAL;
			case "illicit":
				return Group.ILLICIT;
			case "withdrawn":
				return Group.WITHDRAWN;
			case "nutraceutical":
				return Group.NUTRACEUTICAL;
			case "investigational":
				return Group.INVESTIGATIONAL;
			default:
				throw new ParserException(String.format("drug type value %s not known", group));
		}
	}

	private void handleDrugGroup(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String groupString = getCharacters();
			setCaptureCharacters(false);

			if (currentDrug != null) {
				currentDrug.addGroup(handleDrugGroupConversion(groupString));
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleDrugDesc(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String desc = getCharacters();
			setCaptureCharacters(false);
			if (currentDrug != null && currentDrug.getDescription() == null) {
				currentDrug.setDescription(desc);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleDrugIndication(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String indication = getCharacters();
			setCaptureCharacters(false);
			if (currentDrug != null && currentDrug.getIndication() == null) {
				currentDrug.setIndication(indication);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleDrugSynonym(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String synonym = getCharacters();
			setCaptureCharacters(false);
			if (currentDrug != null) {
				currentDrug.addSynonym(synonym);
			} else {
				throw new InvalidStateException();
			}
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

	private void handleProductDosageForm(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String dosageForm = getCharacters();
			setCaptureCharacters(false);
			if (currentProduct != null && currentProduct.getDosageForm() == null) {
				currentProduct.setDosageForm(dosageForm);
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

	private void handleTarget(Attributes attributes, boolean start) throws InvalidStateException {
		if (start) {
			if (currentDrugTarget == null) {
				currentDrugTarget = new DrugTarget();
				currentTargetEntity = new TargetEntity();
			} else {
				throw new InvalidStateException();
			}
		} else {
			currentDrugTarget.setTargetEntity(currentTargetEntity);
			currentDrugTarget.setDrug(currentDrug);
			currentDrug.addDrugTarget(currentDrugTarget);

			currentDrugTarget = null;
		}
	}

	private void handleTargetId(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String id = getCharacters();
			setCaptureCharacters(false);
			if (currentTargetEntity != null && currentTargetEntity.getAccession()==null) {
				currentTargetEntity.setAccession(id);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleTargetName(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String name = getCharacters();
			setCaptureCharacters(false);
			if (currentTargetEntity != null && currentTargetEntity.getName()==null) {
				currentTargetEntity.setName(name);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleTargetOrganism(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String organism = getCharacters();
			setCaptureCharacters(false);
			if (currentTargetEntity != null && currentTargetEntity.getOrganism()==null) {
				currentTargetEntity.setOrganism(organism);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleTargetAction(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			String action = getCharacters();
			setCaptureCharacters(false);
			if (currentDrugTarget != null) {
				currentDrugTarget.addAction(action);
			} else {
				throw new InvalidStateException();
			}
		}
	}

	private void handleTargetKnownAction(Attributes attributes, boolean start) throws ParserException {
		if (start) {
			setCaptureCharacters(true);
		} else {
			boolean known_action = getCharacters() == "y" ? true : false;
			setCaptureCharacters(false);
			if (currentDrugTarget != null) {
				currentDrugTarget.setTargetWithKnownAction(known_action);
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
