#include "parser.h"

//----------------------------------------------------------------------------------------------------//
// public functions																					  //
//----------------------------------------------------------------------------------------------------//

void xpr::Parser::parse(std::istream& _in_) {
	try_parsing(_in_);
}

void xpr::Parser::parse(std::string const& _filename_) {
	std::ifstream istream{ _filename_ }; parse(istream); istream.close();
}

std::ostream& xpr::Parser::print_namelist(std::ostream& _out_) const{
	_out_ << "Current variable list: \n"; name_list.print(_out_); return _out_;
}

//----------------------------------------------------------------------------------------------------//
// private parse functions																			  //
//----------------------------------------------------------------------------------------------------//

void xpr::Parser::try_parsing(std::istream& _in_){
	try {
		if (_in_.good()) {
			m_scanner.register_keyword("print"); m_scanner.register_keyword("set");
			m_scanner.set_istream(_in_, true);
			parse_Program();
			m_scanner.set_istream();
		}
		else
			throw StreamException();
	}
	catch (ParserException& pars_err) {
		std::cerr << pars_err.what();
	}
	catch (StreamException& stream_err) {
		std::cerr << stream_err.what();
	}
	catch (pfc::scn::exception& sym_err) {
		std::cerr << sym_err.what();
	}
}

void xpr::Parser::parse_Program() {
	if (!is_tb_Program())
		throw ParserException("Error parsing \"Program\"!\n");

	while (is_tb_Program()) {
		if (is_tb_Print())
			parse_Print();
		else
			parse_Set();
	}

}

void xpr::Parser::parse_Print() {
	if (!is_tb_Print())
		throw ParserException("Error parsing \"Print\"!\n");

	m_scanner.next_symbol();

	m_scanner.next_symbol('(');
	StNode<double>* root = parse_Expression();
	m_scanner.next_symbol(')');

	m_scanner.next_symbol(';');

	SyntaxTree<double>* tree = new SyntaxTree<double>(root);

	std::cout << tree->evaluate(&name_list) << "\n";

}

void xpr::Parser::parse_Set() {
	if (!is_tb_Set())
		throw ParserException("Error parsing \"Set\"!\n");

	m_scanner.next_symbol();

	m_scanner.next_symbol('(');
	if (is_tb_Identifier()) {
		std::string var_name = m_scanner.get_identifier();

		m_scanner.next_symbol();
		m_scanner.next_symbol(',');

		StNode<double>* root = parse_Expression();

		m_scanner.next_symbol(')');
		m_scanner.next_symbol(';');

		SyntaxTree<double>* tree = new SyntaxTree<double>(root);

		name_list.register_var(var_name, tree);

	}
	else
		throw ParserException("Error parsing \"Set\"!\n");

}

xpr::StNode<double>* xpr::Parser::parse_Expression() {
	if (!is_tb_Expression())
		throw ParserException("Error parsing \"Expression\"!\n");

	StNode<double>* root_expr = parse_Term();

	while (is_tb_AddOp()) {

		char const sign = m_scanner.is('+') ? '+' : '-';
		StNodeOperator<double>* operator_node = nullptr;

		m_scanner.next_symbol();

		switch (sign) {
		case '+':
			 operator_node = new StNodeOperator<double>(StNodeOperator<double>::ADD);
			 break;
		case '-':
			operator_node = new StNodeOperator<double>(StNodeOperator<double>::SUB);
			break;
		default:
			throw ParserException("Error parsing \"Expression\"!\n");
			break;
		}

		StNode<double>* right_term = parse_Term();

		operator_node->set_left(root_expr);
		operator_node->set_right(right_term);
		root_expr = operator_node;

	}

	return root_expr;
}

xpr::StNode<double>* xpr::Parser::parse_Term() {
	if (!is_tb_Term())
		throw ParserException("Error parsing \"Term\"!\n");

	StNode<double>* root_term = parse_Factor();

	while (is_tb_MultOp()) {

		char const sign = m_scanner.is('*') ? '*' : '/';
		StNodeOperator<double>* operator_node = nullptr;

		m_scanner.next_symbol();

		switch (sign) {
		case '*':
			operator_node = new StNodeOperator<double>(StNodeOperator<double>::MUL);
			break;
		case '/':
			operator_node = new StNodeOperator<double>(StNodeOperator<double>::DIV);
			break;
		default:
			throw ParserException("Error parsing \"Term\"!\n");
			break;
		}

		StNode<double>* right_term = parse_Term();

		if (sign == '/' && right_term->evaluate(&name_list) == 0)
			throw DivisionByZero();

		operator_node->set_left(root_term);
		operator_node->set_right(right_term);
		root_term = operator_node;

	}

	return root_term;
}

xpr::StNode<double>* xpr::Parser::parse_Factor() {
	if (!is_tb_Factor())
		throw ParserException("Error parsing \"Factor\"!\n");

	StNode<double>* root_factor = nullptr;

	if (is_tb_AddOp()) {
		StNodeOperator<double>* op_node = new StNodeOperator<double>(StNodeOperator<double>::MUL);
		double sign = m_scanner.is('+') ? 1.0 : -1.0;
		StNodeValue<double>* sign_node = new StNodeValue<double>(sign);

		m_scanner.next_symbol();

		root_factor = op_node;
		op_node->set_left(sign_node);
		op_node->set_right(parse_UFactor());

	}
	else {
		root_factor = parse_UFactor();
	}

	return root_factor;
}

xpr::StNode<double>* xpr::Parser::parse_UFactor() {
	if (!is_tb_UFactor())
		throw ParserException("Error parsing \"UFactor\"!\n");

	StNode<double>* root_uFactor = nullptr;

	if (is_tb_Monom())
		return parse_Monom();
	else if (is_tb_PExpression())
		return parse_PExpression();
	else
		throw ParserException("Error parsing \"UFactor\"!\n");

	return nullptr;
}

xpr::StNode<double>* xpr::Parser::parse_Monom() {
	if (!is_tb_Monom())
		throw ParserException("Error parsing \"Monom\"!\n");

	StNode<double>* root_monom = parse_WMonom();

	if (is_tb_Exponent()) {
		StNode<double>* exp = parse_Exponent();

		exp->set_left(root_monom);
		root_monom = exp;

	}

	return root_monom;
}

xpr::StNode<double>* xpr::Parser::parse_PExpression() {
	if (!is_tb_PExpression())
		throw ParserException("Error parsing \"PExpression\"!\n");

	m_scanner.next_symbol('(');
	StNode<double>* root_expr = parse_Expression();
	m_scanner.next_symbol(')');

	return root_expr;
}

xpr::StNode<double>* xpr::Parser::parse_WMonom() {
	if (!is_tb_WMonom())
		throw ParserException("Error parsing \"WMonom\"!\n");

	if (is_tb_Identifier()) {
		StNodeIdent<double>* ident = new StNodeIdent<double>(m_scanner.get_identifier());
		m_scanner.next_symbol(); return ident;
	}
	else {
		StNodeValue<double>* value = new StNodeValue<double>(m_scanner.get_number());
		m_scanner.next_symbol(); return value;
	}

}

xpr::StNode<double>* xpr::Parser::parse_Exponent() {
	if (!is_tb_Exponent())
		throw ParserException("Error parsing \"Exponent\"!\n");

	StNodeOperator<double>* exp_node = new StNodeOperator<double>(StNodeOperator<double>::EXP);
	m_scanner.next_symbol();

	if (is_tb_AddOp()) {
		StNodeOperator<double>* op_node = new StNodeOperator<double>(StNodeOperator<double>::MUL);
		double sign = m_scanner.is('+') ? 1.0 : -1.0;
		StNodeValue<double>* sign_node = new StNodeValue<double>(sign);

		exp_node->set_right(op_node);
		m_scanner.next_symbol();

		StNodeValue<double>* value = new StNodeValue<double>(m_scanner.get_number());

		op_node->set_left(sign_node);
		op_node->set_right(value);

	}
	else {
		StNodeValue<double>* value = new StNodeValue<double>(m_scanner.get_number());
		m_scanner.next_symbol();

		exp_node->set_right(value);
	}

	return exp_node;
}

//----------------------------------------------------------------------------------------------------//
// is_tb functions																					  //
//----------------------------------------------------------------------------------------------------//

bool xpr::Parser::is_tb_Program() const {
	return is_tb_Set() || is_tb_Print();
}

bool xpr::Parser::is_tb_Print() const {
	return m_scanner.is_keyword("print");
}

bool xpr::Parser::is_tb_Set() const {
	return m_scanner.is_keyword("set");
}

bool xpr::Parser::is_tb_Expression() const {
	return is_tb_Term();
}

bool xpr::Parser::is_tb_Term() const {
	return is_tb_Factor();
}

bool xpr::Parser::is_tb_Factor() const {
	return is_tb_AddOp() || is_tb_UFactor();
}

bool xpr::Parser::is_tb_UFactor() const {
	return is_tb_PExpression() || is_tb_Monom();
}

bool xpr::Parser::is_tb_Monom() const {
	return is_tb_WMonom();
}

bool xpr::Parser::is_tb_PExpression() const {
	return m_scanner.is('(');
}

bool xpr::Parser::is_tb_WMonom() const {
	return is_tb_Identifier() || is_tb_Real();
}

bool xpr::Parser::is_tb_Exponent() const {
	return m_scanner.is('^');
}

bool xpr::Parser::is_tb_MultOp() const {
	return m_scanner.is('*') || m_scanner.is('/');
}

bool xpr::Parser::is_tb_AddOp() const {
	return m_scanner.is('+') || m_scanner.is('-');
}

bool xpr::Parser::is_tb_Identifier() const {
	return m_scanner.is_identifier();
}

bool xpr::Parser::is_tb_Real() const {
	return m_scanner.is_number() || m_scanner.is_real();
}
