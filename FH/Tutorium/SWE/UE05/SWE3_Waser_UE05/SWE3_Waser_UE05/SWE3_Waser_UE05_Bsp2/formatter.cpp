#include "formatter.h"

void SetFormatter::printParts(Part* p) {
	//clear map
	partCounts.clear();
	//Count parts
	CompositePart* compP = dynamic_cast<CompositePart*>(p);
	if (compP != nullptr) {
		vector<Part*>parts = compP->getParts();
		for (auto it = parts.begin(); it != parts.end(); ++it)
			countParts(*it);
	}
	cout << p->getName();
	//iterate through counted parts
	map<string, int>::iterator it;
	for (it = partCounts.begin(); it != partCounts.end(); ++it) {
		cout << "\n\t" << (*it).second << "\t" << (*it).first;
	}

}
void SetFormatter::countParts(Part* p) {
	//check if p is a part or a composite part
	CompositePart* compP = dynamic_cast<CompositePart*>(p);
	if (compP != nullptr) {
		//if it is a composite part call count parts for its parts
		vector<Part*>parts = compP->getParts();
		for (auto it = parts.begin(); it != parts.end(); ++it)
			countParts(*it);
	}
	else {
		//only count if it is a composite parte
		if (partCounts.count(p->getName()) > 0)
			partCounts[p->getName()]++;
		else
			partCounts[p->getName()] = 1;
	}


}
void HierarchyFormatter::printPartsRec(Part* p, int const level) const {
	//print indents
	for (int i(0); i < level; ++i)
		cout << "\t";
	//print part
	cout << p->getName();
	cout << "\n";
	//call printParts for every part p consists of if it is a composite part
	//check if p is a composite part
	CompositePart* compP  = dynamic_cast<CompositePart*>(p);
	if (compP != nullptr) {
		vector<Part*>parts = compP->getParts();
		for (auto it = parts.begin(); it != parts.end(); ++it)
			printPartsRec(*it, level + 1);
	}
}void HierarchyFormatter::printParts(Part* p) {
	printPartsRec(p);
}