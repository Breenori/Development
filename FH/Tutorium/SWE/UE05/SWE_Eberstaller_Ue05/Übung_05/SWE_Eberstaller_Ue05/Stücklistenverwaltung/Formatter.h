#ifndef formatter_h
#define formatter_h

#include "PartsLists.h"
#include <iostream>
#include <map>

using PartsLists::Part;
using PartsLists::CompositePart;

namespace formatters {

	class Formatter { //abstract class
	public:
		virtual ~Formatter();
		virtual void PrintParts(Part* p) = 0; // pure virtual function		
		// = 0 because the method will be implemented in the derived classes and not in this class
	};

	class SetFormatter:public Formatter {
	public:
		SetFormatter(); // constructor
		~SetFormatter(); // destructor
		void CountParts(std::map<std::string, int>* counter, Part* p);		
		void PrintParts(Part* p); //dont need override here because the methode is not implemented in base class (Formatter)
	};

	class HierachyFormatter:public Formatter {
	public:
		HierachyFormatter(); //constructor
		~HierachyFormatter(); //destructor
		void PrintParts(Part* p); //dont need override here because the methode is not implemented in base class (Formatter)
	};

};



#endif

