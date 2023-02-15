#ifndef tests_h
#define tests_h

#include "formatter.h"

void test1()
{
	part p1("Bein (klein)");
	part p2("Sitzflaeche");
	part p3("Bein (gross)");
	part p4("Tischflaeche");

	composite_part c1("Sessel");
	c1.add_part(p1);
	c1.add_part(p1);
	c1.add_part(p1);
	c1.add_part(p1);
	c1.add_part(p2);

	composite_part c2("Tisch");
	c2.add_part(p3);
	c2.add_part(p3);
	c2.add_part(p3);
	c2.add_part(p3);
	c2.add_part(p4);

	composite_part c3("Sitzgarnitur");
	c3.add_part(c1);
	c3.add_part(c1);
	c3.add_part(c2);

	hierarchy_formatter h1;
	h1.print_parts(c3);
	set_formatter f1;
	f1.print_parts(c3);
}

void test2()
{
	std::cout << "\n\n";
	part p1("Bein (klein)");
	part p2("Sitzflaeche");
	part p3("Bein (gross)");
	part p4("Tischflaeche");

	composite_part c1("Sessel");
	c1.add_part(p1);
	c1.add_part(p1);
	c1.add_part(p1);
	c1.add_part(p1);
	c1.add_part(p2);

	composite_part c2("Tisch");
	c2.add_part(p3);
	c2.add_part(p3);
	c2.add_part(p3);
	c2.add_part(p3);
	c2.add_part(p4);

	composite_part c3("Sitzgarnitur");
	c3.add_part(c1);
	c3.add_part(c1);
	c3.add_part(c2);

	c3.store("test2.txt");
}

void test3()
{
	composite_part c4("unknown");
	c4.load("test3.txt");
	hierarchy_formatter h1;
	h1.print_parts(c4);
	set_formatter s1;
	s1.print_parts(c4);
}

void test4()
{
	composite_part c5("unknown");
	c5.load("test4.txt");
	hierarchy_formatter h1;
	h1.print_parts(c5);
	set_formatter s1;
	s1.print_parts(c5);
}

void test5()
{
	composite_part c5("unknown");
	c5.load("test4.txt");
	c5.store("test5.txt");
}

void test6()
{
	composite_part c6("unknown");
	c6.load("test6.txt");
	hierarchy_formatter h1;
	h1.print_parts(c6);
}

#endif