#ifndef parts_lists_h
#define parts_lists_h

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

class storable
{
public:
	virtual ~storable() {}
	virtual void store(string const& filename) = 0;
	virtual void load(string const& filename) = 0;
};

namespace parts_lists
{
	class part
	{
	protected:
		string name;

	public:
		part(string const& _name = "unknown") : name(_name) {}
		virtual ~part(){}

		virtual string get_name()
		{
			return this->name;
		}

		virtual bool equals(part const& other)
		{
			return (this->name == other.name);
		}
	};

	class composite_part : public part, public storable
	{
	private:
		vector<part*> parts;

		void store_rec(std::ofstream& out, part& p, int const level) const
		{
			string tabs = "";
			for (int i{ 1 }; i <= level; ++i)
			{
				tabs += "\t";
			}
			out << tabs << p.get_name() << "\n";
			composite_part* this_part = dynamic_cast<composite_part*>(&p);
			if (this_part != nullptr)
			{
				for (size_t i{ 0 }; i < this_part->get_parts().size();++i)
				{
					store_rec(out, *(this_part->get_parts()[i]), level + 1);
				}
			}
		}

		void load_rec(vector<part*>& this_parts, string& current_name)
		{
			if (current_name[0] != '\t')
			{
				this_parts.push_back(new composite_part(current_name));
			}
			else
			{
				current_name.replace(0, 1, "");
				composite_part* current_parts = dynamic_cast<composite_part*>(this_parts[this_parts.size() - 1]);
				if (current_parts != nullptr)
				{
					load_rec(current_parts->parts, current_name);
				}
			}
		}

	public:
		composite_part(string const& _name)
		{
			this->name = _name;
			parts.clear();
		}
		virtual ~composite_part(){}

		void add_part(part& new_part)
		{
			this->parts.push_back(&new_part);
		}

		vector<part*> get_parts()
		{
			return this->parts;
		}

		virtual void store(string const& filename) override
		{
			std::ofstream out;
			out.open(filename);
			store_rec(out, *this, 0);
		}

		virtual void load(string const& filename) override
		{
			std::ifstream in;
			in.open(filename);
			string line = "";
			std::getline(in, line);
			this->name = line;
			while (in)
			{
				std::getline(in, line);
				if (line[0] == '\t')
				{
					line.replace(0, 1, "");
					load_rec(this->parts, line);
				}
			}
		}
	};
}
#endif