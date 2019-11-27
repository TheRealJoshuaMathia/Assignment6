#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include "Prime.h"
using namespace std;

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

namespace Quadratic
{
template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable(int size = 101) : array(nextPrime(size)) 
    { 
        makeEmpty(); 
    }

    //checks status of the array index
    bool contains(const HashedObj &x)const
    {
        return isActive(findPos(x));
    }
    // handle the different quadratic implementation(aim2 to check if the element is contained in the HashTable 
    bool contains(const HashedObj &x, int hash_code) const
    {
        switch (hash_code)
        {
        case 1:
            return isActive(findPos_simple(x));
        case 2:
            return isActive(findPos_prefix(x));
        case 3:
            return isActive(findPos_full(x));
        default:
            return isActive(findPos(x));
        }
    }
    //Makes the function empty
    void makeEmpty()
    {
        currentSize = 0;
        for (auto &entry : array)
            entry.info = EMPTY;
    }
    // This function handles the insertion of each element
    bool insert(const HashedObj &x)
    {
        // Insert x as active
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;

        if (array[currentPos].info != DELETED)
            ++currentSize;

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > array.size() / 2)
            rehash();

        return true;
    }

    bool insert(const HashedObj &x, int hash_code)
    { // HASH CODE = 1: simple; 2: prefix; 3: full
        int currentPos;
        // Insert x as active
        switch (hash_code)
        {
        case 1:
            currentPos = findPos_simple(x);
            break;
        case 2:
            currentPos = findPos_prefix(x);
            break;
        case 3:
            currentPos = findPos_full(x);
            break;
        default:
            currentPos = findPos(x);
        }

        if (isActive(currentPos))
            return false;

        if (array[currentPos].info != DELETED)
            ++currentSize;

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > array.size() / 2)
            rehash();

        return true;
    }

    bool insert(HashedObj &&x)
    {
        // Insert x as active
        int currentPos = findPos(x);
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

    bool remove(const HashedObj &x)
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

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
            : element{e}, info{i} {}

        HashEntry(HashedObj &&e, EntryType i = EMPTY)
            : element{std::move(e)}, info{i} {}
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    int findPos(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = default_hash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += offset; // Compute ith probe, since current position is just plus one each time 
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    int findPos_simple(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = simple_hash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += offset; // Compute ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    int findPos_prefix(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = prefix_hash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += offset; // Compute ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    int findPos_full(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = full_hash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += offset; // Compute ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    void rehash()
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize(nextPrime(2 * oldArray.size()));
        for (auto &entry : array)
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for (auto &entry : oldArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.element));
    }

    size_t default_hash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % array.size();
    }

    size_t simple_hash(const HashedObj &x) const
    {
        int hashVal = 0;

        for (char ch : x)
            hashVal += ch;

        return hashVal % array.size();
    }

    size_t prefix_hash(const HashedObj &x) const
    {
        return (x[0] + 27 * x[1] + 729 * x[2]) % array.size();
    }

    size_t full_hash(const HashedObj &x) const
    {
        unsigned int hashVal = 0;

        for (char ch : x)
            hashVal = 37 * hashVal + ch;

        return hashVal % array.size();
    }
};
}
#endif