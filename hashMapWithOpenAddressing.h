

#ifndef HASHMAP_HASHMAPWITHOPENADDRESSING_H
#define HASHMAP_HASHMAPWITHOPENADDRESSING_H


#include <string>
#include <cmath>
#include "listNode.h"

template<typename keyType, typename valType>
struct hashMapWithOpenAddressing {
    int tableSize;
    int numAddedEl;
    const double constVal = (sqrt(5) - 1) / 2;

    listNode<keyType, valType> **arrayPointer;

    hashMapWithOpenAddressing(int size);

    ~hashMapWithOpenAddressing();

    valType &operator[](keyType i);

    listNode<keyType, valType> *get(keyType key);

    valType getVal(keyType key);

    void addElement(keyType key, valType val);

    void update(keyType key, valType newVal);


    void viewMap();

    int getMaxSize();

    int getSize();

    void destroyMap();


    void addNewEllement(keyType key, valType value);

    void addExsistElement(listNode<keyType, valType> *newEl, listNode<keyType, valType> **pointerOnNewTable);

    void relocateMemory();

    int getHash(int key);

    int getHash(double key);

    int getHash(char key);

    int getHash(std::string key);

    bool isExsistInTable(keyType key);


};
#include "hashMapWithOpenAddressing.cpp"
#endif //HASHMAP_HASHMAPWITHOPENADDRESSING_H
