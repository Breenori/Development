#include "formatter.h"

using parts_list::part_t;
using parts_list::composite_part_t;

std::ostream& formatter::print_hierarchy(std::ostream& out, part_t const& part)
{
	// call recursive print hierarchy function with starting indent 0
	print_hierarchy_rec(out, &part, 0);
	return out;
}

void formatter::print_hierarchy_rec(std::ostream& out, part_t const* part, int indent)
{
	// create indent
	for (int i = 0; i < indent; i++)
	{
		out << "   ";		
	}

	// print part name (if part is existing)
	if (part != nullptr)
	{
		out << part->get_name() << std::endl;
	}

	// if part is composite part => print hierarchy recursive for each child part
	composite_part_t const* cp = dynamic_cast<composite_part_t const*>(part);
	if (cp != nullptr)
	{
		for (size_t i{ 0 }; i < cp->get_parts().size(); ++i)
		{
			print_hierarchy_rec(out, cp->get_parts()[i], indent + 1);
		}
	}
}

std::ostream& formatter::print_part_set(std::ostream& out, part_t const& part)
{
	// print main part name first
	out << part.get_name() << ":";

	composite_part_t const* cp = dynamic_cast<composite_part_t const*>(&part);
	if (cp == nullptr)
	{
		// no parts if part is part_t
		out << " no composite parts";
	}
	else
	{
		std::map<std::string, int> part_map;	// create single part dictionary
		auto& parts = (*cp).get_parts();		// get parts to check if there are any

		if (parts.size() == 0)
		{
			out << " no composite parts";
		}
		else
		{
			// start getting all single parts recursively
			get_part_set_rec(part_map, &part);
		}

		// print all parts with amount
		for (auto ite = part_map.begin(); ite != part_map.end(); ++ite)
		{
			out << "\n   " << ite->second << " " << ite->first;
		}
	}

	return out << std::endl;
}

void formatter::get_part_set_rec(std::map<std::string, int>& part_dict, part_t const* part)
{
	composite_part_t const* cp = dynamic_cast<composite_part_t const*>(part);
	if (cp != nullptr)
	{
		// if part is composite part => get all it's sub-parts
		auto& parts = (*cp).get_parts();
		for (size_t i{ 0 }; i < parts.size(); ++i)
		{
			get_part_set_rec(part_dict, parts[i]);
		}
	}
	else
	{
		// part must not be nullptr (if nullptr has been added to part list)
		if (part != nullptr)
		{
			part_dict.count(part->get_name())
				? part_dict[part->get_name()]++
				: part_dict[part->get_name()] = 1;
		}
	}
}
