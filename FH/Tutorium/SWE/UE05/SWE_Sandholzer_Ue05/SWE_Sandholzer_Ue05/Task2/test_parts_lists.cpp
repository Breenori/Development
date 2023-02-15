#include "test_parts_lists.h"
#include "formatter.h"

using std::cout;

using parts_list::part_t;
using parts_list::composite_part_t;

const std::string FILE_1 = "../save01.txt";
const std::string FILE_2 = "../save02.txt";
const std::string FILE_3 = "../save03.txt";
const std::string FILE_4 = "../save04.txt";
const std::string FILE_CLIMB = "../../climb.txt";
const std::string FILE_PANS = "../../pans.txt";
const std::string FILE_DRINK = "../../bottle.txt";
const std::string FILE_INV = "../../inv.txt";
const std::string FILE_MORE = "../../more.txt";

void print_hierarchy_and_set_overview(part_t const& part);

void test1()
{
	cout << "start test 1\n\n";

	composite_part_t sg("Sitzgarnitur");
	composite_part_t s1("Sessel");
	sg.add_part(s1);
	sg.add_part(s1);

	part_t bk("Bein (klein)");
	part_t sf("Sitzflaeche");
	s1.add_part(bk);
	s1.add_part(bk);
	s1.add_part(bk);
	s1.add_part(bk);
	s1.add_part(sf);

	composite_part_t ti("Tisch");
	part_t bg("Bein (gross)");
	part_t tf("Tischflaeche");
	ti.add_part(bg);
	ti.add_part(bg);
	ti.add_part(bg);
	ti.add_part(bg);
	ti.add_part(tf);
	sg.add_part(ti);

	formatter::print_hierarchy(cout, sg) << std::endl;

	formatter::print_part_set(cout, sg);

	sg.store(FILE_1);

	composite_part_t p_load;
	p_load.load(FILE_1);

	if (sg.equals(p_load))
	{
		cout << "\n\npart loaded with success\n\n";
	}
	else
	{
		cout << "\n\nERROR LOADED PART NOT EQUAL TO ORIGINAL!\n\n";
	}

	formatter::print_hierarchy(cout, p_load) << std::endl;

	formatter::print_part_set(cout, p_load);

	cout << "\nend test 1\n\n";
}

void test2()
{
	cout << "start test 2\n";

	cout << "\ncreating composite part: ";
	composite_part_t p1("");
	cout << "new part name: " << p1.get_name();
	cout << "\ncreating composite part: ";
	composite_part_t p2("\t");
	cout << "new part name: " << p2.get_name();
	cout << "\ncreating composite part: ";
	composite_part_t p3("\tuat");
	cout << "new part name: " << p3.get_name();
	cout << "\ncreating composite part: ";
	composite_part_t p4("\n\n");
	cout << "new part name: " << p4.get_name();
	cout << "\ncreating composite part: ";
	composite_part_t p5("\t      ");
	cout << "new part name: " << p5.get_name();
	cout << "\ncreating composite part: ";
	composite_part_t p6("leider mit {");
	cout << "new part name: " << p6.get_name();
	cout << "\ncreating composite part: ";
	composite_part_t p7("}dabei");
	cout << "new part name: " << p7.get_name();
	cout << "\ncreating composite part with valid name: ";
	composite_part_t p8("1()");
	cout << "new part name: " << p8.get_name();

	cout << "\n\nsavig part...";
	p8.store(FILE_2);
	composite_part_t cp1;

	cout << "\nloading part...";
	cp1.load(FILE_2);

	cout << "\ncheck if equal...";
	if (p8.equals(cp1))
	{
		cout << " they are equal!";
	}
	else
	{
		cout << " ERROR NOT EQUAL!!!!\n\n";
	}

	cout << "\n\nloading stored composite part as part...";
	part_t pl;
	pl.load(FILE_2);

	cout << "\ncheck if equal...";
	if (p8.equals(pl))
	{
		cout << " ERROR THEY ARE EQUAL!\n\n";
	}
	else
	{
		cout << " They are not equal because (empty) composite part != part";
	}

	cout << "\nsaving part...";
	pl.store(FILE_3);

	cout << "\nloading part...";
	part_t pl2;
	pl2.load(FILE_3);

	cout << "\ncheck if equal...";
	if (pl.equals(pl2))
	{
		cout << " they are equal!";
	}
	else
	{
		cout << " ERROR NOT EQUAL!!!!\n\n";
	}

	cout << "\n\ncreating composite part...";
	composite_part_t cpl("hello");
	cout << " part name: " << cpl.get_name();

	cout << "\nnow load previously stored part as composite part...";
	cpl.load(FILE_3);

	cout << "\ncheck if equal...";
	if (pl.equals(cpl))
	{
		cout << " THEY ARE EQUAL (part == composite part!!!)";
	}
	else
	{
		cout << " ERROR THEY ARE NOT EQUAL (BUT THEY SHOULD BE EVEN THO THEY ARE NOT)";
	}

	cout << "\n\npart_t: " << pl.get_name() << "\ncomposite_part_t: " << cpl.get_name();

	cout << "\n\nend test 2\n\n";
}

void test3()
{
	cout << "start test 3\n";
	
	composite_part_t cp1("Computermaus");
	print_hierarchy_and_set_overview(cp1);

	part_t pt1("Computermauskabel");
	part_t pt2("Computermausmaus");
	cp1.add_part(pt1);
	cp1.add_part(pt2);

	cout << "\nupdating part:\n";
	print_hierarchy_and_set_overview(cp1);

	cout << "\noutput for part_t:\n";
	print_hierarchy_and_set_overview(pt1);

	cout << "\nend test 3\n\n";
}

void test4()
{
	cout << "start test 4\n";

	composite_part_t cp;
	cp.load(FILE_CLIMB);

	print_hierarchy_and_set_overview(cp);

	auto& parts = cp.get_parts();
	parts.push_back(nullptr);

	print_hierarchy_and_set_overview(cp);

	cp.store(FILE_4);

	composite_part_t cpl;
	cpl.load(FILE_4);

	cout << "\n\nsaved and loaded, now check if they are equal:";
	if (cp.equals(cpl))
	{
		cout << "\n\nERROR THEY ARE EQUAL\n";
	}
	else
	{
		cout << "\n\nThey are not equal yet...\n";
	}

	cout << "\nadding a nullptr like for the original part...";
	auto& parts1 = cpl.get_parts();
	parts1.push_back(nullptr);
	if (cp.equals(cpl))
	{
		cout << "\n\nThey are equal now!\n";
	}
	else
	{
		cout << "\n\nERROR STILL NOT EQUAL!!!\n";
	}

	cout << "\nend test 4\n\n";
}

void test5()
{
	cout << "start test 5\n";

	composite_part_t cp;
	cp.load(FILE_PANS);
	print_hierarchy_and_set_overview(cp);

	part_t pt("coole Pfanne!");
	//cp.add_part(pt);			// not allowed!!! because in cp it would be erased but it cannot

	print_hierarchy_and_set_overview(pt);
	print_hierarchy_and_set_overview(cp);

	part_t* p_pt(new part_t("tolle Pfanne"));
	cp.add_part(*p_pt);

	print_hierarchy_and_set_overview(*p_pt);
	print_hierarchy_and_set_overview(cp);

	//delete p_pt;				// DO NOT DELETE IN HERE! cp is using it (at least to delete it)
	p_pt = nullptr;				// bad practise, but in this case ok to avoid dangling pointers

	cout << "\nend test 5\n\n";
}

void test6()
{
	cout << "start test 6\n";

	part_t bot1;
	bot1.load(FILE_DRINK);
	cout << "\nmy part: " << bot1.get_name();

	part_t bot2;
	bot2.load(FILE_INV);
	cout << "\ninv part: " << bot2.get_name();

	cout << "\n\nsame with composite part.\nmy part:";
	composite_part_t cbt1;
	cbt1.load(FILE_DRINK);
	print_hierarchy_and_set_overview(cbt1);

	cout << "\ninv part: \n";
	composite_part_t cbt2;
	cbt2.load(FILE_INV);
	print_hierarchy_and_set_overview(cbt2);

	cout << "\n\nend test 6\n\n";
}

void test7()
{
	cout << "start test 7\n";

	composite_part_t hi;
	hi.load(FILE_MORE);
	print_hierarchy_and_set_overview(hi);

	cout << "\nend test 7\n\n";
}

void print_hierarchy_and_set_overview(part_t const& part)
{
	cout << "\nhierarchy:\n";
	formatter::print_hierarchy(cout, part) << "\nsets:\n";
	formatter::print_part_set(cout, part);
}