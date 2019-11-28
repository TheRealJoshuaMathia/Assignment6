/*
Authors: Parker Guillen, Josh Mathia
Class: Cpts 223
Project: PA#6
*/

#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include "Prime.h"
using namespace std;

// Quadratic Probing Hash table class
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
    // handle the different quadratic implementation(aim2) to check if the element is contained in the HashTable 
    bool contains(const HashedObj &x, int hashCode) const
    {
        switch (hashCode)
        {
        case 1:
            return isActive(findPosSimple(x));
        case 2:
            return isActive(findPosPrefix(x));
        case 3:
            return isActive(findPosFull(x));
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
    // This function handles the insertion of each object
    bool insert(const HashedObj &x)
    {
        // Insert x as active
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;

        if (array[currentPos].info != DELETED) // increasesize if active
            ++currentSize;

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > array.size() / 2)
            rehash();

        return true;
    }

    bool insert(const HashedObj &x, int hashCode)
    { 
        int currentPos;
        switch (hashCode)
        {
        case 1:
            currentPos = findPosSimple(x);
            break;
        case 2:
            currentPos = findPosPrefix(x);
            break;
        case 3:
            currentPos = findPosFull(x);
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
        int currentPos = defaultHash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += offset; // Compute ith probe, since current position is just plus one each time 
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    int findPosSimple(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = simpleHash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += offset; 
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    int findPosPrefix(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = prefixHash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += offset; // Compute ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    int findPosFull(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = fullHash(x);

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

        // Copy table into new rehashed table
        currentSize = 0;
        for (auto &entry : oldArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.element));
    }

    size_t defaultHash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % array.size();
    }

    size_t simpleHash(const HashedObj &x) const
    {
        int hashVal = 0;

        for (char ch : x)
            hashVal += ch;

        return hashVal % array.size();
    }

    size_t prefixHash(const HashedObj &x) const
    {
        return (x[0] + 27 * x[1] + 729 * x[2]) % array.size();
    }

    size_t fullHash(const HashedObj &x) const
    {
        unsigned int hashVal = 0;

        for (char ch : x)
            hashVal = 37 * hashVal + ch;

        return hashVal % array.size();
    }
};
}
#endif