/*
Authors: Parker Guillen, Josh Mathia
Class: Cpts 223
Project: PA#6
*/

#ifndef APP_H
#define APP_H

#include "Quadratic.h"
#include "LinearProbing.h"
#include "Chaining.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include <cstddef>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

// Encompasses the timing statistics
typedef struct stat
{
    int count = 0;
    double timer;
    int collisions = 0;
} Stat;

//Insert functions that are templetated for each collision method
Stat insertIntoHashT(vector<string> DataArray, Chaining::HashTable<string> hashT);
Stat insertIntoHashT(vector<string> DataArray, Linear::HashTable<string> hashT);
Stat insertIntoHashT(vector<string> DataArray, Quadratic::HashTable<string> hashT);

// Search functions that are templated to work for the collision methods
Stat searchHashT(vector<string> QueryArray, Chaining::HashTable<string> hashT);
Stat searchHashT(vector<string> QueryArray, Linear::HashTable<string> hashT);
Stat searchHashT(vector<string> QueryArray, Quadratic::HashTable<string> hashT);

//Prints statistics for the each operations
void printInsertStats(Stat data);
void printSearchStats(Stat data);

//------------------------------------------------
// Aim 2 functions
Stat insertIntoHashTSimple(vector<string> DataArray, Quadratic::HashTable<string> hashT);
Stat insertIntoHashTPrefix(vector<string> DataArray, Quadratic::HashTable<string> hashT);
Stat insertIntoHashTFull(vector<string> DataArray, Quadratic::HashTable<string> hashT);

Stat searchHashTSimple(vector<string> QueryArray, Quadratic::HashTable<string> hashT);
Stat searchHashTPrefix(vector<string> QueryArray, Quadratic::HashTable<string> hashT);
Stat searchHashTFull(vector<string> QueryArray, Quadratic::HashTable<string> hashT);

#endif