package at.fhhagenberg.util;

import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpressionException;

import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class XPathUtil {

	public static String extractString(Node node, String expression, XPath xPath)
			throws XPathExpressionException {
		return ((String) xPath.evaluate(expression, node, XPathConstants.STRING)).trim();
	}

	public static void processNodeList(Node node, String xPathExpression, NodeConsumer consumer,
			XPath xPath) throws XPathExpressionException {
		processNodeList((NodeList) xPath.evaluate(xPathExpression, node, XPathConstants.NODESET),
				consumer);
	}

	private static void processNodeList(NodeList nl, NodeConsumer consumer)
			throws XPathExpressionException {
		for (int i = 0; i < nl.getLength(); ++i) {
			consumer.accept(nl.item(i));
		}
	}

	@FunctionalInterface
	public static interface NodeConsumer {
		public void accept(Node node) throws XPathExpressionException;
	}
}
