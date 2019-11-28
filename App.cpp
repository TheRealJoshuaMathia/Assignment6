#include "App.h"
/*
Authors: Parker Guillen, Josh Mathia
Class: Cpts 223
Project: PA#6
*/

int main()
{
    Chaining::HashTable<string> ChainingHashT;
    Linear::HashTable<string> LinearProbingHashT;
    Quadratic::HashTable<string> QuadraticProbingHashT;

    ifstream infileH;
    ifstream infileQ;

    //Opens File
    infileH.open("OHenry.txt");
    infileQ.open("queries.txt");

    if (!infileH.is_open())
    {
        cout << "OHenry File error " << endl;
    }
    if (!infileQ.is_open())
    {
        cout << "queries File error " << endl;
    }

    cout << "Starting to Read File... " << endl
         << endl;

    vector<string> DataArray;
    vector<string> QueryArray;

    string line;

    //Reads in the contents of the array and populates the extracted string into the DataArray
    while (infileH >> line)
    {
        //cout << line << endl;
        DataArray.push_back(line);
    }
    infileH.close(); // close file for reading

    //Reads in the contents of the array and populates the extracted string into the QueryArray
    while (infileQ >> line)
    {
        // cout << line << endl;
        infileQ >> line;
        QueryArray.push_back(line);
    }

    cout << "Starting Insertion..." << endl
         << endl;

    //Insert data into each of the following
    Stat chaining = insertIntoHashT(DataArray, ChainingHashT);
    Stat linear = insertIntoHashT(DataArray, LinearProbingHashT);
    Stat quadratic = insertIntoHashT(DataArray, QuadraticProbingHashT);

    cout << "Chaining Results: " << endl;
    printInsertStats(chaining);

    cout << "Linear Results: " << endl;
    printInsertStats(linear);

    cout << "Quadratic Results:" << endl;
    printInsertStats(quadratic);

    cout << endl
         << "Starting Search ..." << endl
         << endl;

    //Runs through each of the collision methods and queries the elements in the array
    // To find the elements in the hashTable
    Stat searchChaining = searchHashT(QueryArray, ChainingHashT);
    Stat searchLinear = searchHashT(QueryArray, LinearProbingHashT);
    Stat searchQuadratic = searchHashT(QueryArray, QuadraticProbingHashT);

    cout << "Chaining Results: " << endl;
    printSearchStats(searchChaining);
    cout << "Linear Results: " << endl;
    printSearchStats(searchLinear);
    cout << "Quadratic Results:" << endl;
    printSearchStats(searchQuadratic);

    cout << "Starting Aim2..." << endl;
    cout << "----------------------------" << endl
         << endl;

    cout << "Starting Insertion..." << endl
         << endl;
    Stat quadraticSimple = insertIntoHashTSimple(DataArray, QuadraticProbingHashT);
    Stat quadraticPrefix = insertIntoHashTPrefix(DataArray, QuadraticProbingHashT);
    Stat quadraticFull = insertIntoHashTFull(DataArray, QuadraticProbingHashT);

    cout << "Quadratic (Simple):" << endl;
    printInsertStats(quadraticSimple);
    cout << "Quadratic (Prefix):" << endl;
    printInsertStats(quadraticPrefix);
    cout << "Quadratic (Full):" << endl;
    printInsertStats(quadraticFull);

    cout << endl
         << "Starting Search ..." << endl
         << endl;
    Stat quadraticSimpleSearch = searchHashTSimple(DataArray, QuadraticProbingHashT);
    Stat quadraticPrefixSearch = searchHashTPrefix(DataArray, QuadraticProbingHashT);
    Stat quadraticFullSearch = searchHashTFull(DataArray, QuadraticProbingHashT);

    cout << "Quadratic (Simple):" << endl;
    printSearchStats(quadraticSimpleSearch);
    cout << "Quadratic (Prefix):" << endl;
    printSearchStats(quadraticPrefixSearch);
    cout << "Quadratic (Full):" << endl;
    printSearchStats(quadraticFullSearch);
}

// This function inserts data from the DataArray into the hash table
// The time of insertion is recorded. Stop - Start 
// The time of insertion is then returned as well as the number of collisions
// As well as the number of insertions.
Stat insertIntoHashT(vector<string> DataArray, Chaining::HashTable<string> hashT)
{
    Stat data;
    
    auto alg1st = high_resolution_clock::now();
    for (auto it = DataArray.begin(); it != DataArray.end(); ++it)
    {
        if (!hashT.contains(*it))
        {
            hashT.insert(*it);
            data.count++;
        }
        data.collisions++;
    }
    auto algsp = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}

// This function inserts data from the DataArray into the hash table
// The time of insertion is recorded. Stop - Start 
// The time of insertion is then returned as well as the number of collisions
// As well as the number of insertions.
Stat insertIntoHashT(vector<string> DataArray, Linear::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = high_resolution_clock::now();

    for (auto it = DataArray.begin(); it != DataArray.end(); ++it)
    {
        if (!hashT.contains(*it))
        {
            hashT.insert(*it);
            data.count++;
        }
        else if(hashT.contains(*it))
        {
            data.collisions++; 
        }
    }
    auto algsp = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(algsp - alg1st);

    data.timer = duration.count();
    return data;
}

// This function inserts data from the DataArray into the hash table
// The time of insertion is recorded. Stop - Start 
// The time of insertion is then returned as well as the number of collisions
// As well as the number of insertions.
Stat insertIntoHashT(vector<string> DataArray, Quadratic::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = high_resolution_clock::now();

    for (auto it = DataArray.begin(); it != DataArray.end(); ++it)
    {
        if (!hashT.contains(*it))
        {
            hashT.insert(*it);
            data.count++;
        }
       else if (hashT.contains(*it))
        {
            data.collisions++;
        }
    }
    auto algsp = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}
//This function prints the statisitcs for each insert function
//Prints the Insertion Time, Number of Insertions, Number of COllisions, Time per insertion
void printInsertStats(Stat data)
{
    cout << "Insertion Time: " << data.timer << endl
         << "Number of Insertions: " << data.count << endl
         << "Number of Collisions: " << data.collisions << endl
         << "Timer Per Insertions: " << (data.timer / data.count) << endl
         << endl;
}
//This function prints the statistics for each search function
//Prints search time, number of searches, and Timer per search
void printSearchStats(Stat data)
{
    cout << "Search Time: " << data.timer << endl
         << "Number of Searches: " << data.count << endl
         << "Time Per Search: " << (data.timer / data.count) << endl
         << endl;
}

// This function inserts data from the DataArray into the hash table
// The time of insertion is recorded. Stop - Start 
// The time of insertion is then returned as well as the number of collisions
// As well as the number of insertions.
// This function uses the hash simple method
Stat insertIntoHashTSimple(vector<string> DataArray, Quadratic::HashTable<string> hashT)
{
    Stat data;

    auto alg1st = high_resolution_clock::now();
    for (auto it = DataArray.begin(); it != DataArray.end(); ++it)
    {
        if (!hashT.contains(*it))
        {

            hashT.insert(*it, 1);
            data.count++;
        }
        else if (hashT.contains(*it))
        {
            data.collisions++;
        }
    }
    auto algsp = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}

Stat insertIntoHashTPrefix(vector<string> DataArray, Quadratic::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto it = DataArray.begin(); it != DataArray.end(); ++it)
    {
        if (!hashT.contains(*it))
        {
            hashT.insert(*it, 2);
            data.count++;
        }
        else if (hashT.contains(*it))
        {
            data.collisions++;
        }
    }
    auto algsp = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}

Stat insertIntoHashTFull(vector<string> DataArray, Quadratic::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto it = DataArray.begin(); it != DataArray.end(); ++it)
    {
        if (!hashT.contains(*it))
        {

            hashT.insert(*it, 3);

            data.count++;
        }
        else if (hashT.contains(*it))
        {
            data.collisions++;
        }
    }
    auto algsp = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}

Stat searchHashT(vector<string> QueryArray, Chaining::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto i = QueryArray.begin(); i != QueryArray.end(); ++i)
    {
        hashT.contains(*i);
        data.count++;
    }
    auto algsp = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}

Stat searchHashT(vector<string> QueryArray, Linear::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto i = QueryArray.begin(); i != QueryArray.end(); ++i)
    {
        hashT.contains(*i);
        data.count++;
    }
    auto algsp = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}

Stat searchHashT(vector<string> QueryArray, Quadratic::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto i = QueryArray.begin(); i != QueryArray.end(); ++i)
    {

        hashT.contains(*i);

        data.count++;
    }

    auto algsp = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(algsp - alg1st);
    data.timer = duration.count();
    return data;
}

Stat searchHashTSimple(vector<string> QueryArray, Quadratic::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto i = QueryArray.begin(); i != QueryArray.end(); ++i)
    {
        hashT.contains(*i, 1);
        data.count++;
    }
    auto algsp = chrono::high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(algsp - alg1st);

    data.timer = duration.count();

    return data;
}

Stat searchHashTPrefix(vector<string> QueryArray, Quadratic::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto i = QueryArray.begin(); i != QueryArray.end(); ++i)
    {
        hashT.contains(*i, 2);
        data.count++;
    }
    auto algsp = chrono::high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(algsp - alg1st);

    data.timer = duration.count();

    return data;
}

Stat searchHashTFull(vector<string> QueryArray, Quadratic::HashTable<string> hashT)
{
    Stat data;
    auto alg1st = chrono::high_resolution_clock::now();
    for (auto i = QueryArray.begin(); i != QueryArray.end(); ++i)
    {
        hashT.contains(*i, 3);
        data.count++;
    }
    auto algsp = chrono::high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(algsp - alg1st);

    data.timer = duration.count();
    return data;
}