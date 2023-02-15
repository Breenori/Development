#include "partslists.h"
#include "formatter.h"


PartsLists::Part::Part(std::string name) {
	this->name = name;
}

std::string PartsLists::Part::getName() const {
	return this->name;
}

void PartsLists::Part::setName(std::string& name) {
	this->name = name;
}

bool PartsLists::Part::equals(Part o) const {
	return this->getName() == o.getName();
}

PartsLists::CompositePart::CompositePart(std::string name) : Part(name){
	// delegate to base class and call constructor
}

void PartsLists::CompositePart::addPart(Part * p) {
	this->parts.push_back(p);
}


std::vector<PartsLists::Part*> PartsLists::CompositePart::getParts() {
	return this->parts;
}

std::istream& PartsLists::Part::load(std::istream& in) {
	if (in.good()) {
		std::string tmp;
		std::string partName;
		getline(in, tmp);
		if (tmp[0] == '>') {
			getline(in, partName);
			this->setName(partName);
		}
	}
	return in;
}

std::istream& PartsLists::CompositePart::load(std::istream& in) {
	if (in.good()) {
		std::vector<std::string> overview;
		size_t i{ 0 };
		std::string tmp;

		// read list into vector
		while (!in.eof()) {
			getline(in, tmp);
			if (tmp[0] == '>') {
				getline(in, tmp);
			}
			overview.push_back(tmp);
		}

		PartsLists::CompositePart* cp = nullptr;

		for (size_t k{ 0 }; k < overview.size()-1; ++k) {
			size_t l{ 3 };
			// get number of whitespace bevor part name
			while (overview[k][l] == ' ') {
				++l;
			}
			std::string partName = overview[k].substr(l, overview[k].size() - l);
			if (overview[k][0] == 'C') {
				if (k == 0) {
					this->setName(partName);
				}
				else if (k ==1) {
					// if first Part after SetName is CompositePart
					cp = new PartsLists::CompositePart(partName);
				}
				else {
					// for all other CompositeParts
					this->addPart(cp);
					cp = new PartsLists::CompositePart(partName);
				}
			}
			// add last CompositePart to Object
			else if (overview[k][0] == 'P') {
				cp->addPart(new PartsLists::Part(partName));
			}
		}
		this->addPart(cp);
	}
	return in;
}

std::ostream& PartsLists::Part::store(std::ostream& out) {
	if (out.good()) {
		out << ">Partslist for " << this->getName() << '\n';
		// call HierarchyFormatter to save to File
		HierarchyFormatter hierarchy;
		hierarchy.printParts(*this, out);
	}
	return out;
}