#ifndef CODING_TOKEN
#define CODING_TOKEN

#include "huffman_list.h"
#include "huffman_tree.h"
#include "coding_table.h"
#include <map>
#include <string>
#include <iomanip>

using std::map;
using std::string;
using std::setw;


class CodingToken {
private:
	HuffmanList hList;
	map<char, double> frequency;
	map<char, double> occurrences;
	string text;
	void fill_frequency_map();
	void print_frequency() const;
	void print_compression(CodingTable* ct) const;
	void create_hl();
public:
	CodingToken();
	CodingToken(string const& t);
	CodingTable* generateCodingTable();
	void set_text(string const& t);
};

#endif // !CODING_TOKEN
