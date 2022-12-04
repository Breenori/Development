//
// Created by arzi on 31.10.22.
//

#include <fstream>
#include "testRationalType.h"

void testRationalType::testIsNegative() {
    rationalType a(2,-6);
    rationalType::printResult(a);
    a.isNegative() ? std::cout << "Rational number is negative." : std::cout << "Rational number is not negative.";
    std::cout << std::endl;
}

void testRationalType::testIsPositive() {
    rationalType a(2,6);
    rationalType::printResult(a);
    a.isPositive() ? std::cout << "Rational number is positive." : std::cout << "Rational number is not positive.";
    std::cout << std::endl;
}

void testRationalType::testIsZero() {
    rationalType a(0,4);
    rationalType::printResult(a);
    a.isZero() ? std::cout << "Rational number is zero." : std::cout << "Rational number is not zero.";
    std::cout << std::endl;
}

void testRationalType::testAdd() {
    rationalType a (4,12);
    rationalType b (6,12);
    a.add(b);
    rationalType::printResult(a);
}

void testRationalType::testSub() {
    rationalType a (4,9);
    rationalType b (3,6);
    a.sub(b);
    rationalType::printResult(a);
}

void testRationalType::testMul() {
    rationalType a (1,2);
    rationalType b (1,2);
    a.mul(b);
    rationalType::printResult(a);
}

void testRationalType::testDiv() {
    rationalType a (1,4);
    rationalType b (1,4);
    a.div(b);
    rationalType::printResult(a);
}

void testRationalType::testNormalize() {
    rationalType a (18,27);
    rationalType::printResult(a);
}

void testRationalType::testAddOP() {
    rationalType a (4,12);
    rationalType b (6,12);
    a = a + b;
    rationalType::printResult(a);
}

void testRationalType::testSubOP() {
    rationalType a (4,9);
    rationalType b (3,6);
    a = a - b;
    rationalType::printResult(a);
}

void testRationalType::testMulOP() {
    rationalType a (1,2);
    rationalType b (1,2);
    a = a * b;
    rationalType::printResult(a);
}

void testRationalType::testDivOP() {
    rationalType a (1,4);
    rationalType b (1,4);
    a = a / b;
    rationalType::printResult(a);
}

void testRationalType::testLhsRhsAdd() {
    rationalType a(1,3);
    rationalType b = 1 + a;
    rationalType::printResult(b);
}

void testRationalType::testLhsRhsSub() {
    rationalType a(1,3);
    rationalType b = 1 - a;
    rationalType::printResult(b);
}

void testRationalType::testLhsRhsMul() {
    rationalType a(-1,2);
    rationalType b = a * -10;
    rationalType::printResult(b);
}

void testRationalType::testLhsRhsDiv() {
    rationalType a(1,3);
    rationalType b = 1 / a;
    rationalType::printResult(b);
}

void testRationalType::testEqual() {
    rationalType a(3,4);
    rationalType b(1,2);
    bool result;
    result = a == b;
    std::cout << result << std::endl;
}

void testRationalType::testNotEqual() {
    rationalType a(3,4);
    rationalType b(1,2);
    bool result;
    result = a != b;
    std::cout << result << std::endl;
}

void testRationalType::testSmallerEqual() {
    rationalType a(3,4);
    rationalType b(1,2);
    bool result;
    result = a <= b;
    std::cout << result << std::endl;
}

void testRationalType::testBiggerEqual() {
    rationalType a(3,4);
    rationalType b(1,2);
    bool result;
    result = a >= b;
    std::cout << result << std::endl;
}

void testRationalType::testSmaller() {
    rationalType a(3,4);
    rationalType b(1,2);
    bool result;
    result = a < b;
    std::cout << result << std::endl;
}

void testRationalType::testBigger() {
    rationalType a(3,4);
    rationalType b(1,2);
    bool result;
    result = a > b;
    std::cout << result << std::endl;
}

void testRationalType::testAssignment() {
    rationalType a(4,5);
    rationalType b(1,3);
    rationalType::printResult(a);
    a = b;
    rationalType::printResult(a);
}

void testRationalType::testAssignmentInt() {
    rationalType a(4,5);
    rationalType::printResult(a);
    a = 45;
    rationalType::printResult(a);
}

void testRationalType::testInvalidRational() {
    try {
        rationalType a(2,0);
        rationalType::printResult(a);
    } catch (InvalidRationalException &e) {
        std::cout << "Exception caught: rational number is invalid." << std::endl;
    }
}

void testRationalType::testDivByZero() {
    try {
        rationalType a (1,4);
        rationalType b (0,4);
        a.div(b);
        rationalType::printResult(a);
    } catch (DivByZeroException &e) {
        std::cout << "Exception caught: division by zero is invalid." << std::endl;
    }
}

void testRationalType::testAll() {
    rationalType r(-1,2);
    std::cout << r * -10;
    std::cout << r * rationalType(20,-2);
    r = 7;
    std::cout << r + rationalType(2,3) << 10 / r / rationalType(2) + rationalType(6,5);
}

void testRationalType::testScan() {
    rationalType a, b;

    std::fstream file("inputFile.txt");
    a.scan(file);
    if (!a.isZero()) {
        rationalType::printResult(a);
    } else {
        std::cout << "Rational number input format was invalid, number not saved." << std::endl;
    }

    std::cout << "Please enter two seperated digits as rational number: ";
    b.scan();
    if (!b.isZero()) {
        rationalType::printResult(b);
    } else {
        std::cout << "Rational number input format was invalid, number not saved." << std::endl;
    }
}
