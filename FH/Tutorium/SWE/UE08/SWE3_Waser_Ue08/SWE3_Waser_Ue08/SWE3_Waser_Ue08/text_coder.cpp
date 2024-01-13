#include "text_coder.h"


string TextCoder::read(string const& filename) {
	//open filestream and check if it is good
	ifstream ifs(filename);
	string text = "";
	if (ifs.good()) {
		//read the file in one go
		ostringstream oss;
		oss << ifs.rdbuf();
		text = oss.str();
	}
	ifs.close();
	return text;
}
void TextCoder::read_original(string const& filename) {
	//set original to the text in the file
	original = read(filename);
}


TextCoder::TextCoder() {}
void TextCoder::encode(string const& from, string const& to) {
	//read and set origianl to the text in the from-file
	read_original(from);
	//create a CodingToken and generate a CodingTable
	CodingToken ct(original);
	cTable = ct.generateCodingTable();
	//only encode if if Coding table is not null;
	if (cTable == nullptr)
		return;
	//encode original
	string encoded = "";
	//foreach character in the original, get the code for it from the CodingTable and add it to the string of encoded characters
	for (int i(0); i < original.size(); ++i) {
		encoded += cTable->get_code(original[i]);
	}
	//print the encoded characters
	cout << "\nEncoded:\n" << encoded;
	//and write to the given file
	ofstream ofs(to);
	ofs << encoded;
	ofs.close();
}
void TextCoder::decode(string const& from, string const& to) {
	//read the text to encode
	string encoded = read(from);
	if (cTable == nullptr) {
		cout << "\ncan't decode without Coding Table!";
		return;
	}

	int read = 0;
	string code = "";
	string decoded = "";
	//find the characters the codes stand for
	while (read < encoded.size()) {
		//add another char of the encoded-string to the current code
		code += encoded[read];
		read++;
		//check if there is a sign the current code stands for
		char sign = cTable->get_sign(code);
		//if that's the case (return of get_sign is not -1) add the sign to the decoded string and set the current code back to an empty string
		if (sign != -1) {
			decoded += sign;
			code = "";
		}
	}
	//print the decoded and original strings and compare them
	cout << "\n\nDecoded:\n" << decoded;
	cout << "\nOriginal:\n" << original;
	cout << "\nThe decoded version it is ";
	if (decoded != original)
		cout << "not ";
	cout << "the same as the original!";
	//print the decoded string to the given file
	ofstream ofs(to);
	ofs << decoded;
	ofs.close();
}