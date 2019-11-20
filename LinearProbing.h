//inheritant from stl hash fucntion and add new fucntions
//#includes 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstddef>
#include <cstdlib>




//using namespace std::chrono;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using namespace std;

class LinearProbingHT
{
public:
	void insertIntoLinearProbingHT(vector<string> DataArray);

	void SearchLinearHT(vector<string> QueryArray);

private:
	//data members 
	int InsertionTimerLinearHT;  //holds time to complete all insertions 
	int CollisionsLinearHT;		 //tracks number of collisions, put inisde findpos() while loop 
	int SearchTimerLinearHT;	//holds total time for all searches 

};
