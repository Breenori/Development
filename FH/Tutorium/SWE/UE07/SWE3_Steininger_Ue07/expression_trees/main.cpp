#include <iostream>
#include"syntax_tree.h"
#include "parser.h"
#include <sstream>

#include "test_parse_syntax_tree.h"

using namespace xpr;

int main() {

//    StNodeOperator<double>* root = new StNodeOperator<double>(StNodeOperator<double>::ADD);
//    StNodeValue<double>* left = new StNodeValue<double>(17.0);
//    //StNodeValue<double>* right = new StNodeValue<double>(4.0);
//
//    StdNodeIdent<double>* right = new StdNodeIdent<double>("x");
//    root->set_left(left);
//    root->set_right(right);
//    NameList<SyntaxTree<double>*>*nl = new NameListMap<SyntaxTree<double>*>();
//    StNodeValue<double>* x_value = new StNodeValue<double>(4);
//    SyntaxTree<double>* x_tree = new SyntaxTree<double>(x_value);
//
//    nl->register_var("x", x_tree);
//
//    SyntaxTree<double>* st = new SyntaxTree<double>(root);
//
//    std::cout<<"Addition: ";
//    std::cout <<st<< "\nResult: "<<root->evaluate(nl)<<"\n";
//
//    cout<<" ------------ parser tests -----------\n";
//    std::stringstream sstream;
//    //sstream << "print(3);";
//    sstream << "set(a,1);\nset(pi,3.1415);\nset(k, -(a+3) * pi^0.5);\nprint(k);\nprint(3);\nprint(4 / (2 * (3 - 1)));\nset(x, 15);\nprint(x * 2);\n";
//    sstream <<"set(x, y^2 - 4);\n";
//    sstream << "set(y, 6); print(x); print(y); print(x/2);\n";
//    sstream << "set(y, 5); print(x); print(y); print(x/2);\n";
//    //sstream << "set(x,0); print(7 / r);";
//
//    parse_syntax_tree p (sstream);
//    p.parse();

        bool r1 = test_parse_syntax_tree::test_output_number();
        cout<<"Result: "<<r1<<"\n\n";
        bool r2 = test_parse_syntax_tree::test_output_expression();
        cout<<"Result: "<<r2<<"\n\n";

         bool r3 = test_parse_syntax_tree::test_output_nested_expression();
         cout<<"Result: "<<r3<<"\n\n";
         bool r4 = test_parse_syntax_tree::test_assign_number_and_output();
         cout<<"Result: "<<r4<<"\n\n";
         bool r5 = test_parse_syntax_tree::test_assign_expression_and_output();
         cout<<"Result: "<<r5<<"\n\n";
         bool r6 = test_parse_syntax_tree::test_assign_nested_expression_and_output();
         cout<<"Result: "<<r6<<"\n\n";
         bool r7 = test_parse_syntax_tree::test_exponent();
         cout<<"Result: "<<r7<<"\n\n";
         bool r8 = test_parse_syntax_tree::test_negative_number();
         cout<<"Result: "<<r8<<"\n\n";
         bool r9 = test_parse_syntax_tree::test_negative_expression();
         cout<<"Result: "<<r9<<"\n\n";
         bool r10 = test_parse_syntax_tree::test_reassign_var();
         cout<<"Result: "<<r10<<"\n\n";
         bool r11 = test_parse_syntax_tree::test_use_later_assigned_var_in_assignment();
         cout<<"Result: "<<r11<<"\n\n";
         bool r12 = test_parse_syntax_tree::test_use_unassigned_var_in_output();
         cout<<"Result: "<<r12<<"\n\n";
         bool r13 = test_parse_syntax_tree::test_unregistered_keyword();
         cout<<"Result: "<<r13<<"\n\n";
         bool r14 = test_parse_syntax_tree::test_division_by_zero_direct();
         cout<<"Result: "<<r14<<"\n\n";
         bool r15 = test_parse_syntax_tree::test_division_by_zero_var();
         cout<<"Result: "<<r15<<"\n\n";
         bool r16 = test_parse_syntax_tree::test_invalid_output();
         cout<<"Result: "<<r16<<"\n\n";
         bool r17 = test_parse_syntax_tree::test_invalid_assignment();
         cout<<"Result: "<<r17<<"\n\n";
         bool r18 = test_parse_syntax_tree::test_invalid_expression();
         cout<<"Result: "<<r18<<"\n\n";

         bool r19 = test_parse_syntax_tree::test_print_name_list();
         cout<<"Result: "<<r19<<"\n\n";

    return 0;
}
