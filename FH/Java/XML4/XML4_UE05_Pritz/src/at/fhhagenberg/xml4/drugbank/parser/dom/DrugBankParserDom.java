package at.fhhagenberg.xml4.drugbank.parser.dom;

import static at.fhhagenberg.util.XPathUtil.extractString;
import static at.fhhagenberg.util.XPathUtil.processNodeList;

import java.io.File;
import java.io.IOException;
import java.util.function.Consumer;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.xml.sax.SAXException;

import at.fhhagenberg.util.CheckedExceptionWrapper;
import at.fhhagenberg.util.Pair;
import at.fhhagenberg.xml4.drugbank.domain.Drug;
import at.fhhagenberg.xml4.drugbank.domain.Product;
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

	private Drug processDrug(Node drugNode) throws XPathExpressionException, ParserException {
		Drug drug = new Drug();
		addDrugAccessions(drugNode, drug);
		addDrugProducts(drugNode, drug);
		addDrugATCs(drugNode, drug);
		//TODO remaining properties
		return drug;
	}

	private void addDrugAccessions(Node drugNode, Drug drug) throws XPathExpressionException {
		addDrugAccession(drugNode, drug);
		//TODO secondary accessions
	}

	private void addDrugAccession(Node drugNode, Drug drug) throws XPathExpressionException {
		drug.setAccession(extractString(drugNode, C.DRUG.PRIMARY_ACCESSION, xPath));
	}

	private void addDrugName(Node drugNode, Drug drug) throws XPathExpressionException {
		drug.setName(extractString(drugNode, C.DRUG.NAME, xPath));
	}

	private void addDrugATCs(Node drugNode, Drug drug) throws XPathExpressionException {
		processNodeList(drugNode, C.DRUG.ATC_CODES, n -> {
			drug.addAtcCode(n.getNodeValue());
		}, xPath);
	}

	private void addDrugProducts(Node drugNode, Drug drug) throws XPathExpressionException {
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
		//TODO product dosage form
		overTheCounter = Boolean.parseBoolean(extractString(productNode, C.PRODUCT.OVER_THE_COUNTER, xPath));
		return new Pair<>(product, overTheCounter);
	}

	private void addProductName(Node productNode, Product product) throws XPathExpressionException {
		product.setName(extractString(productNode, C.PRODUCT.NAME, xPath));
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
			public static final String PRODUCTS = "products/product";
			public static final String NAME = "name/text()";
			public static final String ATC_CODES = "atc-codes/atc-code/@code";
			public static final String GROUPS = "groups/group";
			public static final String TYPE = "@type";
			public static final String DESCRIPTION = "description";
			public static final String INDICATION = "indication";
			public static final String SYNONYMS = "synonyms/Synonym";
		}

		public interface PRODUCT {
			public static final String NAME = "name";
			public static final String OVER_THE_COUNTER = "over-the-counter";
		}

		public interface DRUGTARGET {
			public static final String EFFECTS = "actions/action";
			public static final String KNOWN_ACTION = "known-action";
		}
	}
}
