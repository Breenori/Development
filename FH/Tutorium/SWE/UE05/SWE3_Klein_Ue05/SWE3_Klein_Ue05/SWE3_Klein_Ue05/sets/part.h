#if ! defined PARTS_H
#define PARTS_H

#include <string>
#include <vector>
#include <iostream>

namespace PartsLists {

	// interface
	class Storable {
	public:
		virtual void store() = 0;
		virtual void load() = 0;

	protected:
		std::vector<std::string> part_list;
	};

	// base class
	class Part: public Storable {
	public:
		Part(std::string const& name): name_(name){}

		virtual ~Part(){}

		std::string getName() {
			return name_;
		}

		bool equals(Part const& o) {
			return name_ == o.name_;
		}

		// implemented in the cpp
		void store();
		void load();

	protected:
		std::string name_;

	private:
		// implemented in the cpp
		void store_rec(PartsLists::Part* p);
	};

	// specialized class
	class CompositePart :public Part {
	public:
		CompositePart(std::string const& name): Part(name){
		}
		~CompositePart() {
		}
		void addPart(Part* p) {
			parts.push_back(p);
		}

		std::vector<Part*> getParts()const {
			return parts;
		}

	private:
		std::vector<Part*> parts;
	};
}




#endif
