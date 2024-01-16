#ifndef partsList_h
#define partsList_h

#include <string>
#include <vector>
#include <iostream>

namespace PartsLists {
	class Part {
	private:
		std::string name;

	public:
		Part();
		Part(std::string const& na);
		Part(Part const& other);
		std::string getName() const;
		bool equal(Part const& other);
	};

	class CompositePart: public Part{
	private:
		std::vector<Part*> parts;
	public:
		CompositePart(std::string const& na);
		CompositePart(std::vector<Part*> other);
		~CompositePart();
		void addPart(Part& p);
		std::vector<Part*> getParts();
		void printForTest(std::ostream& out);
	};
}

class Formatter {
protected:
	std::vector<PartsLists::Part*> part;
public:
	Formatter() = default;
	Formatter(PartsLists::Part p);
	Formatter(std::vector< PartsLists::Part*> src);
	virtual void printParts(PartsLists::Part p, std::ostream& = std::cout) = 0;
	virtual ~Formatter();
};

class HierarchyFormatter :public Formatter {
public:
	HierarchyFormatter(std::vector< PartsLists::Part*> src);
	void printParts(PartsLists::Part p, std::ostream& out =std::cout) override;
};

class SetFormatter:public Formatter {
public:
	SetFormatter(std::vector< PartsLists::Part*> src);
	void printParts(PartsLists::Part p, std::ostream& out =std::cout) override;
};

class Storable {
public:
	bool store(std::vector<PartsLists::Part*> toSave,Formatter& form, std::ostream& out);
	std::vector<PartsLists::Part*> load(std::istream& in);
};
#endif // !partList_h

