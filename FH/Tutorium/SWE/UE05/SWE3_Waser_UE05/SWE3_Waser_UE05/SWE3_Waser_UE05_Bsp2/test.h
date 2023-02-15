#ifndef TEST_H
#define TEST_H
#include "formatter.h"
#include <fstream>

using std::ofstream;
using std::ifstream;


void testConstructor();
void testEquals();
void testAddPartGetParts();
void testHierarchyFormatter();
void testSetFormatter();
void testStore();
void testLoad();

#endif // !TEST_H
