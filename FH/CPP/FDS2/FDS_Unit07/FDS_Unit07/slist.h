#ifndef SLIST_H
#define SLIST_H
#include<iostream>

class slist {
public:
	typedef int value_t;
	typedef void (*function_t) (value_t&);

	slist();
	slist(slist const& src);
	~slist();

	void apply(function_t f);
	bool at(size_t n, value_t& value);
	size_t clear();
	bool contains(value_t const& value) const;
	size_t count(value_t const& value) const;
	bool empty() const;
	bool equal(slist const& rhs) const;
	void insert_sorted(value_t const& value);
	bool pop_back(value_t& value);
	bool pop_front(value_t& value);
	std::ostream& print(std::ostream& out = std::cout) const;
	void push_back(value_t const& value);
	void push_front(value_t const& value);


private:
	struct node_t
	{
		value_t data;
		node_t* next;
	};
};

#endif