#include"syntax_tree.h"
#include "parse_syntax_tree.h"
#include "test_expression_tree.h"
#include <iostream>

using std::endl;
using namespace xpr;

int main()
{

	

	size_t test_idx(0);


	test_expression_tree::test_e_t_excp("print(5+4)", ++test_idx, "Kein Strichpunkt");
	test_expression_tree::test_e_t_excp("set(a,5+4)", ++test_idx, "Kein Strichpunkt");
	test_expression_tree::test_e_t_excp("print 5+4", ++test_idx, "Keine Klammern");
	test_expression_tree::test_e_t_excp("set a,5+4)", ++test_idx, "Keine Klammern");
	test_expression_tree::test_e_t_excp("set (a,5+4]", ++test_idx, "Keine Klammern");
	test_expression_tree::test_e_t_excp("set (a,5+4", ++test_idx, "Keine Klammern");
	test_expression_tree::test_e_t_excp("set (a,5+4", ++test_idx, "Keine Klammern");
	test_expression_tree::test_e_t_excp("set (a 5+4);", ++test_idx, "Keine Beistrich");
	test_expression_tree::test_e_t_excp("(a,5+4);", ++test_idx, "Kein Keyword");
	test_expression_tree::test_e_t_excp("(5+4);", ++test_idx, "Kein Keyword");
	test_expression_tree::test_e_t_excp("print(*5+4);", ++test_idx, "Ungueltige Expression");
	test_expression_tree::test_e_t_excp("print(5+4+);", ++test_idx, "Ungueltige Expression");
	test_expression_tree::test_e_t_excp("print(5*45+);", ++test_idx, "Ungueltige Expression");
	test_expression_tree::test_e_t_excp("", ++test_idx, "Leerer Input");
	test_expression_tree::test_e_t_excp(" ", ++test_idx, "Leerer Input");
	test_expression_tree::test_e_t_excp("print;", ++test_idx, "Ungueltiger Input");
	test_expression_tree::test_e_t_excp("print();", ++test_idx, "Ungueltiger Input");
	test_expression_tree::test_e_t_excp("set;", ++test_idx, "Ungueltiger Input");
	test_expression_tree::test_e_t_excp("set();", ++test_idx, "Ungueltiger Input");
	test_expression_tree::test_e_t_excp("print(a);", ++test_idx, "Undefinierte Variable");
	test_expression_tree::test_e_t_excp("print(10/0);", ++test_idx, "Division by 0");
	test_expression_tree::test_e_t_excp("print(10/(5-5));", ++test_idx, "Division by 0");
	test_expression_tree::test_e_t_excp("print(10/((5-2)*0));", ++test_idx, "Division by 0");

	test_expression_tree::test_e_t("print(5+4);", "9", ++test_idx, "Einzelne Zahl");
	test_expression_tree::test_e_t("print(5+4);", "9", ++test_idx, "Addition");
	test_expression_tree::test_e_t("print(51.63-4.42);", "47.21", ++test_idx, "Subtraktion");
	test_expression_tree::test_e_t("print(5*2.2);", "11", ++test_idx, "Multiplikation");
	test_expression_tree::test_e_t("print(5/4);", "1.25", ++test_idx, "Division");
	test_expression_tree::test_e_t("print(2^2);", "4", ++test_idx, "Exponent");
	test_expression_tree::test_e_t("print(5/4*5+(8-21.3)-5+2^2);", "-22.05", ++test_idx, "Komplexer Ausdruck");
	test_expression_tree::test_e_t("print(5*(4+1));", "25", ++test_idx, "Komplexer Ausdruck");
	test_expression_tree::test_e_t("print(2*4+5*6+7+9+10+1-1-4/2);","66", ++test_idx, "Komplexer Ausdruck");

	test_expression_tree::test_e_t_multi({ "set(a,1);","set(pi,3.1415);","set(k,-(a+3)*pi^0.5);","print(k);","print(3);","print(4/(2*(3-1)));","set(x,15);","print(x*2);","set(x,y^2-4);","set(y, 6);","print(x);","print(y);","print(x / 2)",
	"set(y,5);","print(x);","print(y);","print(x/2);"}, {"","", "", "-7.08971", "3", "1", "", "30","","","32","6","16","","21","5","10.5"}, ++test_idx, "Musterbeispiel");
	test_expression_tree::test_e_t_multi({"set(myvar,5+3);","set(myvar2,myvar+2);","set(myvar3, myvar * myvar2);","print(myvar);","print(myvar2);" ,"print(myvar3);" }, {"","","","8","10","80"}, ++test_idx, "Verschachtelte Variablen");
	test_expression_tree::test_e_t_multi({"set(myvar,5+3);","set(myvar2,myvar+2);","print(myvar);","print(myvar2);" ,"set(myvar,-17.3); ","print(myvar); ","print(myvar2); " }, {"","","8","10","","-17.3","-15.3"}, ++test_idx, "Redefinition von Variablen");
	test_expression_tree::test_e_t_multi({ "set(a,5+3);","set(b,c+2);","print(b);"}, {"","","EXCEPTION"}, ++test_idx, "Undefinierte Variablen");
	test_expression_tree::test_e_t_multi({ "set(a,5+3);","set(b,a+2);","print(b);","print(c);"}, {"","","10","EXCEPTION"}, ++test_idx, "Undefinierte Variablen");
	test_expression_tree::test_e_t_multi({ "set(a,5+3);","set(c,5-17+9*51^2-(8-7.4+8-9));","set(b,a + 2); ","print(c); ","Get Namelist"}, {"","","","-23419.4","PRINTNAMELIST"}, ++test_idx, "Namelist ausgeben");
	test_expression_tree::test_e_t_multi({"set(a,4*(5+3)+5+2+1*4);","a"}, {"","PRINTMETHODS"}, ++test_idx, "Print-Methoden ausgeben");
	test_expression_tree::test_e_t_multi({"set(a,4*(5+3));","a"}, {"","PRINTMETHODS"}, ++test_idx, "Print-Methoden ausgeben");


	return 0;
}