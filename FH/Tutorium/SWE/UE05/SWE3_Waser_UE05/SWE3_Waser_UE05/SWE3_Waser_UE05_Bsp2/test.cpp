#include "test.h"


void testConstructor() {
	HierarchyFormatter h;
	cout << "\nTest Constructors\tExpected\tActual\nDefault (Part)\t\tunknown part\t";
	Part default_p;
	h.printParts(&default_p);

	cout << "Default(Comp.Part)\tunknown part\t";
	CompositePart comp_p;
	h.printParts(&comp_p);

	cout << "given string (Part)\tTest test\t";
	Part string_p("Test test");
	h.printParts(&string_p);

	cout << "given string (Comp.Part) Test test\t";
	CompositePart string_comp_p("Test test");
	h.printParts(&string_comp_p);
}
void testEquals() {
	CompositePart p1("Sitzgarnitur");
	CompositePart p2("Sessel");
	CompositePart p8("Sessel rot");
	Part p3("Bein (klein)");
	Part p4("Sitzflaeche");
	CompositePart p5("Tisch");
	Part p6("Bein (gross)");
	Part p7("Tischflaeche");
	Part p9("Tischflaeche");

	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p4);
	p8.addPart(p3);
	p8.addPart(p3);
	p8.addPart(p3);
	p8.addPart(p3);
	p8.addPart(p4);

	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p7);
	p1.addPart(p2);
	p1.addPart(p2);
	p1.addPart(p5);

	HierarchyFormatter h;
	SetFormatter s;


	cout << "\nTest equals:\n";
	cout << "compare two composite parts: test1 ('Sessel') and test2 ('Sessel rot')\n";
	s.printParts(&p2);
	cout << "\n";
	s.printParts(&p8);
	cout << "\ntest1.equals(test2) \texpected: false\tactual: ";
	cout << std::boolalpha << p2.equals(p8);
	cout << "\ntest2.equals(test1) \texpected: false\tactual: ";
	cout << std::boolalpha << p8.equals(p2);

	cout << "\n\ncompare two parts: test3 ('Tischflaeche') and test4 ('Tischflaeche')\n";
	s.printParts(&p7);
	cout << "\n";
	s.printParts(&p9);
	cout << "\ntest3.equals(test4)\texpected: true\tactual: ";
	cout << std::boolalpha << p7.equals(p9);
	cout << "\ntest4.equals(test3)\texpected: true\tactual: ";
	cout << std::boolalpha << p9.equals(p7);

	cout << "\n\ncompare composite part and part: test1 ('Sessel') and test4 ('Tischflaeche')";
	cout << "\ntest1.equals(test4)\texpected: false\tactual: ";
	cout << std::boolalpha << p2.equals(p9);
	cout << "\ntest4.equals(test1)\texpected: false\tactual: ";
	cout << std::boolalpha << p9.equals(p2);

	cout << "\n\ncompare part to itself: test4 ('Tischflaeche')";
	cout << "\ntest4.equals(test4) \texpected: true\tactual: ";
	cout << std::boolalpha << p9.equals(p9);
	cout << "\ntest4.equals(test4) \texpected: true\tactual: ";
	cout << std::boolalpha << p9.equals(p9);
	cout << "\n\ncompare composite part to itself: test2 ('Sessel rot')";
	cout << "\ntest2.equals(test2) \texpected: true\tactual: ";
	cout << std::boolalpha << p8.equals(p8);
	cout << "\ntest4.equals(test4) \texpected: true\tactual: ";
	cout << std::boolalpha << p8.equals(p8);
	cout << "\ncompare two default parts\t expected: true\tactual: ";
	Part d_p;
	Part d_p2;
	cout << std::boolalpha << d_p.equals(d_p2);
	cout << "\n\ncompare two default composite parts\t expected: true\tactual: ";
	CompositePart d_cp;
	CompositePart d_cp2;
	cout << std::boolalpha << d_cp.equals(d_cp2);

}
void testAddPartGetParts() {
	SetFormatter sf;
	HierarchyFormatter hf;
	cout << "\n\nTest addPart and getParts\n";
	cout << "create composite part 'Sessel', print with SetFormatter:\n";
	CompositePart s("Sessel");
	CompositePart k("Kissen");
	Part kb("Kissenbezug");
	Part fk("Fuellkissen");
	Part b1("Bein");
	Part b2("Bein");
	Part b3("Bein");
	Part b4("Bein");
	k.addPart(kb);
	k.addPart(fk);
	sf.printParts(&s);
	cout << "\n\nadd part ('Bein') four times, print with SetFormatter:\n";
	s.addPart(b1);
	s.addPart(b2);
	s.addPart(b3);
	s.addPart(b4);
	sf.printParts(&s);
	cout << "\ngetParts and change name of second part to ('Bein klein'): (print with HierarchyFormatter)\n";
	s.getParts()[1]->getName() = "Bein klein";
	hf.printParts(&s);
	cout << "\nadd composite part (print with HierarchyFormatter)\n";
	s.addPart(k);
	hf.printParts(&s);
}

void testHierarchyFormatter() {
	cout << "\n\ntest HierarchyFormatter:\n";
	CompositePart p1("Sitzgarnitur");
	CompositePart p2("Sessel");
	Part p3("Bein (klein)");
	Part p4("Sitzflaeche");
	CompositePart p5("Tisch");
	Part p6("Bein (gross)");
	Part p7("Tischflaeche");
	CompositePart p8;
	Part p9;
	Part p10("Vase");

	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p4);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p7);
	p1.addPart(p2);
	p1.addPart(p2);
	p1.addPart(p5);
	p1.addPart(p10);

	HierarchyFormatter f;
	cout << "Test with CompositPart:\n";
	f.printParts(&p1);
	cout << "\nTest with CompositPart without any elements in Part-Vector:\t";
	f.printParts(&p8);
	cout << "\nTest with Part:\t";
	f.printParts(&p3);
	cout << "\nTest with default-Part:\t";
	f.printParts(&p9);
}

void testSetFormatter() {
	cout << "\n\ntest SetFormatter:\n";
	CompositePart p1("Sitzgarnitur");
	CompositePart p2("Sessel");
	Part p3("Bein (klein)");
	Part p4("Sitzflaeche");
	CompositePart p5("Tisch");
	Part p6("Bein (gross)");
	Part p7("Tischflaeche");
	CompositePart p8;
	Part p9;
	Part p10("Vase");

	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p4);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p7);
	p1.addPart(p2);
	p1.addPart(p2);
	p1.addPart(p5);
	p1.addPart(p10);

	SetFormatter f;
	cout << "Test with CompositPart:\n";
	f.printParts(&p1);
	cout << "\nTest with CompositPart without any elements in Part-Vector:\t";
	f.printParts(&p8);
	cout << "\nTest with Part:\t";
	f.printParts(&p3);
	cout << "\nTest with default-Part:\t";
	f.printParts(&p9);
}

void testStore() {
	CompositePart p1("Sitzgarnitur");
	CompositePart p2("Sessel");
	CompositePart p5("Tisch");
	CompositePart p9;
	CompositePart p10("Schreibtisch");
	Part p3("Bein (klein)");
	Part p4("Sitzflaeche");
	Part p6("Bein (gross)");
	Part p7("Tischflaeche");
	Part p8;
	Part p11("Vase");

	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p3);
	p2.addPart(p4);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p6);
	p5.addPart(p7);
	p1.addPart(p2);
	p1.addPart(p2);
	p1.addPart(p5);
	p1.addPart(p11);


	ofstream ofs1("test_store_composite.txt");
	ofstream ofs2("test_store_part.txt");
	ofstream ofs3("test_store_part_default.txt");
	ofstream ofs4("test_store_composite_default.txt");
	ofstream ofs5("test_store_composite_empty.txt");
	ofstream ofs6("test_closed.txt");
	ofs6.close();
	p1.store(ofs1);
	p7.store(ofs2);
	p8.store(ofs3);
	p9.store(ofs4);
	p10.store(ofs5);
	p11.store(ofs6);
	ofs1.close();
	ofs2.close();
	ofs3.close();
	ofs4.close();
	ofs5.close();
	cout << "\n\ntest store\nstored composite in test_store_composite.txt"
		<< "\nstored part in test_store_part.txt\nstore default part in test_store_part_default.txt"
		<< "\nstored default composite part in test_store_composite_default.txt"
		<< "\nstored composite part without parts in test_store_composite_empty.txt"
		<< "\ntry storing part with closed stream in test_closed.txt";

}

void testLoad() {
	HierarchyFormatter f;
	SetFormatter s;
	ifstream ifs1("test_store_composite.txt");
	ifstream ifs2("test_store_part.txt");
	ifstream ifs3("test_store_part_default.txt");
	ifstream ifs4("test_store_composite_default.txt");
	ifstream ifs5("test_store_composite_empty.txt");
	ifstream ifs6("test_closed.txt");

	CompositePart p1(ifs1);
	CompositePart p2(ifs4);
	CompositePart p3(ifs5);
	CompositePart p4(ifs2);
	ifs1.close();
	ifs2.close();
	ifs4.close();
	ifs5.close();
	ifs1.open("test_store_composite.txt");
	ifs2.open("test_store_part.txt");
	ifs4.open("test_store_composite_default.txt");
	ifs5.open("test_store_composite_empty.txt");

	Part p5(ifs2);
	Part p6(ifs3);
	Part p7(ifs1);
	Part p8(ifs4);
	Part p10(ifs6);
	ifs6.clear();
	ifs1.close();
	ifs2.close();
	ifs3.close();
	ifs4.close();
	Part p9(ifs3);
	cout << "\n\ntest load: load Part/Compositepart then print with HierarchyFormatter (HF) and SetFormatter(SF)\nload CompositePart from test_store_composite.txt:\nHF:\n";
	f.printParts(&p1);
	cout << "SF:\n";
	s.printParts(&p1);
	cout << "\n\nload CompositePart from test_store_composite_default.txt:\nHF:\n";
	f.printParts(&p2);
	cout << "SF:\n";
	s.printParts(&p2);
	cout << "\n\nload CompositePart from test_store_composite_empty.txt:\nHF:\n";
	f.printParts(&p3);
	cout << "SF:\n";
	s.printParts(&p3);
	cout << "\n\nload CompositePart from test_store_part.txt:\nHF:\n";
	f.printParts(&p4);
	cout << "SF:\n";
	s.printParts(&p4);
	cout << "\n\nload Part from test_store_part.txt:\nHF:\n";
	f.printParts(&p5);
	cout << "SF:\n";
	s.printParts(&p5);
	cout << "\n\nload Part from test_store_part_default.txt:\nHF:\n";
	f.printParts(&p6);
	cout << "SF:\n";
	s.printParts(&p6);
	cout << "\n\nload Part from test_store_composite.txt:\nHF:\n";
	f.printParts(&p7);
	cout << "SF:\n";
	s.printParts(&p7);
	cout << "\n\nload Part from test_store_composite_empty.txt:\nHF:\n";
	f.printParts(&p8);
	cout << "SF:\n";
	s.printParts(&p8);
	cout << "\n\ntry load Part from closed stream:\nHF:\n";
	f.printParts(&p9);
	cout << "SF:\n";
	s.printParts(&p9);
	cout << "\n\ntry load Part from empty file:\nHF:\n";
	f.printParts(&p9);
	cout << "SF:\n";
	s.printParts(&p9);


}