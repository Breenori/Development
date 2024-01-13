package at.fhhagenberg.xml4.drugbank.logic;

import java.io.Writer;
import java.util.*;

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

import at.fhhagenberg.xml4.drugbank.domain.DrugTarget;
import org.w3c.dom.Document;

import at.fhhagenberg.xml4.drugbank.domain.Drug;
import org.w3c.dom.Element;

public class TargetReporGenerator {

	public void generateTargetReport(Collection<Drug> drugs, Writer outputWriter) throws TargetReporGeneratorException {
		try {
			Document reportDocument = newDocumentBuilder().newDocument();

			Map<String, Integer> targetMap = new HashMap<>();
			Set<DrugTarget> targetSet = new HashSet<>();

			for(Drug drug : drugs) {
				for(DrugTarget drugTarget : drug.getTargets()) {
					String currentAccession = drugTarget.getTargetEntity().getAccession();
					if(!targetMap.containsKey(currentAccession)) {
						targetMap.put(currentAccession,1);
						targetSet.add(drugTarget);
					} else {
						targetMap.computeIfPresent(currentAccession, (k,v) -> v + 1);
					}
				}
			}


			Element root = reportDocument.createElement("targets");
			for(DrugTarget drugTarget : targetSet) {
				Element target = reportDocument.createElement("target");
				target.setAttribute("id", drugTarget.getTargetEntity().getAccession());

				Element name = reportDocument.createElement("name");
				name.setTextContent(drugTarget.getTargetEntity().getName());
				Element organism = reportDocument.createElement("organism");
				organism.setTextContent(drugTarget.getTargetEntity().getOrganism());
				Element noDrugs = reportDocument.createElement("number-of-drugs");
				noDrugs.setTextContent(targetMap.get(drugTarget.getTargetEntity().getAccession()).toString());

				target.appendChild(name);
				target.appendChild(organism);
				target.appendChild(noDrugs);

				root.appendChild(target);
			}

			reportDocument.appendChild(root);
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
