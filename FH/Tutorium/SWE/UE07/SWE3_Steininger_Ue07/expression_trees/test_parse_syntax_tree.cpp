//
// Created by Lukas Steininger on 07.02.23.
//

#include "test_parse_syntax_tree.h"

bool test_parse_syntax_tree::test_output_number() {
    cout<<"Test: output of simple number\n";
    string program = "print(3);\n";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "3";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_output_expression() {
    cout<<"Test: output of expression\n";
    string program = "print(12 * 3 + 20 / 5);\n";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "40";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_output_nested_expression() {
    cout<<"Test: output of nested expression\n";
    string program = "print(4 / (2 * (3 - 1)));\n";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "1";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_assign_number_and_output() {
    cout<<"Test: assign a simple number to a variable and use it in output\n";
    string program = "set(x,3);\nprint(x/2);\n";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "1.5";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_assign_expression_and_output() {
    cout<<"Test: assign an expression to a variable and use it in output\n";
    string program = "set(x,12 * 3 + 20 / 5);\nprint(x/5);\n";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "8";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;}

bool test_parse_syntax_tree::test_assign_nested_expression_and_output() {
    cout<<"Test: assign nested expression to var and use it multiple times in output\n";
    string program = "set(x,4 / (2 * (3 - 1)));\nprint((x * 5) / (x / 2));";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "10";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_exponent() {
    cout<<"Test: implementation of exponent\n";
    string program = "set(x,4);\nprint(x^2);";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "16";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_negative_number() {
    cout<<"Test: implementation negative number\n";
    string program = "set(x,-4);\nprint(5 - x);";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "9";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_negative_expression() {
    cout<<"Test: implementation of negative expression\n";
    string program = "set(x,12.5);\nprint(0 + -(x*3));";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "-37.5";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_reassign_var() {
    cout<<"Test: assign and reassign a value to var\n";
    string program = "set(x,12.5);\nprint(x);\nset(x,5);\nprint(x);";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string expected_1 = "12.5";
    string expected_2 = "5";
    string result_1;
    string result_2;
    out>>result_1;
    out>>result_2;

    cout << "expected: " << expected_1 << ", " << expected_2 << "\n";
    cout << "actual: "<<result_1<<", "<<result_2 <<"\n";

    return expected_1 == result_1 && expected_2==result_2;
}

bool test_parse_syntax_tree::test_use_later_assigned_var_in_assignment() {
    cout<<"Test: assign an expression to a var that uses an unassigned var\n\tshould work because the lookup for the variable happens when evaluating\n";
    string program = "set(x,y^2 - 4);\nset(y,6);\nprint(x);";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);

    string excpected = "32";
    string result;
    out>>result;

    cout << "expected: "<<excpected<<"\n";
    cout << "actual: "<<result<<"\n";

    return excpected==result;
}

bool test_parse_syntax_tree::test_use_unassigned_var_in_output() {
    cout << "Test: use unassigned var in output\n";
    string program = "set(x,y^2 - 4);\nprint(x);";
    cout << "Testing: " << program;

    stringstream in;
    in << program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    cout<< "expected: Variable 'y' not found"<<"\n";
    try {
        parser.parse(out);

    }
    catch (xpr::VariableNotFoundException *p) {
        cout << p->what() << "\n";
        return true;
    }

}
bool test_parse_syntax_tree::test_unregistered_keyword() {
    cout << "Test: use unrecognised keyword\n";
    string program = "zet(x,y^2 - 4);\nprint(x);";
    cout << "Testing: " << program;

    stringstream in;
    in << program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    cout<< "expected: Error parsing 'program'"<<"\n";
    try {
        parser.parse(out);

    }
    catch (xpr::parser_error *p) {
        cout << p->what() << "\n";
        return true;
    }
}

bool test_parse_syntax_tree::test_division_by_zero_direct() {
    cout << "Test: division by zero\n";
    string program = "print(7 / 0);";
    cout << "Testing: " << program;

    stringstream in;
    in << program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    cout<< "expected: Division by Zero"<<"\n";
    try {
        parser.parse(out);

    }
    catch (xpr::division_by_zero *p) {
        cout << p->what() << "\n";
        return true;
    }
}

bool test_parse_syntax_tree::test_division_by_zero_var() {
    cout << "Test: division by zero through variable\n";
    string program = "set(x,0);\nprint(7 / x);";
    cout << "Testing: " << program;

    stringstream in;
    in << program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    cout<< "expected: Division by Zero"<<"\n";
    try {
        parser.parse(out);

    }
    catch (xpr::division_by_zero *p) {
        cout << p->what() << "\n";
        return true;
    }
}

bool test_parse_syntax_tree::test_invalid_output() {
    cout << "Test: invalid format of print statement\n";
    string program = "print (7 / x, 1);";
    cout << "Testing: " << program;

    stringstream in;
    in << program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    cout<< "expected: Expected ')' but have ..."<<"\n";
    try {
        parser.parse(out);

    }
    catch (const pfc::scn::exception& p) {
        cout << p.what() << "\n";
        return true;
    }
}

bool test_parse_syntax_tree::test_invalid_assignment() {
    cout << "Test: invalid format of set statement\n";
    string program = "set(x);\n";
    cout << "Testing: " << program;

    stringstream in;
    in << program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    cout<< "expected: Expected ',' but have ..."<<"\n";
    try {
        parser.parse(out);

    }
    catch (const pfc::scn::exception& p) {
        cout << p.what() << "\n";
        return true;
    }
}

bool test_parse_syntax_tree::test_invalid_expression() {
    cout << "Test: invalid format of expression\n";
    string program = "set(x, / 4 5);\n";
    cout << "Testing: " << program;

    stringstream in;
    in << program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    cout<< "expected: Error parsing 'expression'"<<"\n";
    try {
        parser.parse(out);

    }
    catch (xpr::parser_error *p) {
        cout << p->what() << "\n";
        return true;
    }
}

bool test_parse_syntax_tree::test_print_name_list() {
    cout<<"Test: define multiple variables and print every (subtree) of each variable\n";
    string program = "set(x,y^2 - 4);\nset(y,6+4);\nprint((x * 5) / (x / 2));\n";
    cout << "Testing: "<<program;

    stringstream in;
    in<<program;
    xpr::parse_syntax_tree parser(in);

    stringstream out;
    parser.parse(out);
    parser.print_name_list();

    return true;
}
