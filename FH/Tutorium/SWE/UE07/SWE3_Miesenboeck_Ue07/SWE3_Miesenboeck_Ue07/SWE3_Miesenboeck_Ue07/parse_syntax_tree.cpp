#include "parse_syntax_tree.h"

using std::string;
using std::cout;
using std::endl;


// GLOBALS

namespace globals
{
	string PRINT("print");
	string SET("set");
}







// CONSTRUCTORS AND UTILITY FCTNS

xpr::parse_syntax_tree::parse_syntax_tree()
{
	this->m_scanner.register_keyword(globals::PRINT);
	this->m_scanner.register_keyword(globals::SET);
	m_nl = new name_list_map<syntax_tree<double>*>();

}

xpr::parse_syntax_tree::~parse_syntax_tree()
{
	this->clear();
}

// delete tree and name_list
void xpr::parse_syntax_tree::clear()
{
	delete this->m_tree;
	reset_syntax_tree();
	delete this->m_nl;
	this->m_nl = nullptr;
}


void xpr::parse_syntax_tree::reset_syntax_tree()
{
	// reset to nullptr, NOT delete tree (needed in name_list)
	this->m_tree = nullptr;
}


void xpr::parse_syntax_tree::parse(std::istream& in)
{
	reset_syntax_tree();

	// set input on scanner
	m_scanner.set_istream(in, true);

	// parse expression and get result
	parse_programm();

	// if scanner is not at end of input --> throw error --> whole scanner content has to be valid expression
	if (!m_scanner.is_eof())
	{
		throw ParserException("Error parsing 'Expression'.");
	}

	// remove input from scanner
	m_scanner.set_istream();

}

void xpr::parse_syntax_tree::parse(std::string const& str)
{
	// converts string to stream
	std::istringstream in{ str };

	// calls parse fctn
	parse(in);
}

void xpr::parse_syntax_tree::print_in_order_by_name(std::string const& name, std::ostream& os) const
{
	auto res = this->m_nl->lookup_var(name);
	if (res != nullptr)
	{
		os << res;
	}
}

void xpr::parse_syntax_tree::print_pre_order_by_name(std::string const& name, std::ostream& os) const
{
	auto res = this->m_nl->lookup_var(name);
	if (res != nullptr)
	{
		res->print_pre_order();
	}
}

void xpr::parse_syntax_tree::print_post_order_by_name(std::string const& name, std::ostream& os) const
{
	auto res = this->m_nl->lookup_var(name);
	if (res != nullptr)
	{
		res->print_post_order();
	}
}

void xpr::parse_syntax_tree::print_2d_by_name(std::string const& name, std::ostream& os) const
{
	auto res = this->m_nl->lookup_var(name);
	if (res != nullptr)
	{
		res->print_2d();
	}
}

void xpr::parse_syntax_tree::print_2d_upright_by_name(std::string const& name, std::ostream& os) const
{
	auto res = this->m_nl->lookup_var(name);
	if (res != nullptr)
	{
		res->print_2d_upright();
	}
}

void xpr::parse_syntax_tree::print_namelist(std::ostream& os) const
{
	this->m_nl->print(os);
}






// TB CHECKER

bool xpr::parse_syntax_tree::is_tb_programm() const
{
	return is_tb_output() || is_tb_assignment();
}

bool xpr::parse_syntax_tree::is_tb_output() const
{
	return m_scanner.is_keyword(globals::PRINT);
}

bool xpr::parse_syntax_tree::is_tb_assignment() const
{
	return m_scanner.is_keyword(globals::SET);
}

bool xpr::parse_syntax_tree::is_tb_expression() const
{
	return is_tb_term();
}

bool xpr::parse_syntax_tree::is_tb_term() const
{
	return is_tb_factor();
}

bool xpr::parse_syntax_tree::is_tb_factor() const
{
	return is_tb_add_op() || is_tb_u_factor();
}

bool xpr::parse_syntax_tree::is_tb_u_factor() const
{
	return is_tb_monom() || is_tb_p_expression();
}

bool xpr::parse_syntax_tree::is_tb_monom() const
{
	return is_tb_wmonom();
}

bool xpr::parse_syntax_tree::is_tb_p_expression() const
{
	return m_scanner.is('(');
}

bool xpr::parse_syntax_tree::is_tb_wmonom() const
{
	return m_scanner.is_identifier() || m_scanner.is_number();
}

bool xpr::parse_syntax_tree::is_tb_exponent() const
{
	return m_scanner.is('^');
}

bool xpr::parse_syntax_tree::is_tb_add_op() const
{
	return m_scanner.is('+') || m_scanner.is('-');
}

bool xpr::parse_syntax_tree::is_tb_mult_op() const
{
	return m_scanner.is('*') || m_scanner.is('/');
}









// PARSE FCTNS

void xpr::parse_syntax_tree::parse_programm()
{

	if (!is_tb_programm())
	{
		throw ParserException{ "ERROR parsing 'Programm'" };
	}

	if (is_tb_output())
	{
		parse_output();
	}

	else if (is_tb_assignment())
	{
		parse_assignment();
	}

}

void xpr::parse_syntax_tree::parse_output()
{
	if (!is_tb_output())
	{
		throw ParserException{ "ERROR parsing 'Ausgabe'" };
	}

	m_scanner.next_symbol();

	m_scanner.next_symbol('(');

	// create new tree by parsing expression
	this->m_tree = new syntax_tree<double>(parse_expression());

	m_scanner.next_symbol(')');

	m_scanner.next_symbol(';');

	// evaluate tree
	std::cout << m_tree->evaluate(this->m_nl) << std::endl;
	// reset current tree
	reset_syntax_tree();
}

void xpr::parse_syntax_tree::parse_assignment()
{
	if (!is_tb_assignment())
	{
		throw ParserException{ "ERROR parsing 'Zuweisung'" };
	}

	m_scanner.next_symbol();

	m_scanner.next_symbol('(');

	// get keyword
	string const keyword(m_scanner.get_identifier());

	// move scanner to next symbol
	m_scanner.next_symbol();

	m_scanner.next_symbol(',');

	// create new tree by parsing expression
	this->m_tree = new syntax_tree<double>(parse_expression());

	m_scanner.next_symbol(')');

	m_scanner.next_symbol(';');

	// register tree in name_list
	this->m_nl->register_var(keyword, this->m_tree);

	// reset current tree
	reset_syntax_tree();
}




xpr::st_node<double>* xpr::parse_syntax_tree::parse_expression()
{
	if (!is_tb_expression())
	{
		throw ParserException{ "ERROR parsing 'Expression'" };
	}

	st_node<double>* t_left(parse_term());
	st_node<double>* t_root(nullptr);

	if (is_tb_add_op())
	{
		t_root = parse_add_op();
		t_root->set_left(t_left);

		// multiple expressions can follow
		st_node<double>* t_right(parse_expression());
		t_root->set_right(t_right);
	}

	// does add op follow or not?
	if (t_root != nullptr)
	{
		return t_root;
	}

	return t_left;
}

xpr::st_node<double>* xpr::parse_syntax_tree::parse_term()
{
	if (!is_tb_term())
	{
		throw ParserException{ "ERROR parsing 'Term'" };
	}

	st_node<double>* t_left(parse_factor());
	st_node<double>* t_root(nullptr);

	if (is_tb_mult_op())
	{
		t_root = parse_mult_op();
		t_root->set_left(t_left);

		// multiple terms can follow
		st_node<double>* t_right(parse_term());
		t_root->set_right(t_right);
	}

	// does mult op follow or not?
	if (t_root != nullptr)
	{
		return t_root;
	}

	return t_left;
}

xpr::st_node<double>* xpr::parse_syntax_tree::parse_factor()
{
	if (!is_tb_factor())
	{
		throw ParserException{ "ERROR parsing 'Factor'" };
	}

	st_node<double>* t_root(nullptr);

	if (is_tb_add_op())
	{
		t_root = parse_add_op();
		t_root->set_left(new st_node_value<double>(0));
	}

	st_node<double>* t_right(parse_u_factor());

	if (t_root != nullptr)
	{
		t_root->set_right(t_right);
		return t_root;
	}

	return t_right;
}

xpr::st_node<double>* xpr::parse_syntax_tree::parse_u_factor()
{
	if (!is_tb_u_factor())
	{
		throw ParserException{ "ERROR parsing 'U Factor'" };
	}

	if (is_tb_monom())
	{
		st_node<double>* t_root(parse_monom());
		return t_root;
	}

	else if (is_tb_p_expression())
	{
		st_node<double>* t_root(parse_p_expression());
		return t_root;
	}

	throw ParserException{ "ERROR parsing 'Add Op'" };
}

xpr::st_node<double>* xpr::parse_syntax_tree::parse_monom()
{
	if (!is_tb_monom())
	{
		throw ParserException{ "ERROR parsing 'Monom'" };
	}

	st_node<double>* t_left(parse_wmonom());
	st_node<double>* t_root(nullptr);

	if (is_tb_exponent())
	{
		t_root = parse_exponent();
		t_root->set_left(t_left);
	}

	if (t_root != nullptr)
	{
		return t_root;
	}

	return t_left;
}


xpr::st_node<double>* xpr::parse_syntax_tree::parse_p_expression()
{
	if (!is_tb_p_expression())
	{
		throw ParserException{ "ERROR parsing 'P Expression'" };
	}

	m_scanner.next_symbol('(');

	st_node<double>* t_root(parse_expression());

	m_scanner.next_symbol(')');

	return t_root;
}


xpr::st_node<double>* xpr::parse_syntax_tree::parse_exponent()
{
	if (!is_tb_exponent())
	{
		throw ParserException{ "ERROR parsing 'Exponent'" };
	}


	if (m_scanner.is('^'))
	{

		st_node<double>* t_root = new st_node_operator<double>(st_node_operator<double>::EXP);
		m_scanner.next_symbol();
		if (m_scanner.is_number())
		{
			t_root->set_right(new st_node_value<double>(m_scanner.get_number()));
			m_scanner.next_symbol();
			return t_root;
		}
		else
		{
			throw ParserException{ "ERROR parsing 'Exponent'" };
		}
	}

	throw ParserException{ "ERROR parsing 'Exponent'" };

}

xpr::st_node<double>* xpr::parse_syntax_tree::parse_wmonom()
{
	if (!is_tb_wmonom())
	{
		throw ParserException{ "ERROR parsing 'W Monom'" };
	}

	if (m_scanner.is_identifier())
	{
		st_node_ident<double>* t_root = new st_node_ident<double>(m_scanner.get_identifier());
		m_scanner.next_symbol();
		return t_root;
	}

	else if (m_scanner.is_number())
	{
		st_node_value<double>* t_root = new st_node_value<double>(m_scanner.get_number());
		m_scanner.next_symbol();
		return t_root;
	}

	throw ParserException{ "ERROR parsing 'W Monom'" };

}


xpr::st_node_operator<double>* xpr::parse_syntax_tree::parse_add_op()
{
	if (!is_tb_add_op())
	{
		throw ParserException{ "ERROR parsing 'Add Op'" };
	}

	if (m_scanner.is('+'))
	{
		m_scanner.next_symbol();
		return new st_node_operator<double>(st_node_operator<double>::ADD);
	}

	else if (m_scanner.is('-'))
	{
		m_scanner.next_symbol();
		return new st_node_operator<double>(st_node_operator<double>::SUB);
	}

	throw ParserException{ "ERROR parsing 'Add Op'" };
}

xpr::st_node_operator<double>* xpr::parse_syntax_tree::parse_mult_op()
{
	if (!is_tb_mult_op())
	{
		throw ParserException{ "ERROR parsing 'Mult Op'" };
	}

	if (m_scanner.is('*'))
	{
		m_scanner.next_symbol();
		return new st_node_operator<double>(st_node_operator<double>::MUL);
	}

	else if (m_scanner.is('/'))
	{
		m_scanner.next_symbol();
		return new st_node_operator<double>(st_node_operator<double>::DIV);
	}

	throw ParserException{ "ERROR parsing 'Mult Op'" };
}
