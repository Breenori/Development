#include "Stücklistenverwaltung.h"
using namespace std;
using namespace PartsLists;

Part::Part() {
	name = "no name";
}

Part::~Part() {

}

Part::Part(string const& name) {
	this->name = name;
}


string Part::get_name() {
	return name;
}

bool Part::equals(Part const& o) {
	return this->name == o.name;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/



CompositePart::CompositePart(std::string const& name): Part(name) {
	
}

CompositePart::~CompositePart() {

}

void CompositePart::add_part(Part p) {
	parts_vec.push_back(&p);
}

std::vector<Part*> CompositePart::getParts() {
	return parts_vec;;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/



void SetFormatter::print_parts(Part& p) const {
	cout << p.get_name() << endl;
	CompositePart* cp = dynamic_cast<CompositePart*>(&p);
	if (cp != nullptr) {
		for (Part* part : cp->getParts()) {
			cout << part->get_name() << endl;
		}
	}
}

void HierarchyFormatter::print_parts(Part& p) const {
	cout << p.get_name() << endl;
	CompositePart* cp = dynamic_cast<CompositePart*>(&p);
	if (cp != nullptr) {
		size_t counter = 0;
		for (Part* part : cp->getParts()) {
			if (p.equals(*part)) {
				++counter;
			}
			else {
				cout << part->get_name() << counter << "times" << endl;
				counter = 0;
			}
		}
	}
}




