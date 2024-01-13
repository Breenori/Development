#if!defined STÜCKLISTENVERWALTUNG_H
#define STÜCKLISTENVERWALTUNG_H
#include <iostream>
#include <string>
#include <vector>

namespace PartsLists {
	class Part {
	public:
		Part();  //default-constructor
		virtual ~Part(); //deconstructor
		Part(std::string const& name);
		std::string get_name();
		bool equals(Part const& o);

	private:
		std::string name;
	};

	class CompositePart :public Part {
	public:
		CompositePart(std::string const& name);
		~CompositePart();
		void add_part(Part p);
		std::vector<Part*> getParts();
		
	private:
		std::vector<Part*> parts_vec;
	};

	class Formatter {
	public:
		virtual void print_parts(Part & p) const = 0;

	};

	class SetFormatter :public Formatter {
	public:
		void print_parts(Part & p) const override;

	};

	class HierarchyFormatter :public Formatter {
	public:
		void print_parts(Part & p) const override;

	};

	class Storable {
	public:
		virtual void store() const = 0;
		virtual void load() const = 0;
	};

}

#endif
