#include "Formatter.h"
#include "PartsLists.h"
#include <iostream>
#include <fstream>

using formatters::SetFormatter;
using formatters::HierachyFormatter;



void test_set_formatter_invalid_part() {
	CompositePart sessel("Sessel");
	SetFormatter set_fmt;
	set_fmt.PrintParts(&sessel);
}

void test_set_formatter_sessel() {
	CompositePart thing("Sitzgarnitur");

	CompositePart sessel("Sessel");
	Part bein_klein("Bein (klein)");
	Part sitzfleache("Sitzflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	thing.addPart(&sessel);
	thing.addPart(&sessel);


	SetFormatter set_fmt;

	set_fmt.PrintParts(&sessel);
}

void test_set_formatter_Sitzgarnitur() {
	CompositePart thing("Sitzgarnitur");
	CompositePart sessel("Sessel");
	CompositePart tisch("Tisch");
	Part bein_klein("Bein (klein)");
	Part bein_big("Bein (gross)");
	Part sitzfleache("Sitzflaeche");
	Part tischfleache("Tischflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&tischfleache);

	thing.addPart(&sessel);
	thing.addPart(&sessel);
	thing.addPart(&tisch);

	SetFormatter set_fmt;

	set_fmt.PrintParts(&thing);
}

void test_hierachy_formatter_invalid_part() {
	CompositePart sessel("Sessel");
	HierachyFormatter h_fmt;
	h_fmt.PrintParts(&sessel);
}

void test_hierachy_formatter_sessel() {
	CompositePart thing("Sitzgarnitur");

	CompositePart sessel("Sessel");
	Part bein_klein("Bein (klein)");
	Part sitzfleache("Sitzflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	thing.addPart(&sessel);
	thing.addPart(&sessel);

	HierachyFormatter h_fmt;

	h_fmt.PrintParts(&sessel);
}

void test_hierachy_formatter_Sitzgarnitur() {
	CompositePart thing("Sitzgarnitur");
	CompositePart sessel("Sessel");
	CompositePart tisch("Tisch");
	Part bein_klein("Bein (klein)");
	Part bein_big("Bein (gross)");
	Part sitzfleache("Sitzflaeche");
	Part tischfleache("Tischflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&tischfleache);

	thing.addPart(&sessel);
	thing.addPart(&sessel);
	thing.addPart(&tisch);

	HierachyFormatter h_fmt;

	h_fmt.PrintParts(&thing);
}

void test_load() {
	
	CompositePart thing("Sitzgarnitur");
	CompositePart sessel("Sessel");
	CompositePart tisch("Tisch");
	Part bein_klein("Bein (klein)");
	Part bein_big("Bein (gross)");
	Part sitzfleache("Sitzflaeche");
	Part tischfleache("Tischflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&tischfleache);

	thing.addPart(&sessel);
	thing.addPart(&sessel);
	thing.addPart(&tisch);

	std::ifstream y("test_load.txt");
	thing.load(y);
	y.close();

	HierachyFormatter h_fmt;

	h_fmt.PrintParts(&thing);
}

void test_store() {
	CompositePart thing("Sitzgarnitur");
	CompositePart sessel("Sessel");
	CompositePart tisch("Tisch");
	Part bein_klein("Bein (klein)");
	Part bein_big("Bein (gross)");
	Part sitzfleache("Sitzflaeche");
	Part tischfleache("Tischflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&bein_big);
	tisch.addPart(&tischfleache);

	thing.addPart(&sessel);
	thing.addPart(&sessel);
	thing.addPart(&tisch);

	std::ofstream x("test_store.txt");
	thing.store(x);
	x.close();

}

void test_part_constructor() {
	Part p("Bein");
	std::cout << p.get_name() << std::endl;
}

void test_part_get_name() {
	Part bein_klein("Bein (klein)");
	std::string s =  bein_klein.get_name();
	std::cout << s << std::endl;
}


void test_part_equals() {
	Part bein_1("Bein (klein)");
	Part bein_2("Bein (klein)");
	Part flaeche_1("Sitzflaeche");
	Part flaeche_2("Tischflaeche");

	std::cout << bein_1.get_name() << " and " <<bein_2.get_name() << std::endl;
	if (bein_1.equals(bein_2)) {
		std::cout << "Equal!" << std::endl;
	}
	else {
		std::cout << "Not Equal!" << std::endl;
	}

	std::cout << flaeche_1.get_name() << " and " << flaeche_2.get_name() << std::endl;
	if (flaeche_1.equals(flaeche_2)) {
		std::cout << "Equal!" << std::endl;
	}
	else {
		std::cout << "Not Equal!" << std::endl;
	}

}


void test_CompositePart_constructor() {
	CompositePart sessel("Sessel");
	std::cout << sessel.get_name() << std::endl;

}

void test_CompositePart_addPart() {
	CompositePart sessel("Sessel");

	Part bein_klein("Bein (klein)");
	Part sitzfleache("Sitzflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	HierachyFormatter h_fmt;

	h_fmt.PrintParts(&sessel);
}


void test_CompositePart_get_parts() {
	CompositePart sessel("Sessel");

	Part bein_klein("Bein (klein)");
	Part sitzfleache("Sitzflaeche");

	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&bein_klein);
	sessel.addPart(&sitzfleache);

	vector<Part*> parts;
	parts = sessel.getParts();

	std::cout << "Parts of " << sessel.get_name() << std::endl;
	for (int i = 0; i < parts.size(); ++i) {
		std::cout << parts[i]->get_name() << std::endl;
	}

}



int main() {

	
	std::cout << "Testing formatters" << std::endl;
	std::cout << "Testing set formatter with invalid part" << std::endl;
	test_set_formatter_invalid_part();

	std::cout << "Testing set formatter with sessel" << std::endl;
	test_set_formatter_sessel();
	
	std::cout << "Testing set formatter with Sitzgarnitur" << std::endl;
	test_set_formatter_Sitzgarnitur();

	std::cout << "Testing hierachy formatter with invalid part" << std::endl;
	test_hierachy_formatter_invalid_part();
	std::cout << "Testing hierachy formatter with sessel" << std::endl;
	test_hierachy_formatter_sessel();
	std::cout << "Testing hierachy formatter with Sitzgarnitur" << std::endl;
	test_hierachy_formatter_Sitzgarnitur();

	std::cout << "Testing storable" << std::endl;
	std::cout << "Testing load (+ Hierachy Formatter for printing)" << std::endl;
	test_load();
	std::cout << "Testing store" << std::endl;
	test_store();
	

	std::cout << "Testing class part" << std::endl;
	std::cout << "Testing constructor" << std::endl;
	test_part_constructor();
	std::cout << "Testing get_name()" << std::endl;
	test_part_get_name();
	std::cout << "Testing equals()" << std::endl;
	test_part_equals();

	std::cout << "Testing constructor" << std::endl;
	test_CompositePart_constructor();
	std::cout << "Testing class CompositePart" << std::endl;
	std::cout << "Testing get_parts()" << std::endl;
	test_CompositePart_get_parts();
	std::cout << "Testing addPart()" << std::endl;
	test_CompositePart_addPart();

}
