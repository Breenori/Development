#include "coding_table.h"

//prints all the signs and their codes
void CodingTable::print_codes() const {
	cout << "\n" << setw(5) << "c" << "|" << setw(5) << "p" << "\n" << "------------\n";
	for (auto it = entries.begin(); it != entries.end(); ++it) {
		string firststring = "\"";
		firststring += it->first;
		firststring += "\"";
		cout << setw(5) << firststring << "|" << setw(5) << it->second << "\n";
	}
}

void CodingTable::find_codes_rec(HTNode const* node, string code) {
	//only continue if node is no nullpointer
	if (node == nullptr)
		return;

	//when the node is a leaf, set current code for its sign
	HTNode* left = node->get_left();
	HTNode* right = node->get_right();

	if (left == nullptr && right == nullptr) {
		entries[node->get_sign()] = code;
	}
	else {
		//make code longer, last position 0/1 for left/right
		find_codes_rec(left, code + "0");
		find_codes_rec(right, code + "1");
	}
}

char const& CodingTable::get_sign(string const& code) const {
	//try to find an entry with code as value, return its key
	for (auto it = entries.begin(); it != entries.end(); ++it) {
		if (it->second == code)
			return it->first;
	}
	//returning -1 if there is no entry with code as value
	return -1;
}

string const& CodingTable::get_code(char const c) {
	//returns the code of the character c if it is in the map otherwise it returns an empty string
	if (entries.count(c) > 0)
		return entries[c];
	else
		return "";
}
void CodingTable::find_codes(HTNode const* root) {
	//can only find codes if the root is not a nullpointer
	if (root == nullptr)
		return;

	//check if root has children
	HTNode* left = root->get_left();
	HTNode* right = root->get_right();
	//if there are no children add root with code 1
	if (left == nullptr && right == nullptr) {
		entries[root->get_sign()] = 1;
	}
	else {
		//codes on the left start with 0, codes on the right start with 1
		find_codes_rec(left, "0");
		find_codes_rec(right, "1");
	}
}
//getter
map<char, string> const& CodingTable::get_entries() const {
	return entries;
}