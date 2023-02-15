#include "testing.h"
#include "formatter.h"

#include <iostream>
#include <fstream>

using PartsLists::CompositePart;
using PartsLists::Part;

void testPart() {
	std::cout << "Test Part:\n";
	Part tablet("tabletop");
	std::cout << tablet.getName();
	std::cout << "\n----------------------------\n\n";

	Part tableleg("table leg");
	CompositePart table("table");
	std::cout << "Test CompositePart:\n";
	std::cout << table.getName();

	table.addPart(&tablet);
	table.addPart(&tableleg);
	table.addPart(&tableleg);
	std::cout << "\n";
	CompositePart sofaset("Sofaset");
	sofaset.addPart(&table);
	CompositePart chair("sofachair");
	sofaset.addPart(&chair);
	Part leg("leg");
	chair.addPart(&leg);
	std::cout << "\n----------------------------\n\n";
	std::cout << "\n\nTest SetFormatter:\n";
	HierarchyFormatter hier;
	SetFormatter set;
	set.printParts(table);
	std::cout << "\n------\n";
	set.printParts(sofaset);
	std::cout << "\n----------------------------\n\n";
	std::cout << "\nTest HierarchyFormatter:\n";
	hier.printParts(sofaset);
	
	//std::ofstream out ("output.txt");
	////out.open();
	//sofaset.store(out);
	//out.close();

	std::ifstream in("output.txt");
	PartsLists::CompositePart test("test");
	test.load(in);
	std::cout << "\nTest load\n";
	hier.printParts(test);

	//set.store(&sofaset);
}

void testequals() {
	std::cout << "Testing method equals():\n";
	Part leg1("Tischbein");
	Part leg2("Stuhlbein");
	Part leg3("Tischbein");
	std::cout << "Test part 1: \n";
	std::cout << "Input parameters: leg1 = " << leg1.getName() << " leg2 = " << leg2.getName() << '\n';
	if (leg1.equals(leg2)) {
		std::cout << leg1.getName() << " is equal to " << leg2.getName() << '\n';
	}
	else {
		std::cout << leg1.getName() << " is not equal to " << leg2.getName() << '\n';
	}

	std::cout << "\n-----------------------------------\n";
	std::cout << "Test part 2: \n";
	std::cout << "Input parameters: leg1 = " << leg1.getName() << " leg3 = " << leg3.getName() << '\n';
	if (leg1.equals(leg3)) {
		std::cout << leg1.getName() << " is equal to " << leg3.getName() << '\n';
	}
	else {
		std::cout << leg1.getName() << " is not equal to " << leg3.getName() << '\n';
	}
}

void testCompositePart() {
	std::cout << "Testing CompositePart List and HierarchyFormatter:\n";
	CompositePart livingspace("Wohnkueche");
	CompositePart sitzecke("Sitzecke");
	CompositePart table("Tisch");
	Part leg("Tischbein");
	Part tabletop("Tischplatte");
	table.addPart(&leg);
	table.addPart(&leg);
	table.addPart(&leg);
	table.addPart(&leg);
	table.addPart(&tabletop);
	sitzecke.addPart(&table);
	livingspace.addPart(&sitzecke);
	CompositePart kitchen("Kueche");
	Part microwave("Mikrowelle");
	kitchen.addPart(&microwave);
	Part fridge("Kuehlschrank");
	kitchen.addPart(&fridge);
	CompositePart island("Kuecheninsel");
	Part oven("Herd");
	CompositePart storage("Moebelstueck");
	Part drawer("Lade");
	storage.addPart(&drawer);
	storage.addPart(&drawer);
	storage.addPart(&drawer);
	island.addPart(&oven);
	island.addPart(&storage);
	kitchen.addPart(&island);
	livingspace.addPart(&kitchen);

	HierarchyFormatter hierarchy;
	std::cout << "Print with HierarchyFormatter:\n";
	hierarchy.printParts(livingspace);

	SetFormatter set;
	std::cout << "\n\nPrint with SetFormatter:\n";
	set.printParts(livingspace);
}

void testLoadStore() {
	std::cout << "Test load and store with sofaset:\n";
	CompositePart sofaset("Sofaset");
	CompositePart table("table");
	Part leg("leg");
	Part tabletop("tabletop");
	table.addPart(&leg);
	table.addPart(&leg);
	table.addPart(&leg);
	table.addPart(&leg);
	table.addPart(&tabletop);
	CompositePart sofachair("sofachair");
	Part seat("seatcushion");
	sofachair.addPart(&seat);
	sofachair.addPart(&leg);
	sofachair.addPart(&leg);
	sofachair.addPart(&leg);
	sofachair.addPart(&leg);
	sofaset.addPart(&table);
	sofaset.addPart(&sofachair);

	std::ofstream outFile("output.txt");
	sofaset.store(outFile);
	outFile.close();
	std::cout << "Test store to file --> result see file\n";

	std::ifstream inFile("output.txt");
	CompositePart inObject("tmp");
	inObject.load(inFile);

	std::cout << "Test load from File:\n";
	HierarchyFormatter hiera;
	hiera.printParts(inObject);

}

void testEmptyFile() {
	std::ifstream inFile ("empty.txt");
	Part test1("test1");
	test1.load(inFile);
	SetFormatter set;
	set.printParts(test1);
	std::cout << "Test load from empty file. Test Oject to call load has been initialized with name test1\n";
	std::cout << test1.getName();
}