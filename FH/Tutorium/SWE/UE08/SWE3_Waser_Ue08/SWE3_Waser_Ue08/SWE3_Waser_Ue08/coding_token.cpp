#include "coding_token.h"
void CodingToken::fill_frequency_map() {
	frequency.clear();
	occurrences.clear();
	//go through text
	for (int i(0); i < text.size(); ++i) {
		//if it is not in the map add with 1 occurrence
		if (occurrences.count(text[i]) == 0)
			occurrences[text[i]] = 1;
		//otherwise increase the number of times it has been found
		else
			occurrences[text[i]]++;
	}
	//calculate values into percentages
	for (auto it = occurrences.begin(); it != occurrences.end(); ++it) {
		frequency[it->first] = it->second / text.size();
	}
}

void CodingToken::print_compression(CodingTable* ct) const {
	if (ct == nullptr)
		return;
	int original = text.size() * 8;
	double current = 0;
	for (auto it = occurrences.begin(); it != occurrences.end(); ++it) {
		current += it->second * ct->get_code(it->first).size();
	}
	cout << "\nCompression rate of " << current / original *100 << "%\n";
}

void CodingToken::print_frequency() const {
	//prints the percentage for each occuring sign
	cout << "\n" << setw(5) << "c" << "|" << setw(5) << "p" << "\n" << "------------\n";
	for (auto it = frequency.begin(); it != frequency.end(); ++it) {
		string firststring = "\"";
		firststring += it->first;
		firststring += "\"";
		cout << setw(5) << firststring << "|" << setw(5) << it->second << "\n";
	}
}

void CodingToken::create_hl() {
	//adds a new tree with just one frequency entry as element to the huffman list
	for (auto it = frequency.begin(); it != frequency.end(); ++it) {
		HuffmanTree* tree = new HuffmanTree(new HTNode(it->first, it->second));
		hList.add(new HLNode(tree));
	}
}

CodingToken::CodingToken() : text("") {}

CodingToken::CodingToken(string const& t) : text(t) {}
//setter
void CodingToken::set_text(string const& t) {
	text = t;
}
//generates a coding table
CodingTable* CodingToken::generateCodingTable() {
	//first get the frequency map and print the results
	fill_frequency_map();
	print_frequency();
	//create list elements from frequency map entries
	create_hl();
	//add entries together to create just one tree (one list entry with the whole tree in it)
	while (hList.get_size() > 1) {
		//as long as there are more than one entries left, remove the first two
		//( =the ones with the lowest percentages)
		HLNode* hl_left = hList.pop_front();
		HLNode* hl_right = hList.pop_front();
		HTNode* left = hl_left->get_node()->get_root();
		HTNode* right = hl_right->get_node()->get_root();
		//create a new tree with those (percentages get added automatically)
		HuffmanTree* tree = new HuffmanTree(new HTNode(left, right));
		//and add new node with the just created tree
		//'add' adds the node sorted
		hList.add(new HLNode(tree));
	}
	//print tree
	cout << "\nHuffman tree:";
	hList.print_tree();

	//only create CodingTable if there is a huffman tree
	HLNode* node = hList.pop_front();
	if (node != nullptr) {
		CodingTable* ct = new CodingTable();
		//calcualte the codes for the characters based on the huffman tree in the first list element
		ct->find_codes(node->get_node()->get_root());
		ct->print_codes();
		print_compression(ct);
		return ct;
	}
	return nullptr;
}