#ifndef FORMATTER_H
#define FORMATTER_H

#include "part.h"
#include <iostream>
#include <map>

using PartsLists::Part;
using PartsLists::CompositePart;
using std::cout;
using std::map;

//abstract class
class Formatter {
public:
	//dynamically bound destructor since there is a dynamically bound method
	virtual ~Formatter() {};
	//pure virtual function
	virtual void printParts(Part* p) = 0;
};

class SetFormatter : public Formatter {
private:
	map<string, int> partCounts;
	void countParts(Part* p);
public:
	void printParts(Part* p) override;
};

class HierarchyFormatter : public Formatter {
private:
	void printPartsRec(Part* p, int const level = 0) const;
public:
	void printParts(Part* p) override;
};
#endif // !FORMATTER_H
