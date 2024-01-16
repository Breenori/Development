#ifndef CODING_TABLE_H
#define CODING_TABLE_H

#include "huffman_tree.h"
#include <map>
#include <string>
#include <iomanip>

using std::map;
using std::string;
using std::setw;

class CodingTable {
private:
	map<char, string> entries;
	void find_codes_rec(HTNode const* node, string code);
public:
	CodingTable() {};
	void find_codes(HTNode const* root);
	map<char, string> const& get_entries() const;
	string const& get_code(char const c);
	char const& get_sign(string const& code) const;
	void print_codes() const;
};

#endif // !CODING_TABLE_H
