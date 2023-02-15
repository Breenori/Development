#include "PartsList.hpp"

using namespace PartsList;

// Erstelle eine Sitzgarnitur
void test1() {
	CompositePart sitzgarnitur("Sitzgarnitur");

	// Erstelle zwei Sessel und füge sie der Sitzgarnitur hinzu
	CompositePart* sessel1 = new CompositePart("Sessel");
	CompositePart* sessel2 = new CompositePart("Sessel");
	sitzgarnitur.addPart(sessel1);
	sitzgarnitur.addPart(sessel2);
	// Erstelle vier kleine Beine und füge sie den Sesseln hinzu
	Part* bein1 = new Part("Bein (klein)");
	Part* bein2 = new Part("Bein (klein)");
	Part* bein3 = new Part("Bein (klein)");
	Part* bein4 = new Part("Bein (klein)");
	sessel1->addPart(bein1);
	sessel1->addPart(bein2);
	sessel1->addPart(bein3);
	sessel1->addPart(bein4);
	sessel2->addPart(bein1);
	sessel2->addPart(bein2);
	sessel2->addPart(bein3);
	sessel2->addPart(bein4);

	// Erstelle eine Sitzfläche und füge sie den Sesseln hinzu
	Part* sitzflaeche = new Part("Sitzfläche");
	sessel1->addPart(sitzflaeche);
	sessel2->addPart(sitzflaeche);

	// Erstelle einen Tisch und füge ihn der Sitzgarnitur hinzu
	CompositePart* tisch = new CompositePart("Tisch");
	sitzgarnitur.addPart(tisch);

	// Erstelle vier grosse Beine und füge sie dem Tisch hinzu
	Part* bein5 = new Part("Bein (gross)");
	Part* bein6 = new Part("Bein (gross)");
	Part* bein7 = new Part("Bein (gross)");
	Part* bein8 = new Part("Bein (gross)");
	tisch->addPart(bein5);
	tisch->addPart(bein6);
	tisch->addPart(bein7);
	tisch->addPart(bein8);

	// Erstelle eine Tischfläche und füge sie dem Tisch hinzu
	Part* tischflaeche = new Part("Tischfläche");
	tisch->addPart(tischflaeche);

	// Erstelle einen SetFormatter und einen HierarchyFormatter
	SetFormatter set_formatter;
	HierarchyFormatter hierarchy_formatter;

	// Gib die Stückliste mit dem SetFormatter aus
	std::cout << "SetFormatter:\n";
	set_formatter.printParts(sitzgarnitur);

	// Gib die Stückliste mit dem HierarchyFormatter aus
	std::cout << "\nHierarchyFormatter:\n";
	hierarchy_formatter.printParts(sitzgarnitur);


	// Öffne eine Datei zum Schreiben
	std::ofstream out("sitzgruppe.txt");

	// Speichere die Sitzgruppe in der Datei
	sitzgarnitur.store(out);

	// Schliesse die Datei
	out.close();

	// Öffne die Datei zum Lesen
	std::ifstream in("sitzgruppe.txt");

	// Lade die Sitzgruppe aus der Datei
	auto* sitzgarnitur_kopie = CompositePart::load(in);

	// Schliesse die Datei
	in.close();

	hierarchy_formatter.printParts(*sitzgarnitur_kopie);
	set_formatter.printParts(*sitzgarnitur_kopie);
}


int main() {
	test1();
	return 0;
}