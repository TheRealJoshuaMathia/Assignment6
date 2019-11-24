//#pragma once
//
//
//
//
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <chrono>
//#include <vector>
//#include <cstddef>
//#include <cstdlib>
//#include <list>
//
//
//
//
////using namespace std::chrono;
//using std::ifstream;
//using std::ofstream;
//using std::istream;
//using std::ostream;
//using std::list;
//using namespace std;
//
//
//class ChainingHT
//{
//public:
//	ChainingHT(int size = 101);				//constructor initalize table size 
//	void makeEmpty();
//
//
//
//	void InsertIntoChainingHT(vector<string> DataArray);		//inserts into chaining hash table
//	void  InsertionTimerChainingHT(); //record time to insert into chaining has table 
//
//private:
//	//ChainingHT			//or do different classes for hash table 
//	//LinearProbingHT
//	//QuadraticProbingH
//
//	int currentsize;
//	vector<list> chainHT;
//};

/*
Class for implementation of chaining collision resloution 
Might need to modfiy for stl compliant 


*/

#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <chrono>
#include "Prime.h"
using namespace std;
using namespace std::chrono;

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101) : currentSize{ 0 }
	{
		theLists.resize(101);		//set hash table size to 101
		this->CollisionsChainingHT = 0;
		this->InsertionTimerChainingHT = 0; 
		this->SearchTimerChainingHT = 0; 
	}

	bool contains(const HashedObj& x) const
	{
		auto& whichList = theLists[myhash(x)];		//check if the value is contained in the hash table 
		return find(begin(whichList), end(whichList), x) != end(whichList);
	}

	int gettime(void) const
	{
		return this->InsertionTimerChainingHT;
	}

	int getcollisions(void) const
	{
		return this->CollisionsChainingHT;
	}

	void makeEmpty()
	{
		for (auto& thisList : theLists)			//set the hash table to empty 
			thisList.clear();
	}

	bool insert(const HashedObj& x)
	{	//set timer t1 here
		auto alg1st = high_resolution_clock::now(); //starting the counter clock 
		auto& whichList = theLists[myhash(x)];				
		if (find(begin(whichList), end(whichList), x) != end(whichList))
		{
			return false;
			
		}
		whichList.push_back(x);

		// Rehash; see Section 5.5
		if (++currentSize > theLists.size())
			rehash();

		//set timer t2 here
		auto alg1sp = high_resolution_clock::now();
		auto duration1 = duration_cast<microseconds>(alg1sp - alg1st);

		this->InsertionTimerChainingHT = this->InsertionTimerChainingHT + duration1.count(); 		//in microseconds 
		return true;
	}

	//added 7:50
	void InsertIntoChainingHT(vector<HashedObj> DataArray)
	{
		typename vector<HashedObj>::iterator it = DataArray.begin();			//print data in array of strings
		for (; it != DataArray.end(); it++)
		{
			//cout << count << ". " << *it << endl;
			//count++;
			this->insert(*it);
		}
	}

	bool insert(HashedObj&& x)
	{	//where do i place collisions 
		auto& whichList = theLists[myhash(x)];			//returns iterator with string key value 
		if (find(begin(whichList), end(whichList), x) != end(whichList))		//if you cant find the value 
		{
			return false;
			
		}
		whichList.push_back(std::move(x));			//since there isnt a duplicate input into list 
		//this->CollisionsChainingHT++;
		// Rehash; see Section 5.5
		if (++currentSize > theLists.size())			//check the current size and rehash if needed
			rehash();

		return true;
	}

	bool remove(const HashedObj& x)
	{
		auto& whichList = theLists[myhash(x)];					//look for hash object 
		auto itr = find(begin(whichList), end(whichList), x);		//find the iterator with value of x

		if (itr == end(whichList))			//if iter not found return false 
			return false;

		whichList.erase(itr);			//otherwise erase the iterator with value x 
		--currentSize;					//minus the current size 
		return true;
	}

private:
	vector<list<HashedObj>> theLists;   // hash table The array of Lists
	int  currentSize;					//current size variable 

	int InsertionTimerChainingHT;  //holds time to complete all insertions 
	int CollisionsChainingHT;		 //tracks number of collisions, put inisde findpos() while loop 
	int SearchTimerChainingHT;

	void rehash()						//rezise the table 
	{
		vector<list<HashedObj>> oldLists = theLists;		//save the current vector datwa 

		// Create new double-sized, empty table
		theLists.resize(nextPrime(2 * theLists.size()));	//create a prime number doubled table size 
		for (auto& thisList : theLists)						//
			thisList.clear();

		// Copy table over
		currentSize = 0;						//set current sze to zero 
		for (auto& thisList : oldLists)			//
			for (auto& x : thisList)			//move data over to the new list 
				insert(std::move(x));
	}

	size_t myhash(const HashedObj& x) const		//used to insert into space for new values 
	{											//
		static hash<HashedObj> hf;				//
		return hf(x) % theLists.size();			//
	}
};
#endif