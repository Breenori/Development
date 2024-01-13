#include "partsList_Test.h"

using PartsLists::CompositePart;
using PartsLists::Part;

void testTable() {
	Part tp("Tischplatte");
	Part b1("Bein (gross)");
	Part b2("Bein (gross)");
	Part b3("Bein (gross)");
	Part b4("Bein (gross)");

	std::vector<Part*> p;
	p.push_back(&(tp));
	p.push_back(&(b1));
	p.push_back(&(b2));
	p.push_back(&(b3));
	p.push_back(&(b4));

	CompositePart tps(p);
	std::cout << "Tisch: ";
	tps.printForTest(std::cout);
}

void testStore() {
	Part tp("Tischplatte");
	Part b1("Bein (gross)");
	Part b2("Bein (gross)");
	Part b3("Bein (gross)");
	Part b4("Bein (gross)");

	std::vector<Part*> p;
	p.push_back(&(tp));
	p.push_back(&(b1));
	p.push_back(&(b2));
	p.push_back(&(b3));
	p.push_back(&(b4));

	std::ofstream ofs("store_table.csv");
	HierarchyFormatter hf(p);
	SetFormatter sf(p);

	Storable s;
	s.store(p,hf,ofs);

	std::ofstream ofs1("store_set_table.csv");
	s.store(p, sf, ofs1);
}

void testLoad() {
	std::vector<Part*> list;
	std::ifstream ifs("store_table.csv");
	Storable s;
	list= s.load(ifs);
	for (int i = 0; i < list.size(); ++i) {
		std::cout << list[i]->getName() << " ";
	}
}

void testHierarchy() {
	Part tp("Tischplatte");
	Part b1("Bein (gross)");
	Part b2("Bein (gross)");
	Part b3("Bein (gross)");
	Part b4("Bein (gross)");

	std::vector<Part*> p;
	p.push_back(&(tp));
	p.push_back(&(b1));
	p.push_back(&(b2));
	p.push_back(&(b3));
	p.push_back(&(b4));

	std::ofstream ofs("Table_Hierarchy_Formatter.csv");

	HierarchyFormatter hf(p);
	hf.printParts(tp, std::cout);
	hf.printParts(b1, ofs);

}

void testSet() {
	Part tp("Tischplatte");
	Part b1("Bein (gross)");
	Part b2("Bein (gross)");
	Part b3("Bein (gross)");
	Part b4("Bein (gross)");

	std::vector<Part*> p;
	p.push_back(&(tp));
	p.push_back(&(b1));
	p.push_back(&(b2));
	p.push_back(&(b3));
	p.push_back(&(b4));

	std::ofstream ofs("Table_Set_Formatter.csv");

	SetFormatter sf(p);
	sf.printParts(tp, std::cout);
	sf.printParts(b1, std::cout);
	sf.printParts(tp, ofs);
	sf.printParts(b1, ofs);
}

void testPart() {
	Part p("part");
	Part p2("equipment");

	std::cout << "The Name of the Part is " << p.getName();
	std::cout << " \n";
	if (p.equal(p)) {
		std::cout << p.getName() << " Equals " << p.getName();
	}
	std::cout << " \n";
	if (!p.equal(p2)) {
		std::cout << p.getName() << " Does Not Equal " << p2.getName();
	}
	std::cout << " \n";
	Part p3(p);
	std::cout << p3.getName() << " is a copy of " << p.getName();
}

void testCompositePart() {
	CompositePart p("Part");
	std::cout << "Konstruktor mit String: ";
	p.printForTest(std::cout);
	Part n("addedPart");
	p.addPart(n);
	std::cout << "New Part added: ";
	p.printForTest(std::cout);
	Part n_part ("new part");

	std::vector<Part*> list;
	list.push_back(&(n_part));
	list.push_back(&(n_part));
	list.push_back(&(n_part));
	CompositePart p2(list);

	std::cout << "Konstruktor mit Vektor: ";
	p2.printForTest(std::cout);

	std::vector<Part*> parts = p2.getParts();
	std::cout << "GetParts: ";
	for (int i = 0; i < parts.size(); ++i) {
		std::cout << parts[i]->getName() << " ";
	}
}