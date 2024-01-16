#if ! defined PARTS_TEST_H
#define PARTS_TEST_H

#include "part.h"
#include "formatter.h"

PartsLists::CompositePart& setup() {
	static PartsLists::Part bein_klein("Bein (klein)");
	static PartsLists::Part bein_groﬂ("Bein (gross)");
	static PartsLists::Part sitzfl‰che("Sitzflaeche");
	static PartsLists::Part tischfl‰che("Tischflaeche");

	static PartsLists::CompositePart Sessel("Sessel");
	Sessel.addPart(&bein_klein);
	Sessel.addPart(&bein_klein);
	Sessel.addPart(&bein_klein);
	Sessel.addPart(&bein_klein);
	Sessel.addPart(&sitzfl‰che);


	static PartsLists::CompositePart Tisch("Tisch");
	Tisch.addPart(&bein_groﬂ);
	Tisch.addPart(&bein_groﬂ);
	Tisch.addPart(&bein_groﬂ);
	Tisch.addPart(&bein_groﬂ);
	Tisch.addPart(&tischfl‰che);


	static PartsLists::CompositePart Sitzgarnitur("Sitzgarnitur");
	Sitzgarnitur.addPart(&Sessel);
	Sitzgarnitur.addPart(&Sessel);
	Sitzgarnitur.addPart(&Tisch);

	return Sitzgarnitur;
}

void test_set() {
	SetFormatter test;
	test.printParts(setup());
}

void test_hierarchy() {
	HierarchyFormatter test;
	test.printParts(setup());
}

void store_load() {
	PartsLists::CompositePart& p = setup();
	std::cout << "load part before store: \n\n";
	p.load();
	p.store();
	std::cout << "stored part \n\n";
	std::cout << "load part after store: \n";
	p.load();
}

void problem_loop_hierarchy() {
	PartsLists::CompositePart Sessel("Sessel");
	Sessel.addPart(&Sessel);

	HierarchyFormatter test;
	test.printParts(Sessel);
}

void problem_loop_set() {
	PartsLists::CompositePart Sessel("Sessel");
	Sessel.addPart(&Sessel);

	SetFormatter test;
	test.printParts(Sessel);
}


#endif
