#ifndef FLUGREISE_H
#define FLUGREISE_H

#include "flug.h"
#include <iostream>
#include <ostream>
#include <list>

using std::list;
using std::ostream;
using std::cout;

class Flugreise
{
private:
	string start;
	list<Flug> hin;
	list<Flug> rueck;
	friend ostream& operator<<(ostream& out, Flugreise const& f);
public:

	Flugreise();
	Flugreise(string const& _start);

	void add_hinflug(Flug& f);
	void add_ruckflug(Flug& f);

};

#endif // !FLUGREISE_H
