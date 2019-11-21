#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstddef>
#include <cstdlib>


#include "Chaining.h"

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
	cout << "Enter a file to open: " << endl;
	cin >> filename;
	infileH.open(filename);

	//infileH.open("OHenry.txt");
	vector<string> DataArray; 

	if (!infileH)
	{
		cout << "File error " << endl;
	}

	string line;
	cout << "STarting ";		
	while (!infileH.eof())			//opens file and reads correctly either way
	{
		infileH >> line;
		//getline(infileH, line);
		//cout << line;						
		DataArray.push_back(line);

	}



	int count = 0;
	vector<string>::iterator it = DataArray.begin();			//print data in array of strings
	for (it; it != DataArray.end(); it++)
	{
		//cout << count << ". " << *it;
		count++;
	}

	//

	//readfile(infileH, DataArray);
	//printDatavector(DataArray); 

	HashTable<string> ChainingHT; //create string hash table of chaining type 
	//HashTable<string> LinearHT;
	//HashTable<string> QuadraticHT; 


	ChainingHT.InsertIntoChainingHT(DataArray);
	bool success = false;		//testing if values are inserted into hash table and if they can be found 
	success = ChainingHT.contains("eggman");
	cout << success << "= is 'the' found? " << endl;


	cout << "Insertion timer: " << ChainingHT.gettime() <<" Microseconds"<< endl;
	//next handle timing of inserts 
	//NEED to figure out where to put counter for number of collisions
	cout << "Collisions: " << ChainingHT.getcollisions() << endl;
	//Dont know where to put this 
	//next step is to do searching functions 
	//create a function which loops through every value of quary and searches the hash table for it using contains 
	//save total time and then save average time as well 


	//2. Read in data from queries and store in vector of strings vector<string> QueryArray

	//3. hash table (HT) implementations. Let 
	//us denote the corresponding objects as "ChainingHT", "LinearProbingHT"
	//		and "QuadraticProbingHT
	//need to create HT class and use polymorpthism for ChainingHT ..
	//have one class with all implemetations


	//4.  "int hash( const string & key, int tableSize )" for implementing all we will keep this hash function as-is, and just 
	//experiment by varying the collision resolution implementations, including
	//chaining, linear probingand quadratic probing.

	

	return 0; 
}

