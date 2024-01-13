#include "testRationalType.h"

int main() {
    testRationalType::testAll();

    std::cout << "Testing negative, positive, zero and normalize:" << std::endl;
    testRationalType::testIsNegative();
    testRationalType::testIsPositive();
    testRationalType::testIsZero();
    testRationalType::testNormalize();

    std::cout << "Testing regular mathematical operations:" << std::endl;
    testRationalType::testAdd();
    testRationalType::testSub();
    testRationalType::testMul();
    testRationalType::testDiv();

    std::cout << "Testing overloaded mathematical operations:" << std::endl;
    testRationalType::testAddOP();
    testRationalType::testSubOP();
    testRationalType::testMulOP();
    testRationalType::testDivOP();

    std::cout << "Testing mixed calculations (integers with rationals)" << std::endl;
    testRationalType::testLhsRhsAdd();
    testRationalType::testLhsRhsSub();
    testRationalType::testLhsRhsMul();
    testRationalType::testLhsRhsDiv();

    std::cout << "Testing comparisons:" << std::endl;
    testRationalType::testEqual();
    testRationalType::testNotEqual();
    testRationalType::testBiggerEqual();
    testRationalType::testSmallerEqual();
    testRationalType::testSmaller();
    testRationalType::testBigger();

    std::cout << "Testing assignments: " << std::endl;
    testRationalType::testAssignment();
    testRationalType::testAssignmentInt();

    std::cout << "Testing scan: " << std::endl;
    testRationalType::testScan();

    std::cout << "Testing exceptions: " << std::endl;
    testRationalType::testInvalidRational();
    testRationalType::testDivByZero();
    return 0;
}

// https://www.maths2mind.com/schluesselwoerter/rechenregeln-fuer-brueche
