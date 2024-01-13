#if ! defined FORMATTER_H
#define FORMATTER_H

#include "part.h"
#include <iostream>
#include <map>

// abstract class
class Formatter {
public:
	// implemented in the specialized classes
	virtual void printParts(PartsLists::Part& p) const = 0;
	virtual ~Formatter(){}
};



class SetFormatter : public Formatter {
public:
	void printParts(PartsLists::Part& p) const override;

	// default constructor -> calls constructor of abstract class
	SetFormatter() :Formatter() {}
private:
	void count_parts_rec(std::map<std::string, int>& parts_count, PartsLists::Part* p)const;
};



class HierarchyFormatter : public Formatter {
public:
	void printParts(PartsLists::Part& p) const override;

	// default constructor -> calls constructor of abstract class
	HierarchyFormatter() :Formatter() {}
private:
	void print_parts_rec(PartsLists::Part* p, int const indent)const;
};



#endif