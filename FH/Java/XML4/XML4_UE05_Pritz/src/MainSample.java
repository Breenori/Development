import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.List;

import at.fhhagenberg.xml4.drugbank.domain.Drug;
import at.fhhagenberg.xml4.drugbank.logic.TargetReporGenerator;
import at.fhhagenberg.xml4.drugbank.parser.DrugBankParser;
import at.fhhagenberg.xml4.drugbank.parser.dom.DrugBankParserDom;
import at.fhhagenberg.xml4.drugbank.parser.sax.DrugBankParserSax;

public class MainSample {

	enum ParserType {
		DOM, SAX
	}

	private static ParserType parserType;
	private static File drugBankFile;
	private static OutputStream outputStream;

	
	public static void main(String[] args) throws Exception {
		parseArgs(args);
		DrugBankParser parser = parserType == ParserType.DOM ? new DrugBankParserDom(true)
				: new DrugBankParserSax();
		List<Drug> drugs = new ArrayList<>();
		parser.parse(drugBankFile, drugs::add);
		System.out.println(String.format("#drugs: %s", drugs.size()));
		TargetReporGenerator reportGenerator = new TargetReporGenerator();
		try (Writer writer = new OutputStreamWriter(outputStream != null ? outputStream
				: System.out)) {
			reportGenerator.generateTargetReport(drugs, writer);
		}
	}

	private static void parseArgs(String[] args) throws Exception {
		try {
			if (args.length < 2) {
				throw new Exception();
			}

			parserType = ParserType.valueOf(args[0].toUpperCase());
			drugBankFile = new File(args[1]);
			if (args.length == 3) {
				outputStream = new FileOutputStream(args[2]);
			}

		} catch (Exception e) {
			System.err
					.println("USAGE: DrugBank.jar parserType drugBank.xml [targetReportOutputFile]\nparserType values: dom, sax");
			throw e;
		}
	}

}
