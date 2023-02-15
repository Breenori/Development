#ifndef FORMATTER_H
#define FORMATTER_H

#include "part_t.h"
#include <iostream>
#include <map>

class formatter
{
public:
	static std::ostream& print_hierarchy(std::ostream& out, parts_list::part_t const& part);
	static std::ostream& print_part_set( std::ostream& out, parts_list::part_t const& part);

private:
	formatter() = default;	// do not allow creating instances of formatter

	static void get_part_set_rec(std::map<std::string, int>& part_dict, parts_list::part_t const* part);
	static void print_hierarchy_rec(std::ostream& out, parts_list::part_t const* part, int indent);
};

#endif // !FORMATTER_H
