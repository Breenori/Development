#include "PartsLists.h"

using PartsLists::Storable;
using PartsLists::Part;
using PartsLists::CompositePart;
using std::string;

Storable::~Storable() {

}



Part::Part(std::string name) { // Default Constructor
	this->name = name;
}

Part::~Part() { // Destructor

}

std::string Part::get_name() {
	return name;
}

void Part::set_name(std::string& name)
{
	this->name = name;
}

bool Part::equals(Part o) {
	return name == o.get_name();
}

vector<Part*> Part::getParts()
{
	return vector<Part*>();
}




CompositePart::CompositePart(std::string name):Part(name) { // Default Constructor

}

CompositePart::~CompositePart() { // Destructor

}

void CompositePart::addPart(Part* p) {
	this->parts.push_back(p);
}

vector<Part*> CompositePart::getParts() {
	return this->parts;
}




void CompositePart::store(std::ostream& os) {
	this->print(this, 0, os);
}

void CompositePart::print(Part* p, int level, std::ostream& out)
{
	std::string padding = std::string(level, '\t'); // padding is a string with the number of tabs in the current level
	out << padding << p->get_name() << std::endl;
	for (size_t i = 0; i < p->getParts().size(); i++)
	{
		Part* sub = p->getParts().at(i);
		if (sub->getParts().size() > 0) //if there are more parts -> level deeper
			print(sub, level + 1, out); //recursive
		else // if it does not go one level deeper 
			out << padding << "\t" << sub->get_name() << std::endl; 
	}
}

CompositePart* CompositePart::parse(std::vector<std::tuple<int, std::string>>& data, int& current, int end,
	int level,  CompositePart* root) {

	CompositePart* old_value = root; 
	while (current < end) { // recursion call		

		auto t = data.at(current); 
		int current_level = std::get<0>(t);
		if (current_level <= level) {
			// reached end of compositepart -> one level lower
			// e.g. sitzfläche -> end of hierachy -> returns 
			current--; //current element in list - 1
			return root;
		}
		if (current_level == level+1) {
			// if element is one level deeper
			// e.g. bein 
			old_value = new CompositePart(std::get<1>(t));
			root->addPart(old_value); 		
		}
		else if (current_level == level+2) {
			// if element is another level deeper 
			this->parse(data, current, end, level + 1, old_value); // recursion call
			// -> everytime a new composite parts begins
		}

		current++;
		
	}
	return old_value;


}

void CompositePart::load(std::istream& in) {
	this->parts.clear(); // clear all sub parts
	std::string line;
	int current_level;

	std::getline(in, line); // reads first line
	this->set_name(line);
	// convert to 
	std::vector<std::tuple<int, std::string>> data;	// tupple <level, name>
	while (std::getline(in, line)) { // reads the rest 
		int current_level = std::count(line.begin(), line.end(), '\t'); // counts the tabs
		line.erase(0, current_level); // deletes tabs from string 
		data.push_back({ current_level, line }); // saves current level and name in tupple
	}
	int current = 0;
	this->parse(data, current, data.size(), 0, this);
	
}
	

