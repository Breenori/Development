#include "part.h"

void PartsLists::Part::store() {
	// calling recursive function
	store_rec(this);
}

void PartsLists::Part::store_rec(PartsLists::Part* p) {
	// saving the parts in a vector
	part_list.push_back(p->getName());

	PartsLists::CompositePart* cp = dynamic_cast<PartsLists::CompositePart*>(p);

	// recursion to get to all parts that are needed for the composite parts
	if (cp != nullptr) {
		std::vector< PartsLists::Part*> parts = cp->getParts();
		for (size_t i{ 0 }; i < parts.size(); ++i) {
			store_rec(parts[i]);
		}
	}
}

void PartsLists::Part::load() {
	// output of the list, that was stored before
	for (size_t i{ 0 }; i < part_list.size(); ++i) {
		std::cout << part_list[i] << "\n";
	}
}