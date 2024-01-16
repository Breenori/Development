#ifndef I_STOREABLE_H
#define I_STORABLE_H

#include<string>
#include<fstream>

using std::ostream;
using std::istream;
using std::string;


class IStorable {
public:
	virtual ostream& store(ostream& out) = 0;
	virtual istream& load(istream& in) = 0;
};
#endif // !I_STOREABLE_H
