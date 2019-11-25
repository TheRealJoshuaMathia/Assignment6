//inheritant from stl hash fucntion and add new fucntions
//#includes 

//#include <string>
//#include <iostream>
//#include <fstream>
//#include <chrono>
//#include <vector>
//#include <cstddef>
//#include <cstdlib>
//
//
//
//
////using namespace std::chrono;
//using std::fstream;
//using std::ifstream;
//using std::ofstream;
//using std::istream;
//using std::ostream;
//using namespace std;
//
//class LinearProbingHT
//{
//public:
//	void insertIntoLinearProbingHT(vector<string> DataArray);
//
//	void SearchLinearHT(vector<string> QueryArray);
//
//private:
//	//data members 
//	int InsertionTimerLinearHT;  //holds time to complete all insertions 
//	int CollisionsLinearHT;		 //tracks number of collisions, put inisde findpos() while loop 
//	int SearchTimerLinearHT;	//holds total time for all searches 
//
//};


#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include "Prime.h"
#include <chrono>
using namespace std;
using namespace std::chrono;


//int nextPrime(int n);

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTableLP
{
public:
	explicit HashTableLP(int size = 101) : array(nextPrime(size))
	{
		makeEmpty();
	}

	bool contains(const HashedObj& x) //const
	{
		return isActive(findPos(x, 0));				//set to zero for collision  finding
	}

	int gettime(void) const			
	{
		return this->InsertionTimerLinearHT;
	}

	int getcollisions() const
	{
		return this->CollisionsLinearHT;
	}

	int getsearchtime(void) const
	{
		return this->SearchTimerLinearHT;
	}

	void makeEmpty()
	{
		currentSize = 0;
		for (auto& entry : array)
			entry.info = EMPTY;
	}

	bool insert(const HashedObj& x)  ///const remove here and remove from find position and see what happens 
	{
		// Insert x as active
		int counter = 0;		//used to count collisions 	

		auto alg1st = high_resolution_clock::now();			//starting insertion clock timer 
		int currentPos = findPos(x, &counter);			//wont let me use counter pointer corrrectly, trying to pass 
		//in a counter to keep track of pointer values within find position function 
		//counter keeps returning zero 
		this->CollisionsLinearHT = this->CollisionsLinearHT + counter;
		//cout << "Collisions quad: " << counter; 
		if (isActive(currentPos))
			return false;

		if (array[currentPos].info != DELETED)
			++currentSize;

		array[currentPos].element = x;
		array[currentPos].info = ACTIVE;

		// Rehash; see Section 5.5
		if (currentSize > array.size() / 2)
			rehash();

		auto alg1sp = high_resolution_clock::now();
		auto duration1 = duration_cast<microseconds>(alg1sp - alg1st);
		this->InsertionTimerLinearHT = this->InsertionTimerLinearHT + duration1.count();
		//cout << this->InsertionTimerQuadraticHT;

		return true;
	}

	int InsertIntoLinearHT(vector<HashedObj> DataArray)
	{
		int count = 0;
		//bool success;
		typename vector<HashedObj>::iterator it = DataArray.begin();			//print data in array of strings
		for (it; it != DataArray.end(); it++)
		{	//i think i did this wrong for both we need to continue to try to insert until it is succuessfully keep increasing if(su)


			this->insert(*it);
			//cout << count << ". " << *it << endl;			//probably works how do i test
			count++;

		}
		this->avginserttime = this->InsertionTimerLinearHT / count;
		return avginserttime;
	}

	bool insert(HashedObj&& x)
	{
		// Insert x as active
		int currentPos = findPos(x, 0);				//set to zero for collision finding
		if (isActive(currentPos))
			return false;

		if (array[currentPos].info != DELETED)
			++currentSize;

		array[currentPos] = std::move(x);
		array[currentPos].info = ACTIVE;

		// Rehash; see Section 5.5
		if (currentSize > array.size() / 2)
			rehash();

		return true;
	}



	double SearchLinearHT(vector<HashedObj> QueryArray)
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



			this->SearchTimerLinearHT = this->SearchTimerLinearHT + duration1.count();  // send time to average 
		}

		double timeavg = 0.0;
		timeavg = this->SearchTimerLinearHT / searchcount;
		return timeavg;

	}

	bool remove(const HashedObj& x)
	{
		int currentPos = findPos(x);
		if (!isActive(currentPos))
			return false;

		array[currentPos].info = DELETED;
		return true;
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };

private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj{ }, EntryType i = EMPTY)
			: element{ e }, info{ i } { }

		HashEntry(HashedObj&& e, EntryType i = EMPTY)
			: element{ std::move(e) }, info{ i } { }
	};

	vector<HashEntry> array;
	int currentSize;


	//initalize in constuctore 
	int InsertionTimerLinearHT;  //holds time to complete all insertions 
	int CollisionsLinearHT;		 //tracks number of collisions, put inisde findpos() while loop 
	int SearchTimerLinearHT;
	int avgsearchtime;
	int avginserttime;


	bool isActive(int currentPos) const
	{
		return array[currentPos].info == ACTIVE;
	}

	int findPos(const HashedObj& x, int * collisioncount) //const
	{
		int offset = 1;
		int currentPos = myhash(x);
		int count = 0; 
		while (array[currentPos].info != EMPTY &&
			array[currentPos].element != x)
		{
			count++;
			this->CollisionsLinearHT = count + this->CollisionsLinearHT;
			currentPos += offset;  // Compute ith probe , since current position is just plus one each time 
			//offset += 2;			//doesnt allow for quadratic offset 
			if (currentPos >= array.size())
				currentPos -= array.size();

			//	count += 1;
			//	cout << "Collisions: " << count << endl;
				//*collisioncount = count;
		}
		//this->CollisionsQuadraticHT = count + this->CollisionsQuadraticHT;
		//*collisioncount = count;
		return currentPos;
	}

	void rehash()
	{
		vector<HashEntry> oldArray = array;

		// Create new double-sized, empty table
		array.resize(nextPrime(2 * oldArray.size()));
		for (auto& entry : array)
			entry.info = EMPTY;

		// Copy table over
		currentSize = 0;
		for (auto& entry : oldArray)
			if (entry.info == ACTIVE)
				insert(std::move(entry.element));
	}

	size_t myhash(const HashedObj& x) const
	{
		static hash<HashedObj> hf;
		return hf(x) % array.size();
	}
};

#endif
