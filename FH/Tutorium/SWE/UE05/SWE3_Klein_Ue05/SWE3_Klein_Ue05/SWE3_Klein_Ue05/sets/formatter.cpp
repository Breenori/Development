#include "formatter.h"

void SetFormatter::printParts(PartsLists::Part& p) const {
	std::map<std::string, int> parts_count;

	// counts the parts and saves it in the map
	count_parts_rec(parts_count, &p);

	std::cout << p.getName() << ": \n";

	// iterating through the map to print all the parts with their corresponding count
	for (auto it = parts_count.begin(); it != parts_count.end(); it++) {
		std::cout<<"    " << it->second << " " << it->first << "\n";
	}
}

void SetFormatter::count_parts_rec(std::map<std::string, int>& parts_count, PartsLists::Part* p) const {
	PartsLists::CompositePart* cp = dynamic_cast<PartsLists::CompositePart*>(p);

	// going in recursion for composite parts
	if (cp != nullptr) {
		std::vector< PartsLists::Part*> parts = cp->getParts();
		for (size_t i{ 0 }; i < parts.size(); ++i) {

			count_parts_rec(parts_count, parts[i]);
		}
	}
	// only counting the elementary parts -> parts that aren't composite parts
	else {
		if (parts_count.count(p->getName())) {
			parts_count[p->getName()]++;
		}
		else {
			parts_count[p->getName()] = 1;
		}
	}

}

void HierarchyFormatter::printParts(PartsLists::Part& p) const {
	// calling recursive function
	print_parts_rec(&p, 0);
}

void HierarchyFormatter::print_parts_rec(PartsLists::Part* p, int const indent)const {
	// printing the indent for a nice formatted output
	for (int i{ 0 }; i < indent; ++i) {
		std::cout << "    ";
	}

	// printing the name of the current part
	std::cout << p->getName()<<"\n";


	PartsLists::CompositePart* cp = dynamic_cast<PartsLists::CompositePart*>(p);
	// going in recursion for composite parts
	if (cp != nullptr) {
		std::vector< PartsLists::Part*> parts = cp->getParts();
		for (size_t i{ 0 }; i < parts.size(); ++i) {
			print_parts_rec(parts[i], indent + 1);
		}
	}

}