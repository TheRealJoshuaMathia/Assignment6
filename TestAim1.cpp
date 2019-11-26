
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstddef>
#include <cstdlib>

#include "Chaining.h"
#include "Quadratic.h"
#include "LinearProbing.h"

//using namespace std::chrono;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using namespace std;

//
//void readfile(ifstream& readfile, vector<string> data)
//{
//	ifstream infile;
//	infile.open("OHenry.txt");
//
//	string line;
//
//	while (!infile.eof())
//	{
//		infile >> line;
//		data.push_back(line);
//
//	}
//}
//
//void printDatavector(vector<string> toprint)
//{
//	int count = 0;
//	vector<string>::iterator it = toprint.begin();
//	for (it; it != toprint.end(); it++)
//	{
//		cout << count << ". " << *it << endl;
//		count++;
//	}
//
//}

int main(void)
{
	//1. read in data line by line one word per line) load into vector of strings vector<string> DataArray
	string filename;
	ifstream infileH;
	ifstream infileQ;

	//for user selecting 
//	cout << "Enter a file to open: " << endl;
//	cin >> filename;
//	infileH.open(filename);

	infileH.open("OHenry.txt");
	infileQ.open("queries.txt");


	vector<string> DataArray; 
	vector<string> QueryArray;

	if (!infileH)
	{
		cout << "OHenry File error " << endl;
	}
	if (!infileQ)
	{
		cout << "queries File error " << endl;
	}

	string line;
	cout << "STarting ";

	
	

	//need to change this into fucntion within classes 
	while (!infileH.eof())			//opens file and reads correctly either way
	{
		infileH >> line;
		//getline(infileH, line);
		//cout << line;						
		DataArray.push_back(line);			//push data into dataarray

	}

	//need to print vector and lists 

	while (!infileQ.eof())			//opens file and reads correctly either way
	{
		infileQ >> line;
		//getline(infileH, line);
		//cout << line;						
		QueryArray.push_back(line);		//push data into queryarray 

	}




	infileH.close();
	infileQ.close();				//closes files 


	//int count = 0;
	//vector<string>::iterator it = QueryArray.begin();			//print data in array of strings
	//for (it; it != QueryArray.end(); it++)
	//{
	//	//cout << count << ". " << *it;
	//	count++;
	//}

	//

	//readfile(infileH, DataArray);
	//printDatavector(DataArray); 

	HashTableCH<string> ChainingHT; //create string hash table of chaining type 
	//HashTable<string> LinearHT;
	//HashTable<string> QuadraticHT; 
	int insertionavg = 0; 

	insertionavg = ChainingHT.InsertIntoChainingHT(DataArray);
	bool success = false;		//testing if values are inserted into hash table and if they can be found 
	success = ChainingHT.contains("eggman");
	cout << success << "= is 'the' found? " << endl;


	cout << "Insertion timer: " << ChainingHT.gettime() <<" Microseconds"<< "Average time: "<< insertionavg << endl;
	//next handle timing of inserts 
	//NEED to figure out where to put counter for number of collisions
	cout << "Collisions: " << ChainingHT.getcollisions() << endl;
	//Dont know where to put this 
	//next step is to do searching functions 
	//create a function which loops through every value of quary and searches the hash table for it using contains 
	//save total time and then save average time as well 
	double chainingtimeavg = 0.0; 
	chainingtimeavg = ChainingHT.SearchChainingHT(QueryArray);
	cout << "Chaining: Search time for queary array" << ChainingHT.getsearchtime()<< "Average time(in microseconds): " << chainingtimeavg << endl; 
	//gives total time and average time for searching 


	/*NOW HANDLING QUADRATIC
	1. insert data into hash
	2. measured insertions and collisions 
	3. measures timing 
	*/
	HashTableQP<string> QuadraticHT; 
	int avgtimeinsert = 0; 
	avgtimeinsert = QuadraticHT.InsertIntoQuadraticHT(DataArray);
	cout << "\nQuadratic:Total time:"<< QuadraticHT.gettime() << "\tAverage insert: " << avgtimeinsert << endl; 

	cout << "Collisions: " << QuadraticHT.getcollisions() << endl;

	double Quadratictimeavg = 0.0;
	Quadratictimeavg = QuadraticHT.SearchQuadraticHT(QueryArray);
	cout << "Quadratic total Search time: " << QuadraticHT.getsearchtime()<<"(microseconds)" << "\tAverage time(in microseconds): " << Quadratictimeavg << endl;


	//NOW HANDLING LINEAR
	//Linear hash table functions 
	HashTableLP<string> LinearHT;
	int avgtlin = 0; 
	avgtlin = LinearHT.InsertIntoLinearHT(DataArray);
	cout << "\nLinear:Total insertion time: " << LinearHT.gettime() << "\tAverage insert time: " << avgtlin << " (Microseconds)" << endl;

	cout << "Collisions: " << LinearHT.getcollisions() << endl; 

	double Linearsearcht = 0.0;
	Linearsearcht = LinearHT.SearchLinearHT(QueryArray);
	cout << "Linear total Search time: " << LinearHT.getsearchtime() << "(microseconds)" << "\tAverage time(in microseconds): " << Linearsearcht << endl;

	/*
	//JOSH NEXT STEPS
	work on aim 2 you homo 
	1. copy paste then 2 hash functions from the assignment doc 
	2. put these two hash function into quadraticHT class(dont need to work about full length function since that was what was used in aim 1 so just include the insert and
	search time from quadratic aim 1 for that)
	3. follow same layout for measuring timing using chrono lib. found in quadratic insertion function 
	4. then measure insertions and searches for these functions 


	//also review my collision functions and make sure collision works for chaining, im not sure if im measuring it at the right spots 

	*/



	//3. hash table (HT) implementations. Let 
	//us denote the corresponding objects as "ChainingHT", "LinearProbingHT"
	//		and "QuadraticProbingHT
	//need to create HT class and use polymorpthism for ChainingHT ..
	//have one class with all implemetations


	//4.  "int hash( const string & key, int tableSize )" for implementing all we will keep this hash function as-is, and just 
	//experiment by varying the collision resolution implementations, including
	//chaining, linear probingand quadratic probing.

	//



	return 0; 
}



