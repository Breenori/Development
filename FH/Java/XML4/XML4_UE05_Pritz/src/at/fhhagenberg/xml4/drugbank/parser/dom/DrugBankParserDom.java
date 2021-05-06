package at.fhhagenberg.xml4.drugbank.parser.dom;

import static at.fhhagenberg.util.XPathUtil.extractString;
import static at.fhhagenberg.util.XPathUtil.processNodeList;

import java.io.File;
import java.io.IOException;
import java.util.function.Consumer;

import javax.swing.text.html.parser.Parser;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import at.fhhagenberg.xml4.drugbank.domain.*;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;

import at.fhhagenberg.util.CheckedExceptionWrapper;
import at.fhhagenberg.util.Pair;
import at.fhhagenberg.xml4.drugbank.parser.DrugBankParser;
import at.fhhagenberg.xml4.drugbank.parser.ParserException;

public class DrugBankParserDom implements DrugBankParser {

	boolean chunking;
	private XPath xPath;

	public DrugBankParserDom() {
		chunking = false;
	}

	public DrugBankParserDom(boolean chunking) {
		this.chunking = chunking;
	}

	public void parse(File file, Consumer<Drug> drugConsumer) throws ParserException {
		try {
			xPath = newXPath();
			Document document = newDocumentBuilder().parse(file);
			processNodeList(document, C.DRUGS, n -> {
				try {
					Drug drug = processDrug(n);
					drugConsumer.accept(drug);
				} catch (ParserException e) {
					throw new CheckedExceptionWrapper(e);
				}
			}, xPath);
		} catch (CheckedExceptionWrapper e) {
			throw (ParserException) e.getCause();
		} catch (XPathExpressionException | SAXException | IOException | ParserConfigurationException e) {
			throw new ParserException(e);
		}
	}

	private Type handleDrugTypeAttribute(String typeString) throws ParserException {
		switch (typeString) {
			case "biotech":
				return Type.BIOTECH;
			case "small molecule":
				return Type.SMALL_MOLECULE;
			default:
				throw new ParserException(String.format("drug type value %s not known", typeString));
		}
	}

	static int counter = 0;
	private Drug processDrug(Node drugNode) throws XPathExpressionException, ParserException {
		Drug drug = new Drug();
		addDrugType(drugNode, drug);
		addDrugAccessions(drugNode, drug);
		addDrugProducts(drugNode, drug);
		addDrugName(drugNode, drug);
		addDrugATCs(drugNode, drug);
		addDrugGroups(drugNode, drug);
		addDrugDescription(drugNode, drug);
		addDrugIndication(drugNode, drug);
		addDrugSynonyms(drugNode,drug);
		addDrugTarget(drugNode, drug);

		System.out.println("new drug "+counter++);
		return drug;
	}


	private void addDrugType(Node drugNode, Drug drug) throws XPathExpressionException, ParserException {
		drug.setType(handleDrugTypeAttribute(extractString(drugNode, C.DRUG.TYPE, xPath)));
	}

	private void addDrugAccessions(Node drugNode, Drug drug) throws XPathExpressionException, ParserException {
		addDrugAccession(drugNode, drug);

		processNodeList(drugNode, C.DRUG.SECONDARY_ACCESSIONS, n -> {
			drug.addSecondaryAccessions(extractString(n,".",xPath));
		}, xPath);
	}

	private void addDrugAccession(Node drugNode, Drug drug) throws XPathExpressionException {
		drug.setAccession(extractString(drugNode, C.DRUG.PRIMARY_ACCESSION, xPath));
	}

	private void addDrugName(Node drugNode, Drug drug) throws XPathExpressionException {
		drug.setName(extractString(drugNode, C.DRUG.NAME, xPath));
	}

	private void addDrugATCs(Node drugNode, Drug drug) throws XPathExpressionException, ParserException {
		processNodeList(drugNode, C.DRUG.ATC_CODES, n -> {
			drug.addAtcCode(n.getNodeValue());
		}, xPath);
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

	private void addDrugGroups(Node drugNode, Drug drug) throws XPathExpressionException, ParserException {
		processNodeList(drugNode, C.DRUG.GROUPS, n -> {
			drug.addGroup(handleDrugGroupConversion(extractString(n,".",xPath)));
		}, xPath);
	}

	private void addDrugProducts(Node drugNode, Drug drug) throws XPathExpressionException, ParserException {
		processNodeList(drugNode, C.DRUG.PRODUCTS, n -> {
			Pair<Product, Boolean> productInfo = processProduct(n);
			if (productInfo.getSecond()) {
				drug.addOverTheCounterProduct(productInfo.getFirst());
			} else {
				drug.addPrescriptionProduct(productInfo.getFirst());
			}
		}, xPath);
	}

	private Pair<Product, Boolean> processProduct(Node productNode) throws XPathExpressionException {
		Product product = new Product();
		boolean overTheCounter = false;
		addProductName(productNode, product);
		addProductDosageForm(productNode, product);
		overTheCounter = Boolean.parseBoolean(extractString(productNode, C.PRODUCT.OVER_THE_COUNTER, xPath));
		return new Pair<>(product, overTheCounter);
	}

	private void addProductDosageForm(Node productNode, Product product) throws XPathExpressionException {
		product.setDosageForm(extractString(productNode, C.PRODUCT.DOSAGE_FORM, xPath));
	}

	private void addProductName(Node productNode, Product product) throws XPathExpressionException {
		product.setName(extractString(productNode, C.PRODUCT.NAME, xPath));
	}

	private void addDrugDescription(Node drugNode, Drug drug) throws XPathExpressionException {
		drug.setDescription(extractString(drugNode, C.DRUG.DESCRIPTION, xPath));
	}

	private void addDrugIndication(Node drugNode, Drug drug) throws XPathExpressionException {
		drug.setIndication(extractString(drugNode, C.DRUG.INDICATION, xPath));
	}

	private void addDrugSynonyms(Node drugNode, Drug drug) throws XPathExpressionException, ParserException {
		processNodeList(drugNode, C.DRUG.SYNONYMS, n -> {
			drug.addSynonym(n.getNodeValue());
		}, xPath);
	}

	private void addDrugTarget(Node drugNode, Drug drug) throws XPathExpressionException, ParserException {
		processNodeList(drugNode, C.DRUG.TARGETS, n -> {
			DrugTarget drugTarget = processDrugTarget(n);
			drugTarget.setDrug(drug);
			drug.addDrugTarget(drugTarget);
		}, xPath);
	}

	private DrugTarget processDrugTarget(Node targetNode) throws XPathExpressionException, ParserException {
		DrugTarget drugTarget = new DrugTarget();

		addDrugTargetTargetEntity(targetNode, drugTarget);
		addDrugTargetEffects(targetNode, drugTarget);
		addDrugTargetKnownAction(targetNode, drugTarget);

		return drugTarget;
	}

	private void addDrugTargetTargetEntity(Node targetNode, DrugTarget drugTarget) throws XPathExpressionException, ParserException {
		TargetEntity targetEntity = processTargetEntity(targetNode);
		drugTarget.setTargetEntity(targetEntity);
	}

	private void addDrugTargetEffects(Node targetNode, DrugTarget drugTarget) throws XPathExpressionException, ParserException {
		processNodeList(targetNode, C.TARGET.EFFECTS, n -> {
			drugTarget.addAction(extractString(n,".",xPath));
		}, xPath);
	}

	private void addDrugTargetKnownAction(Node targetNode, DrugTarget drugTarget) throws XPathExpressionException, ParserException {
		drugTarget.setTargetWithKnownAction(extractString(targetNode, C.TARGET.KNOWN_ACTION, xPath).equals("y"));
	}

	private TargetEntity processTargetEntity(Node productNode) throws XPathExpressionException {
		TargetEntity targetEntity = new TargetEntity();
		addTargetEntityAccession(productNode, targetEntity);
		addTargetEntityName(productNode, targetEntity);
		addTargetEntityOrganism(productNode, targetEntity);

		return targetEntity;
	}

	private void addTargetEntityAccession(Node targetNode, TargetEntity targetEntity) throws XPathExpressionException {
		targetEntity.setAccession(extractString(targetNode, C.TARGET.ACCESSION, xPath));
	}

	private void addTargetEntityName(Node targetNode, TargetEntity targetEntity) throws XPathExpressionException {
		targetEntity.setName(extractString(targetNode, C.TARGET.NAME, xPath));
	}

	private void addTargetEntityOrganism(Node targetNode, TargetEntity targetEntity) throws XPathExpressionException {
		targetEntity.setOrganism(extractString(targetNode, C.TARGET.ORGANISM, xPath));
	}


	private DocumentBuilder newDocumentBuilder() throws ParserConfigurationException, SAXException {
		return DocumentBuilderFactory.newInstance().newDocumentBuilder();
	}

	private XPath newXPath() {
		return XPathFactory.newInstance().newXPath();
	}

	private interface C {

		public static final String DRUGS = "/drugbank/drug";

		public interface DRUG {
			public static final String PRIMARY_ACCESSION = "drugbank-id[@primary = \"true\"]/text()";
			public static final String SECONDARY_ACCESSIONS = "drugbank-id[not(@primary)]/text()";
			public static final String PRODUCTS = "products/product";
			public static final String NAME = "name/text()";
			public static final String ATC_CODES = "atc-codes/atc-code/@code";
			public static final String GROUPS = "groups/group";
			public static final String TYPE = "@type";
			public static final String DESCRIPTION = "description";
			public static final String INDICATION = "indication";
			public static final String SYNONYMS = "synonyms/Synonym";
			public static final String TARGETS = "targets/target";
		}

		public interface PRODUCT {
			public static final String NAME = "name";
			public static final String DOSAGE_FORM = "dosage-form";
			public static final String OVER_THE_COUNTER = "over-the-counter";
		}

		public interface TARGET {
			public static final String ACCESSION = "id";
			public static final String NAME = "name";
			public static final String ORGANISM = "organism";
			public static final String EFFECTS = "actions/action";
			public static final String KNOWN_ACTION = "known-action";
		}
	}
}
