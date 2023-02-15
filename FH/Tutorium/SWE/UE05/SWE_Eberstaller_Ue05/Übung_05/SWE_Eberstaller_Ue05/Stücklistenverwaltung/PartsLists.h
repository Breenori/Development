#ifndef parts_lists_h
#define parts_lists_h

#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;

namespace PartsLists {


	class Storable { // Interface
	public:
		virtual ~Storable(); //virtual destructor
		virtual void store(std::ostream &ofs)=0; // pure virtual function
		virtual void load(std::istream &in)=0;
	};

	class Part {
	private:
		std::string name;
	public:
		Part(std::string name); // Default constructor
		~Part(); // Destructor
		std::string get_name();
		void set_name(std::string& name);
		bool equals(Part o);	
		virtual vector<Part*> getParts();

	};

	class CompositePart:public Part, Storable { // multiple inheritance
		// CompositePart is derived from class Part and (abstact) class Storable
	private:
		vector<Part*> parts; 
	public:
		CompositePart(std::string name); // Default Constructor
		~CompositePart(); // Destructor		
		void addPart(Part* p);
		vector<Part*> getParts(); //returns parts
		void store(std::ostream& ofs); 
		void print(Part* p, int level, std::ostream& out);
		CompositePart* parse(std::vector<std::tuple<int, std::string>>& data, int& start, int end, int level,  CompositePart* root);
		void load(std::istream& in);		
	};

};




#endif