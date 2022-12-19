#ifndef TESTS_H
#define TESTS_H

#include "fileManipulator.h"
#include "mergeSorter.h"

// ------------------------------------------------------------------------ //
// ------------------------ TESTS fileManipulatr -------------------------- //
void test_fill_ranomly();
void test_partition();
void test_copy();
void test_print();

// --------------------------------------------------------------------- //
// ------------------------ TESTS mergeSorter -------------------------- //
void test_emptyFile();
void test_sortingNumbers();
void test_sortingCharacters();
void test_sortingStrings();
void test_specialCharacter();
void test_sortingEvenNumber();
void test_sortigOddNumber();

#endif // !TESTS_H
