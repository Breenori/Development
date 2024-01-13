#include "parser.h"

using std::cout;

namespace xpr {

    //create list vor parser
    ParseSyntaxTree::ParseSyntaxTree() {

        m_list = new NameListMap<SyntaxTree<double>*>();

    }

    //parse grammar
    void ParseSyntaxTree::parse(istream& in) {

        //Programm = {Print|Assignment}

        m_scanner.register_keyword("set");
        m_scanner.register_keyword("print");

        m_scanner.set_istream(in, true);

        while (!m_scanner.is_eof()) {

            if (!m_scanner.is_keyword()) {

                throw ParserException("No keyword!");

            }

            if (is_tb_Assignment()) {

                parse_Assignment();

            }

            else if (is_tb_Print()) {

                parse_Print();

            }

            else{

                throw ParserException("Wrong keyword!");

            }

        }

        m_scanner.set_istream();

    }

    void ParseSyntaxTree::parse(string const& filename) {

        ifstream in;

        in.open(filename, ifstream::in);

        if (!in.good()) {

            throw ParserException("stream not good!");

        }

        return parse(in);

    }

    void ParseSyntaxTree::print_vars(ostream& out){

        m_list->print(out);

    }

    ParseSyntaxTree::~ParseSyntaxTree() {

        if (m_list != nullptr) {

            delete m_list;
            m_list = nullptr;

        }

    }

    //grammar rules check is if is...
    bool ParseSyntaxTree::is_tb_Expression() const {

        return is_tb_Term();

    }

    bool ParseSyntaxTree::is_tb_Term() const {

        return is_tb_Factor();

    }

    bool ParseSyntaxTree::is_tb_Factor() const {

        return is_tb_AddOp() || is_tb_U_Factor();

    }

    bool ParseSyntaxTree::is_tb_AddOp() const {

        return m_scanner.is('+') || m_scanner.is('-');

    }

    bool ParseSyntaxTree::is_tb_MultOp() const {

        return m_scanner.is('*') || m_scanner.is('/');

    }

    bool ParseSyntaxTree::is_tb_PExpression() const {

        return m_scanner.is('(');

    }

    bool ParseSyntaxTree::is_tb_U_Factor() const {

        return is_tb_Monom() || is_tb_PExpression();

    }

    bool ParseSyntaxTree::is_tb_Monom() const {

        return is_tb_WMonom();

    }

    bool ParseSyntaxTree::is_tb_WMonom() const {

        return m_scanner.is_identifier() || m_scanner.is_number();

    }

    bool ParseSyntaxTree::is_tb_Exponent() const {

        return m_scanner.is('^');

    }

    bool ParseSyntaxTree::is_tb_Assignment() const {

        return m_scanner.is_keyword("set");

    }

    bool ParseSyntaxTree::is_tb_Print() const {

        return m_scanner.is_keyword("print");

    }

    //parse functions
    StNode<double>* ParseSyntaxTree::parse_Expression() {

        //= Term { AddOp Term }

        if (!is_tb_Expression()) {

            throw ParserException("Error parsing 'Expression'.");

        }

        StNode<double>* root{ parse_Term() };

        while (is_tb_AddOp()) {

            StNode<double>* p{ parse_AddOp() };

            p->set_left(root);
            p->set_right(parse_Term());
            root = p;

        }

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_Term() {

        //= Factor { MultOp Factor }

        if (!is_tb_Term()) {

            throw ParserException("Error parsing 'Term'.");

        }

        StNode<double>* root{ parse_Factor() };

        while (is_tb_MultOp()) {

            StNode<double>* p{ parse_MultOp() };
            p->set_left(root);
            p->set_right(parse_Factor());
            root = p;

        }

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_Factor() {

        //= [ AddOp ] UFactor

        if (!is_tb_Factor()) {

            throw ParserException{ "Error parsing 'Factor'." };

        }

        StNode<double>* root = nullptr;

        if(is_tb_AddOp()){
        
            root = parse_AddOp();
            root->set_left(new StNodeValue<double>(0.0));
            root->set_right(parse_U_Factor());
        
        }

        else{

            root = parse_U_Factor();

        }

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_U_Factor(){

        //= Monom | PExpression

        if(!is_tb_U_Factor()){
        
            throw ParserException("Error parsing 'UFactor'.");
        
        }

        StNode<double>* root = nullptr;

        if (is_tb_PExpression()) {

            root = parse_PExpression();

        }

        else if (is_tb_Monom()) {

            root = parse_Monom();

        }

        return root;
    }

    StNode<double>* ParseSyntaxTree::parse_AddOp() {

        //= ”+“ | ”−“

        if (!is_tb_AddOp()) {

            throw ParserException("Error parsing 'AddOp'.");

        }

        StNode<double>* root = nullptr;

        if (m_scanner.is('+')) {

            root = new StNodeOp<double>(StNodeOp<double>::ADD);
            m_scanner.next_symbol();

        }

        else if (m_scanner.is('-')) {

            root = new StNodeOp<double>(StNodeOp<double>::SUB);
            m_scanner.next_symbol();

        }

        else {

            throw ParserException("Error parsing 'AddOp'.");

        }

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_MultOp(){

        //= ”*“ | ”/“

        if (!is_tb_MultOp()) {

            throw ParserException("Error parsing 'MultOp'.");

        }

        StNode<double>* root = nullptr;

        if (m_scanner.is('*')) {

            root = new StNodeOp<double>(StNodeOp<double>::MUL);
            m_scanner.next_symbol();

        }

        else if (m_scanner.is('/')) {

            root = new StNodeOp<double>(StNodeOp<double>::DIV);
            m_scanner.next_symbol();

        }

        else {

            throw ParserException("Error parsing 'MultOp'.");

        }

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_PExpression() {

        // ”(“ Expression ”)“

        if (!is_tb_PExpression()) {

            throw ParserException{ "Error parsing 'PExpression'." };

        }

        m_scanner.next_symbol('(');
        StNode<double>* root{ parse_Expression() };
        m_scanner.next_symbol(')');

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_Monom(){

        //= WMonom [Exponent]

        if (!is_tb_Monom()) {

            throw ParserException{ "Error parsing 'Monom'." };

        }

        StNode<double>* root{ parse_WMonom()};

        if (is_tb_Exponent()) {

            StNode<double>* p{ new StNodeOp<double>(StNodeOp<double>::EXP) };
            p->set_left(root);
            p->set_right(parse_Exponent());
            root = p;

        }

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_WMonom(){

        //= Identifier | Real

        if (!is_tb_WMonom()) {

            throw ParserException{ "Error parsing 'WMonom'." };

        }

        StNode<double>* root{ nullptr };

        if (m_scanner.is_identifier()) {

            root = new StNodeIdent<double>(m_scanner.get_identifier());

        }

        //real = number so it is possible to use int not only double
        else if(m_scanner.is_number()){

            root = new StNodeValue<double>(m_scanner.get_number());

        }

        else{

            throw ParserException{ "Error parsing 'WMonom'." };

        }

        m_scanner.next_symbol();

        return root;

    }

    StNode<double>* ParseSyntaxTree::parse_Exponent(){

        //= "^" [AddOp] Real

        if (!is_tb_Exponent()) {

            throw ParserException{ "Error parsing 'Exponent'." };

        }

        m_scanner.next_symbol('^');

        StNode<double>* root{ nullptr };

        if (is_tb_AddOp()) {

            root = parse_AddOp();
            root->set_left(new StNodeValue<double>(0.0));
            root->set_right(new StNodeValue<double>(m_scanner.get_number()));

        }

        else {

            root = new StNodeValue<double>(m_scanner.get_number());

        }

        m_scanner.next_symbol();

        return root;

    }

    void ParseSyntaxTree::parse_Assignment() {

        //= "set" "("Identifier "," Expression ")" ";"

        if (!is_tb_Assignment()) {

            throw ParserException("Error parsing 'Assignment'.");

        }

        m_scanner.next_symbol();

        if (m_scanner.is('(')) {

            m_scanner.next_symbol();

            if (m_scanner.is_identifier()) {

                string name{m_scanner.get_identifier()};
                m_scanner.next_symbol();
                   
                if (m_scanner.is(',')) {

                    m_scanner.next_symbol();

                    if (is_tb_Expression()){

                        SyntaxTree<double>* Exp = new SyntaxTree<double>(parse_Expression());

                        if (m_scanner.is(')')) {

                            m_scanner.next_symbol();
                            
                            if (m_scanner.is(';')) {

                                m_scanner.next_symbol();
                                m_list->register_var(name, Exp);
                                return;

                            }


                        }


                    }


                }


            }


        }

        throw ParserException("Error parsing 'Assignment'.");

    }

    void ParseSyntaxTree::parse_Print() {

        //= "print" "("Expression")" ";"

        if (!is_tb_Print()) {

            throw ParserException("Error parsing 'Print'.");

        }

        m_scanner.next_symbol();

        if (m_scanner.is('(')) {

            m_scanner.next_symbol();

            if (is_tb_Expression()) {

                SyntaxTree<double>* Exp = new SyntaxTree<double>(parse_Expression());

                if (m_scanner.is(')')) {

                    m_scanner.next_symbol();

                    if (m_scanner.is(';')) {

                        m_scanner.next_symbol();
                        cout << Exp->evaluate(m_list) << "\n\n";
                        return;

                    }


                }


            }


        }

        throw ParserException("Error parsing 'Print'.");

    }

};