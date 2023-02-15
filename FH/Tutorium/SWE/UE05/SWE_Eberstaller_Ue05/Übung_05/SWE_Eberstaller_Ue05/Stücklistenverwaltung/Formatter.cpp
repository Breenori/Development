#include "Formatter.h"
#include <iostream>

using formatters::Formatter;
using formatters::HierachyFormatter;
using formatters::SetFormatter;

Formatter::~Formatter(){ // destructor

}


SetFormatter::SetFormatter() { //constructor

}

SetFormatter::~SetFormatter() { //destructor

}

void SetFormatter::CountParts(std::map<std::string, int>* counter, Part* p)
{
	if (p->getParts().size() <= 0) {
		// test if value exists in map
		if (counter->find(p->get_name()) != counter->end()) { 
			// if a part with this name already exists -> counter + 
			counter->at(p->get_name()) = counter->at(p->get_name()) + 1;
		} 
		else { // if its ah new part ist added to the map
			counter->insert({ p->get_name(), 1 });
		}

	}
	else {	// next part
		for (size_t i = 0; i < p->getParts().size(); i++)
		{
			CountParts(counter, p->getParts().at(i)); // recursive function 
		}
	}

}


void SetFormatter::PrintParts(Part* p){
	std::map<std::string, int> counter; // counts name of part and number of occurences

	if (p->getParts().size() <= 0) {
		std::cout << "Invalid part was given to formatter - has no sub parts" << std::endl;
		return;
	}

	this->CountParts(&counter, p);
	std::cout << p->get_name() << std::endl;
	for (std::map<std::string, int>::iterator it = counter.begin(); it != counter.end(); ++it) { //iterates map 
		std::cout << "\t\t" << it->second << " " << it->first << std::endl;
	}


}

HierachyFormatter::HierachyFormatter() { // constructor

}

HierachyFormatter::~HierachyFormatter(){ // destructor

}


void HierachyFormatter::PrintParts(Part* p) {
	CompositePart* part = dynamic_cast<CompositePart*>(p);
	// dynamic cast -> need the methods from composite part
	/*if (part == nullptr) {
		std::cout << "Invalid part was given to formatter - has no sub parts" << std::endl;
		return;
	}*/

	if (p->getParts().size() <= 0) {
		std::cout << "Invalid part was given to formatter - has no sub parts" << std::endl;
		return;
	}

	part->print(part, 0, std::cout);
	
}
