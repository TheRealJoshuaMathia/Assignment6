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


//int nextPrime(int n);

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
class HashTableCH
{
public:
	explicit HashTableCH(int size = 101) : currentSize{ 0 }
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

	int getsearchtime(void) const
	{
		return this->SearchTimerChainingHT; 
	}



	void makeEmpty()
	{
		for (auto& thisList : theLists)			//set the hash table to empty 
			thisList.clear();
	}

	bool insert(const HashedObj& x)
	{	//set timer t1 here
		auto alg1st = high_resolution_clock::now(); //starting the counter clock 
		auto& whichList = theLists[myhash(x)];				//iterator = the hash position in the list
		if (find(begin(whichList), end(whichList), x) != end(whichList))		//search if this item is already stored in the hash table 
		{
			return false;						//doesnt allow duplicates 
		//	this->CollisionsChainingHT++;
			
		}
	/*	if (whichList.empty() != true)
		{
			this->CollisionsChainingHT++;
		}*/
		this->CollisionsChainingHT++;
		whichList.push_back(x);
		//whichList.
		// Rehash; see Section 5.5				//chaining doesnt do rehashing
		//if (++currentSize > theLists.size())
		//	rehash();

		//set timer t2 here
		auto alg1sp = high_resolution_clock::now();
		auto duration1 = duration_cast<microseconds>(alg1sp - alg1st);				//end timer count 

		this->InsertionTimerChainingHT = this->InsertionTimerChainingHT + duration1.count(); 		//in microseconds added onto total time 
		return true;
	}

	//added 7:50
	int InsertIntoChainingHT(vector<HashedObj> DataArray)
	{
		int count = 0; 
		typename vector<HashedObj>::iterator it = DataArray.begin();			//print data in array of strings
		for (it; it != DataArray.end(); it++)
		{
			//cout << count << ". " << *it << endl;
			count++;
			this->insert(*it);
		}

		this->avginsertiontime = this->InsertionTimerChainingHT / count; 
		return this->avginsertiontime;
	}

	//bool insert(HashedObj&& x)
	//{	//where do i place collisions 
	//	
	//	auto& whichList = theLists[myhash(x)];			//returns iterator with string key value 
	//	if (find(begin(whichList), end(whichList), x) != end(whichList))		//if you cant find the value 
	//	{
	//		this->CollisionsChainingHT++;
	//		return false;
	//		
	//		
	//	}
	//	whichList.push_back(std::move(x));			//since there isnt a duplicate input into list 
	////	this->CollisionsChainingHT++;
	//	// Rehash; see Section 5.5
	//	if (++currentSize > theLists.size())			//check the current size and rehash if needed
	//		rehash();

	//	return true;
	//}

	double SearchChainingHT(vector<HashedObj> QueryArray)
	{
		//loop through queryarray and search the hash table for each object 
		bool success = false;
		int searchcount = 0;				//used to track average 
		typename vector<HashedObj>::iterator it = QueryArray.begin();			//print data in array of strings
		for (it; it != QueryArray.end(); it++)
		{
			//cout << count << ". " << *it << endl;
			//count++;
			//this->insert(*it);
			searchcount++; 
			auto searcht1 = high_resolution_clock::now();
			//cout << "Searching for this: "<< *it << endl;				//print which item we are searching for 
			success = this->contains(*it);								//search for the value within the table
		//	cout << "Is found: " << success << endl;					//if found or not 
			auto searcht2 = high_resolution_clock::now();
			auto duration1 = duration_cast<microseconds>(searcht2 - searcht1);



			this->SearchTimerChainingHT = this->SearchTimerChainingHT + duration1.count();  // send time to average 
		}

		double timeavg = 0.0; 
		timeavg = this->SearchTimerChainingHT / searchcount; 
		return timeavg; 

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
//	int avgsearchtime; 
	int avginsertiontime;

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



#endif SEPARATE_CHAINING_H
