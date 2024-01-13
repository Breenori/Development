#include "test.h"
#include "text_coder.h"

int main() {

	empty_file();
	nonexistant_files();
	decode_without_coding_table();
	example1();
	example2();
	decode_with_wrong_coding_table();
	return 0;

}