#ifndef partslists_h
#define partslists_h

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


namespace PartsLists {

	class Storable {
	public:
		virtual std::istream& load(std::istream& in) = 0;
		virtual std::ostream& store(std::ostream& out = std::cout) = 0;
	};

	class Part : Storable {
	private:
		std::string name;

	public:
		Part(std::string name);
		virtual std::string getName() const;
		virtual void setName(std::string& name);
		virtual bool equals(Part o) const;

		virtual std::istream& load(std::istream& in);
		virtual std::ostream& store(std::ostream& out = std::cout);
	};

	class CompositePart : public Part {
		std::vector <Part*> parts;
	public:
		CompositePart(std::string name);
		void addPart(Part *p);
		virtual std::vector<Part*> getParts();

		virtual std::istream& load(std::istream& in) override;
	};

}



#endif // !partslists_h
