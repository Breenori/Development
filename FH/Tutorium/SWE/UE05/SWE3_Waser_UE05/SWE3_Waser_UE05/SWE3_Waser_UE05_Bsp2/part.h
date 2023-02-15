#ifndef PARTS_H
#define PARTS_H

#include<string>
#include<vector>
#include"i_storable.h"

using std::string;
using std::vector;

namespace PartsLists {
	class Part : public IStorable {
	private:
		virtual istream& load(istream& in) override;
		string name;
	public:
		Part();
		Part(string const& _name);
		Part(istream& in);
		//virtual destructor so that there is a vtable 
		virtual ~Part() {};
		string& getName();
		bool equals(Part const& o);
		virtual ostream& store(ostream& out) override;		 
	};

	class CompositePart : public Part {
	private:
		vector<Part*> parts;
		istream& load(istream& in) override;
		Part* load_rec(istream& in);
	public:
		CompositePart();
		CompositePart(string const& _name);
		CompositePart(istream& in);
		void addPart(Part& p);
		vector<Part*> getParts();
		ostream& store(ostream& out) override;
	};
}



#endif // !PARTS_H
