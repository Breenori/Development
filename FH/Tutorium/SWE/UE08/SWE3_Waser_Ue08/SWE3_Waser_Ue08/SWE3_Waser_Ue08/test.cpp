#include "test.h"

void empty_file() {
	cout << "\n\nTest with empty file:";
	TextCoder tc;
	tc.encode("test_files/empty.txt", "test_files/empty.txt");
	tc.decode("test_files/empty.txt", "test_files/empty.txt");

}
void nonexistant_files() {
	cout << "\n\nTest with non existant file:";
	TextCoder tc;
	tc.encode("test_files/a.txt", "test_files/a_encoded.txt");
	tc.decode("test_files/a_encoded.txt", "test_files/a.txt");
}
void decode_without_coding_table() {
	cout << "\n\nTest decoding without coding table (should not work):";
	TextCoder tc;
	tc.decode("test_files/test1_encoded.txt", "test_files/test1.txt");
}
void decode_with_wrong_coding_table() {
	cout << "\n\nTest decoding different file than what was encoded:";
	TextCoder tc;
	tc.encode("test_files/test1.txt", "test_files/test1_encoded.txt");
	tc.decode("test_files/test2_encoded.txt", "test_files/test2.txt");
}
void example1() {
	cout << "\n\nTest with example from instructions:";
	TextCoder tc;
	tc.encode("test_files/test1.txt", "test_files/test1_encoded.txt");
	tc.decode("test_files/test1_encoded.txt", "test_files/test1.txt");
}
void example2() {
	cout << "\n\nTest with other text from instructions:";
	TextCoder tc;
	tc.encode("test_files/test2.txt", "test_files/test2_encoded.txt");
	tc.decode("test_files/test2_encoded.txt", "test_files/test2.txt");
}
