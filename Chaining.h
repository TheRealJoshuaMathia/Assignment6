using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using namespace std;


class ChainingHT
{
public:
	ChainingHT(int size = 101);
	void makeEmpty();



	void InsertIntoChainingHT(vector<string> DataArray);		//inserts into chaining hash table
	void  InsertionTimerChainingHT(); //record time to insert into chaining has table 

private:
	//ChainingHT			//or do different classes for hash table 
	//LinearProbingHT
	//QuadraticProbingH

	int currentsize; 
	vector<list> chainHT; 
};
