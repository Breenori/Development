#include "Test.h"
using namespace std;
using namespace PartsLists;

void test_part_constructor() {
	Part a;
	cout <<  "Name of this part: " << a.get_name();
}

void test_part_constructor_2() {
	Part b("sessel");
	cout << "Name of this part: " << b.get_name();
}

bool test_equals() {
	Part a("sessel");
	//Part b("Sessel");
	Part b("sessel");
	cout << "Part 1: " << a.get_name() << endl;
	cout << "Part 2: " << b.get_name() << endl;

	if (a.equals(b)) {
		cout << "Both parts are the exact same" << endl;
		return true;
	}
	else {
		cout << "Both parts are not the exact same" << endl;
		return false;
	}
}


void test_composite_part_constructor() {
	
	CompositePart* sitzgarnitur = new CompositePart("Sitzgarnitur");
	cout << "Composite part: " << sitzgarnitur->get_name() << endl;
	delete sitzgarnitur;
}

void test_add_part(){
	CompositePart* sitzgarnitur = new CompositePart("Sitzgarnitur");
    Part a("sessel");
	Part b("tisch");
	Part c("tür");
	
	sitzgarnitur->add_part(a);
	sitzgarnitur->add_part(b);
	sitzgarnitur->add_part(c);

	cout << "Size of composite part: " << sitzgarnitur->getParts().size();
	delete sitzgarnitur;
}

void test_get_parts() {
	CompositePart* sitzgarnitur = new CompositePart("Sitzgarnitur"); 
	Part a("sessel");
	Part b("tisch");
	Part c("tür");

	sitzgarnitur->add_part(a);
	sitzgarnitur->add_part(b);
	sitzgarnitur->add_part(c);

	cout << "Composite Part: " << sitzgarnitur->get_name() << endl;
	cout << "Parts of composite part: " << endl;
	for (size_t i{ 0 }; i < sitzgarnitur->getParts().size(); i++ ){
		cout << &sitzgarnitur->getParts()[i] << endl; //just getting adress and not part names
	}

	delete sitzgarnitur;
}

//does not work
void test_formatter() {
CompositePart* sitzgarnitur = new PartsLists::CompositePart("Sitzgarnitur");
CompositePart* tisch = new PartsLists::CompositePart("Tisch");

Part sessel("Sessel");
Part beinKlein("Bein klein");
Part beinGross ("Beingroß");

sitzgarnitur->add_part(sessel);
sitzgarnitur->add_part(sessel);
sitzgarnitur->add_part(beinKlein);
sitzgarnitur->add_part(beinKlein);
sitzgarnitur->add_part(beinKlein);
sitzgarnitur->add_part(beinKlein);

tisch->add_part(beinGross);
tisch->add_part(beinGross);
tisch->add_part(beinGross);
tisch->add_part(beinGross);

sitzgarnitur->add_part(*tisch);

SetFormatter set;
HierarchyFormatter hierarchy;

set.print_parts(*sitzgarnitur);

cout << endl;

hierarchy.print_parts(*sitzgarnitur);

delete sitzgarnitur;
delete tisch;
}
