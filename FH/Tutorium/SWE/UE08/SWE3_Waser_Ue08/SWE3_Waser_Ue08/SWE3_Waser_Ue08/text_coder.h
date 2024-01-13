#ifndef TEXT_CODER_H
#define TEXT_CODER_H

#include "coding_token.h"
#include <map>
#include <sstream>
#include <iomanip>
#include <fstream>

using std::ostringstream;
using std::ofstream;
using std::ifstream;

class TextCoder {
private:
	string original;
	string read(string const& filename);
	void read_original(string const& filename);
	CodingTable* cTable{ nullptr };
public:
	TextCoder();
	void encode(string const& from, string const& to);
	void decode(string const& from, string const& to);
};

#endif // !TEXT_CODER_H
