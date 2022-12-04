//
// Created by Hakim Bajim on 13.11.22.
//

#include "../content/rational_t.h"
#include "../content/div_by_zero.h"

void test_as_string() {
    std::cout << "\nTest as_string method: \n";
    std::cout << "expected outcome: <1/2>\nactual output: ";
    try {
        rational_t r1(1,2);
        std::cout << r1.as_string();
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_is_zero() {
    std::cout << "\nTest is_zero method: \n";
    std::cout << "expected outcome: true\nactual output: ";
    try {
        rational_t r1(0,5);
        std::cout << r1 << ": " << r1.is_zero();
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_is_positive() {
    std::cout << "\nTest is_positive method: \n";
    std::cout << "expected outcome: false\nactual output: ";
    try {
        rational_t r1(-1,2);
        std::cout << r1 << ": " << r1.is_positive();
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_is_negative() {
    std::cout << "\nTest is_negative method: \n";
    std::cout << "expected outcome: true\nactual output: ";
    try {
        rational_t r1(-1,2);
        std::cout << r1 << ": " << r1.is_negative();
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_copy_constructor() {
    std::cout << "\nTest copy constructor: \n";
    std::cout << "expected outcome: r1: <1/2> r: <1/2>\nactual output: ";
    try {
        rational_t r1(1,2);
        rational_t r2(r1);
        std::cout << "r1: " << r1 << " r2: " << r2;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_normalize() {
    std::cout << "\nTest normalize: \n";
    std::cout << "expected outcome: 0.5\nactual output: ";
    try {
        rational_t r1(1,2);
        std::cout << r1.normalize();
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_div_assign() {
    std::cout << "\nTest div assign of two rationals: \n";
    std::cout << "expected outcome: <1/2> / <1/4> = <1/2>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(1, 2);
        r1 *= r2;
        std::cout << r1;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_div() {
    std::cout << "\nTest div of two rationals: \n";
    std::cout << "expected outcome: <1/2> / <1/4> = <1/2>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(1, 2);
        r1 *= r2;
        std::cout << r1;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_mul_assign() {
    std::cout << "\nTest mul assign of two rationals: \n";
    std::cout << "expected outcome: <2/2> * <1/2> = <2/4>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(1, 2);
        r1 *= r2;
        std::cout << r1;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_mul() {
    std::cout << "\nTest mul of two rationals: \n";
    std::cout << "expected outcome: <2/2> * <1/2> = <2/4>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(1, 2);
        std::cout << r1 * r2;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_sub_assign() {
    std::cout << "\nTest sub assign of two rationals: \n";
    std::cout << "expected outcome: <2/2> - <1/2> = <1/2>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(1, 2);
        r1 -= r2;
        std::cout << r1;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_sub() {
    std::cout << "\nTest sub of two rationals: \n";
    std::cout << "expected outcome: <2/2> - <1/2> = <1/2>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(1, 2);
        std::cout << r1 - r2;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_addition_assign() {
    std::cout << "\nTest addition assign of two rationals: \n";
    std::cout << "expected outcome: <2/2> + <2/2> = <6/2>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(2);
        r1 += r2;
        std::cout << r1;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_addition() {
    std::cout << "\nTest addition of two rationals: \n";
    std::cout << "expected outcome: <2/2> + <2/2> = <6/2>\nactual output: ";
    try {
        rational_t r1(2,2);
        rational_t r2(2);
        std::cout << r1 + r2;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_with_0_in_denominator() {
    std::cout << "\nTest rational basic function: \n";
    std::cout << "expected outcome: an error\nactual output: ";
    try {
        rational_t r(1,0);
        std::cout << r;
    }
    catch (div_by_zero &e){
        std::cout << e.what();
    }
    std::cout << "\n\n";
}

void test_basic_test() {
    std::cout << "\nTest rational basic function: \n";
    std::cout << "expected outcome: <3/4>\nactual output: ";
    rational_t r(3,4);
    std::cout << r;
    std::cout << "\n\n";
}

void test_rational() {
    test_basic_test();
    test_with_0_in_denominator();
    test_addition();
    test_addition_assign();
    test_sub();
    test_sub_assign();
    test_mul();
    test_mul_assign();
    test_div();
    test_div_assign();
    test_normalize();
    test_copy_constructor();
    test_is_negative();
    test_is_positive();
    test_is_zero();
    test_as_string();
}