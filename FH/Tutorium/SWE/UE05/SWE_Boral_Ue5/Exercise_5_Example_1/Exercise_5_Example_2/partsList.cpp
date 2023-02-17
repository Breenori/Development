#include "partsList.h"

using PartsLists::Part;
using PartsLists::CompositePart;

bool typeFormatter(Formatter* f);

Part::Part() {
	name = " ";
}

Part::Part(std::string const& na) {
	name = na;
}

Part::Part(Part const& other) {
	name = other.name;
}

std::string Part::getName() const {
	return name;
}

bool Part::equal(Part const& other) {
	return name == other.getName();
}

CompositePart::CompositePart(std::string const& na) {
	Part *p= new Part(na);
	parts.push_back(p);
}

CompositePart::CompositePart(std::vector<Part*> other) {
	parts = other;
}

CompositePart::~CompositePart() {
	for (int i = 0; i < parts.size(); i++) {
		auto ptr = *parts[i];
		delete parts[i];
	}
}

void CompositePart::addPart(Part& p) {
	Part* pp = new Part(p);
	parts.push_back(pp);
}

std::vector<Part*> CompositePart::getParts() {
	return parts;
}

void CompositePart::printForTest(std::ostream& out) {
	for (int i = 0; i < parts.size(); ++i) {
		out << (parts[i]->getName());
		if (i < parts.size() - 1) {
			out << ", ";
		}
	}
	out << "\n";
}

Formatter::Formatter(PartsLists::Part p) {
	Part* pp = new Part(p);
	part.push_back(pp);
}

Formatter::Formatter(std::vector< PartsLists::Part*> src) {
	part = src;
}

Formatter::~Formatter() {
	for (int i = 0; i < part.size(); ++i) {
		part.erase(part.begin() + i);
	}
}

HierarchyFormatter::HierarchyFormatter(std::vector< PartsLists::Part*> src) {
	part = src;
}

void HierarchyFormatter::printParts(PartsLists::Part p, std::ostream& out) {
	for (int i = 0; i < part.size(); ++i) {
		out << part[i]->getName() << ";\n";
	}
	out << "\n";
}

SetFormatter::SetFormatter(std::vector< PartsLists::Part*> src) {
	part = src;
}

void SetFormatter::printParts(PartsLists::Part p, std::ostream& out) {
	int count = 0;
	for (int i = 0; i < part.size(); ++i) {
		if (p.equal(*(part[i]))) {
			++count;
		}
	}
	out << count << " " << p.getName() << ";\n";
}

bool Storable::store(std::vector<PartsLists::Part*> toSave,Formatter& form, std::ostream& out) {
	int i = 0;
	int counter = 0;
	if (toSave.size() != 0) {
		if (typeFormatter(&form)) {
			form.printParts(*(toSave[0]), out);
		}
		else {			
			while(i< toSave.size()) {
				//checks if the next one is the same part 
				if(toSave[i]->equal(toSave[i+1]->getName())){
					//if the counter !=0 then it already has been printed
					if (counter == 0) {
						form.printParts(*(toSave[i]), out);
					}
					//adds 2 --> current and next one is the same
					i += 2;
					++counter;
				}
				else {
					form.printParts(*(toSave[i]), out);
					++i;
					counter = 0;
				}
			}
		}
		return true;
	}
	//toSave is empty
	return false;
}

std::vector<PartsLists::Part*> Storable::load(std::istream& in) {
	std::string name;
	Part *p;
	std::vector<Part*> tmp;
	while (in.good()) {
		in >> name;
		p = new Part(name);
		tmp.push_back(p);
	}
	return tmp;
}

//returns if derived class HierarchyFormatter
bool typeFormatter(Formatter* f) {
	HierarchyFormatter* h = dynamic_cast<HierarchyFormatter*>(f);
	if (h == nullptr) {
		return false;
	}
	return true;
}