
#include "Chaining.h"
#include <iostream>
using namespace std;

/**
 * A hash routine for string objects.
 */
size_t hash(const string& key)
{
	size_t hashVal = 0;

	for (char ch : key)
		hashVal = 37 * hashVal + ch;

	return hashVal;
}

/**
 * A hash routine for ints.
 */
size_t hash(int key)
{
	return key;
}
