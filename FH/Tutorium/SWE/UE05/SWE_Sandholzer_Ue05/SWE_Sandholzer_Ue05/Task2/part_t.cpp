#include "part_t.h"
#include <fstream>
#include <regex>

namespace parts_list
{
	// store base method from the storable interface can be implemented as follows
	void storable_t::store(std::string const& file_name) const
	{
		std::ofstream ofs(file_name);

		// create file stream and call recursive method
		this->store_rec(ofs);

		ofs.close();
	}

	// initialize part_t with default name
	part_t::part_t() : part_t(get_default_part_name())
	{}

	// initialize part_t with given name
	part_t::part_t(std::string const& name)
	{
		// validate name, must start with a letter or number and my only contain specific special chars
		if (std::regex_match(name, std::regex(get_regex_pattern())))
		{
			this->name = name;
		}
		else
		{
			// for testing purposes only
			std::cout << "invalid part name detected! taking default name\n";
			this->name = get_default_part_name();	// use default name
		}
	}

	std::string const& part_t::get_name() const
	{
		// getter for part name
		return this->name;
	}

	bool part_t::equals(part_t const& other) const
	{
		// two parts are equal if both names are the same
		// Note: cannot check if other may be a composite part!
		return this->name == other.name;
	}

	std::string const& part_t::get_default_part_name()
	{
		// static and constant default part name
		static const std::string def_name{ "undefined part" };
		return def_name;
	}

	std::string const& part_t::get_regex_pattern()
	{
		// static and constant regex pattern to validate part name
		static const std::string reg_pattern{ "^[A-Za-z0-9][A-Za-z0-9\\-\\(\\) ]*$" };
		return reg_pattern;
	}

	void part_t::load(std::string const& file_name)
	{
		std::ifstream ifs(file_name);

		// part can be loaded by getting the first string and set it as name
		std::string tmp_name{ "" };

		// first, get a non empty string
		while (tmp_name == "" && ifs.good())
		{
			std::getline(ifs, tmp_name);
		}

		// check if the string is valid => otherwise take default
		if (std::regex_match(tmp_name, std::regex(get_regex_pattern())))
		{
			this->name = tmp_name;
		}
		else
		{
			this->name = get_default_part_name();
		}

		ifs.close();
	}

	void part_t::store_rec(std::ostream& out) const
	{
		// store part name
		out << this->name;
	}

	// default ctor for composite part => default name
	composite_part_t::composite_part_t() : composite_part_t(get_default_part_name())
	{}

	composite_part_t::composite_part_t(std::string const& name) : part_t(name)
	{
		// init composite part using part ctor
		this->parts.clear();	// plus clear list
	}

	composite_part_t::~composite_part_t()
	{
		if (loaded)
		{
			// delete all composite parts if the list was initially loaded from a file
			for (size_t i = 0; i < this->parts.size(); i++)
			{
				if (this->parts[i] != nullptr)
				{
					delete this->parts[i];
				}
			}

			// clear dangling pointers
			this->parts.clear();
		}
	}

	void composite_part_t::add_part(part_t& part)
	{
		// CAVE: Here it can happen that elements might be added to list that will be but 
		// shouldn't be deleted when the composite part destructor is called (if the instance 
		// has been initialized with the "load" function)
		this->parts.push_back(&part);
	}

	std::vector<part_t*>& composite_part_t::get_parts()
	{
		// get parts non const
		return this->parts;
	}
	std::vector<part_t*> const& composite_part_t::get_parts() const
	{
		// get parts const
		return this->parts;
	}

	bool composite_part_t::equals(part_t const& other) const
	{
		composite_part_t const* cp = dynamic_cast<composite_part_t const*>(&other);
		if (cp == nullptr)
		{
			return false;	// part is not composite part (even if the part list is empty)
		}

		// if the names and the amount of parts are equal, have a closer look into the single parts
		if (this->name == other.get_name() && this->parts.size() == cp->get_parts().size())
		{
			// checks (recursively), if all parts are equal (equal name and equal "children")
			size_t indx(0);
			bool equal(true);
			while (equal && indx < this->parts.size())
			{
				if (this->parts[indx] == nullptr || cp->get_parts()[indx] == nullptr)
				{
					// if there is a nullptr at pos "indx" in one of the arrays, they can only
					// be equal if there is a nullptr on BOTH arrays at this index
					equal = this->parts[indx] == nullptr && cp->get_parts()[indx] == nullptr;
				}
				else
				{
					equal = this->parts[indx]->equals(*(cp->get_parts()[indx]));
				}
				++indx;
			}

			return equal;
		}
		else
		{
			return false;
		}
	}

	void composite_part_t::load(std::string const& file_name)
	{
		std::ifstream ifs(file_name);

		// loading composite part: start with root name, then load the rest recursively
		// first, get a non empty string
		std::string tmp_name{ "" };
		while (tmp_name == "" && ifs.good())
		{
			std::getline(ifs, tmp_name);
		}

		// check if the string is valid => otherwise take default
		if (std::regex_match(tmp_name, std::regex(get_regex_pattern())))
		{
			this->name = tmp_name;
		}
		else
		{
			this->name = get_default_part_name();
		}
		this->load_rec(ifs);

		ifs.close();
	}

	void composite_part_t::store_rec(std::ostream& out) const
	{
		out << this->name << std::endl;	// save part name
		composite_part_t const* cp = dynamic_cast<composite_part_t const*>(this);
		if (cp != nullptr)
		{
			// save the children in {...}, when part is a composite part
			out << "{\n";
			for (size_t i{ 0 }; i < cp->get_parts().size(); ++i)
			{
				// check if part is not nullptr
				part_t* tmp = cp->get_parts()[i];
				if (tmp != nullptr)
				{
					tmp->store_rec(out);
					out << std::endl;
				}
			}

			out << "\n}\n";
		}
	}

	void composite_part_t::load_rec(std::istream& in)
	{
		// mark current part as loaded => so later the children are going to be deleted
		this->loaded = true;		
		std::string curr{}, next{};

		// when a } comes (that isn't being processed inside the loop), all children
		// from the current composite part are read
		while (curr != "}" && in.good())
		{
			// gets an element; ignore { and empty strings
			while (curr == "{" || curr == "")
			{
				std::getline(in, curr);
			}

			// if the closing } are there (like empty parts list), immedeately end function
			if (curr == "}")
			{
				return;
			}

			// get next element (if there is any)
			while (next == "" && in.good())
			{
				std::getline(in, next);
			}

			// as long as there is a element in curr, parse part_t
			if (in.good() || curr != "")
			{
				if (next == "{")
				{
					// when the next line are opening { => composite part detected
					composite_part_t* cp(new composite_part_t(curr));	// create part
					cp->load_rec(in);				// get part children recursively
					this->add_part(*cp);			// add part to composite part
					curr = "";		// reset var
					next = "";		// reset var
				}
				else
				{
					// next line seems to be another part => part_t detected
					part_t* pa(new part_t(curr));		// create part
					this->add_part(*pa);				// add to list
					curr = next;						// shift next part name to curr var
					next = "";							// reset var
				}
			}
		}
	}
}
