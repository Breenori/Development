#ifndef formatter_h
#define formatter_h

#include "parts_lists.h"
#include <iostream>
#include <map>

using parts_lists::part;
using parts_lists::composite_part;
using std::map;

class formatter
{
public:
	virtual ~formatter(){}
	virtual void print_parts(part& p) const = 0;
};

class set_formatter : public formatter
{
private:
	void count_parts_rec(part& p, map<string, int>& map) const
	{
		composite_part* this_part = dynamic_cast<composite_part*>(&p);
		if (this_part != nullptr && !this_part->get_parts().empty())
		{
			for (size_t i{ 0 }; i < this_part->get_parts().size();++i)
			{
				count_parts_rec(*(this_part->get_parts()[i]), map);
			}
		}
		else
		{
			if (p.get_name() != "")
			{
				if (map.find(p.get_name()) == map.end())
					//not found
				{
					map[p.get_name()] = 1;
				}
				else
					//found
				{
					++map[p.get_name()];
				}
			}
		}
	}

public:
	virtual void print_parts(part& p) const override
	{
		map<string,int> this_parts;
		count_parts_rec(p, this_parts);
		std::cout << p.get_name() << ":\n";
		map<string, int>::iterator it;
		
		for (it = this_parts.begin(); it != this_parts.end(); ++it)
		{
			std::cout << "\t" << it->second << " " << it->first << "\n";
		}
	}
};

class hierarchy_formatter : public formatter
{
private:
	void print_parts_rec(part& p, int const level) const
	{
		string tabs = "";
		for (int i{ 1 }; i <= level; ++i)
		{
			tabs += "\t";
		}
		std::cout << tabs << p.get_name() << "\n";
		composite_part* this_part = dynamic_cast<composite_part*>(&p);
		if (this_part != nullptr)
		{
			for (size_t i{ 0 }; i < this_part->get_parts().size();++i)
			{
				print_parts_rec(*(this_part->get_parts()[i]), level + 1);
			}
		}
	}

public:

	virtual void print_parts(part& p) const override 
	{
		print_parts_rec(p, 0);
	}
};

#endif