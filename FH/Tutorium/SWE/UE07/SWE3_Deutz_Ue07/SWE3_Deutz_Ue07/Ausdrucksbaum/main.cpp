#include "test.h"

using namespace xpr;

int main() {

	StNode<double>* a = new StNodeValue<double>(5.3);
	StNode<double>* b = new StNodeValue<double>(2.1);
	//StNode<double>* c = new StNodeValue<double>(150.98);

	NameListMap<SyntaxTree<double>*> test_map;

	SyntaxTree<double> tree(a);
	SyntaxTree<double> tree_2(b);

	test_map.register_var("a", &tree);

	test_add_to_namelist(&test_map, "a", &tree_2);

	return 0;
}