#include "part.h"

using PartsLists::Part;
using PartsLists::CompositePart;

//Implementation of Part
//default name
Part::Part() : name("unknown part") {}
Part::Part(string const& _name) : name(_name) {}
Part::Part(istream& in) {
	load(in);
}
//just return name
string& Part::getName() {
	return name;
}
bool Part::equals(Part const& o) {
	//since a part only has a name -> compare names (case sensitiv)
	return name == o.name;
}
ostream& Part::store(ostream& out) {
	//just write name
	if (out.good())
		out << name;
	return out;
}
istream& Part::load(istream& in) {
	//read one whole line and set as name
	if (in.good())
		std::getline(in, name);
	return in;
}



//Implementation of Compositepart
CompositePart::CompositePart() {}
//set name in constructor 
CompositePart::CompositePart(string const& _name) {
	getName() = _name;
}
CompositePart::CompositePart(istream& in) {
	load(in);
}
void CompositePart::addPart(Part& p) {
	//add part to parts vector
	parts.push_back(&p);
}
vector<Part*> CompositePart::getParts() {
	//return parts vector
	return parts;
}
ostream& CompositePart::store(ostream& out) {
	if (out.good()) {
		//write name
		out << getName();
		//write parts too if there are any
		if (parts.size() > 0) {
			out << "{";
			for (size_t i(0); i < parts.size(); ++i) {
				out << "\n";
				parts[i]->store(out);
			}
			out << "\n}";
		}
	}
	return out;
}
istream& CompositePart::load(istream& in) {
	if (in.good()) {
		Part* part = load_rec(in);
		if (part == nullptr) {
			getName() = "unkown";
		}
		else {
			//set name
			getName() = part->getName();
			//if part is composite part -> copy parts list
			CompositePart* comp_part = dynamic_cast<CompositePart*>(part);
			if (comp_part != nullptr) {
				vector<Part*> to_copy = comp_part->getParts();

				//add each part to the current parts list
				for (vector<Part*>::iterator it = to_copy.begin(); it != to_copy.end(); ++it)
					parts.push_back(*it);
			}
		}
	}
	return in;
}
Part* CompositePart::load_rec(istream& in) {
	if (in.good()) {
		//count brackets
		bool not_closed(true);
		string curr_line;
		std::getline(in, curr_line);
		//check if theres is a '}' if there is, return nullptr
		size_t pos = curr_line.find('}');
		if (pos != string::npos)
			return nullptr;
		//check if there is a '{' and use everything before as name
		pos = curr_line.find('{');
		//if '{' has been found it is a composite part
		if (pos != string::npos) {
			CompositePart* curr_comp = new CompositePart(curr_line.substr(0, pos));
			//read all children -> read until open brackets is at 0
			do {
				//call load for the children and add to parts vector, stop if it is a nullprt
				Part* curr_child = load_rec(in);
				if (curr_child != nullptr)
					curr_comp->parts.push_back(curr_child);
				else
					not_closed = false;
			} while (not_closed);

			return curr_comp;
		}
		//otherwise it is just a part
		else {
			//return part
			Part* p = new Part(curr_line);
			return p;
		}
	}
	return nullptr;
}