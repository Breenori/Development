#ifndef formatter_h
#define formatter_h

#include "partslists.h"
#include <iostream>
#include <map>

using PartsLists::Part;


class Formatter {

public:
	virtual void printParts(PartsLists::Part& p, std::ostream& out = std::cout) = 0;

};

class SetFormatter : public Formatter {
private:
	std::map<std::string, int> partStats;
	void getStats(PartsLists::Part& p);
public:
	virtual void printParts(PartsLists::Part& p, std::ostream& out = std::cout) override;
};

class HierarchyFormatter : public Formatter {

	void printParts(Part &p, size_t level, std::ostream& out);

public: 
	virtual void printParts(PartsLists::Part& p, std::ostream& out = std::cout) override;
};

#endif // !formatter_h
