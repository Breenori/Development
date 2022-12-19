//
// Created by arzi on 31.10.22.
//

#ifndef INC_01_RATIONAL_TESTRATIONALTYPE_H
#define INC_01_RATIONAL_TESTRATIONALTYPE_H

#include "rationalType.h"

class testRationalType {

public:
    static void testIsNegative();
    static void testIsPositive();
    static void testIsZero();

    static void testAdd();
    static void testSub();
    static void testMul();
    static void testDiv();
    static void testNormalize();

    static void testAddOP();
    static void testSubOP();
    static void testMulOP();
    static void testDivOP();

    static void testLhsRhsAdd();
    static void testLhsRhsSub();
    static void testLhsRhsMul();
    static void testLhsRhsDiv();

    static void testAssignment();
    static void testAssignmentInt();

    static void testEqual();
    static void testNotEqual();
    static void testSmallerEqual();
    static void testBiggerEqual();
    static void testSmaller();
    static void testBigger();

    static void testScan();

    static void testInvalidRational();
    static void testDivByZero();

    static void testAll();

};


#endif //INC_01_RATIONAL_TESTRATIONALTYPE_H
