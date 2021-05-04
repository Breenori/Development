package at.fhhagenberg.xml4.drugbank.logic;

import java.io.Writer;
import java.util.Collection;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;

import at.fhhagenberg.xml4.drugbank.domain.Drug;

public class TargetReporGenerator {

	public void generateTargetReport(Collection<Drug> drugs, Writer outputWriter) throws TargetReporGeneratorException {
		try {
			Document reportDocument = newDocumentBuilder().newDocument();
			//TODO generate report
			reportDocument.appendChild(reportDocument.createElement("dummy"));
			serializeDocument(reportDocument, outputWriter);
		} catch (TransformerFactoryConfigurationError | TransformerException | ParserConfigurationException e) {
			throw new TargetReporGeneratorException(e);
		}
	}
	
	private void serializeDocument(Document document, Writer outputWriter) throws TransformerException {
		Transformer transformer = newTransformer();
		transformer.transform(new DOMSource(document), new StreamResult(outputWriter));
	}

	private DocumentBuilder newDocumentBuilder() throws ParserConfigurationException {
		return DocumentBuilderFactory.newInstance().newDocumentBuilder();
	}

	private Transformer newTransformer()
			throws TransformerConfigurationException, TransformerFactoryConfigurationError {
		Transformer transformer = TransformerFactory.newInstance().newTransformer();
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		return transformer;
	}

}
