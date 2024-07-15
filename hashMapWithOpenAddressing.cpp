#include "hashMapWithOpenAddressing.h"
#include <cmath>
#include <iostream>
using namespace std;


template<typename keyType, typename valType>
hashMapWithOpenAddressing<keyType, valType>::hashMapWithOpenAddressing(int size) {
    this->tableSize = size;
    arrayPointer = new listNode<keyType, valType> *[size];
    for (int i = 0; i < size; i++) {
        arrayPointer[i] = nullptr;
    }
    numAddedEl = 0;
}

template<typename keyType, typename valType>
hashMapWithOpenAddressing<keyType, valType>::~hashMapWithOpenAddressing() {
    if (arrayPointer) {
        destroyMap();
        arrayPointer = nullptr;
    }

}

template<typename keyType, typename valType>
valType &hashMapWithOpenAddressing<keyType, valType>::operator[](keyType i) {
    int index = getHash(i);
    listNode<keyType, valType> *temp = arrayPointer[index];
    listNode<keyType, valType> *tempBefore = nullptr;
    if (arrayPointer[index]) {
        while (temp && temp->keyVal != i) {
            tempBefore = temp;
            temp = temp->next;
        }
        if (!temp) {
            tempBefore->next = new listNode<keyType, valType>(i);
            temp = tempBefore->next;
            numAddedEl++;
        }
    } else {
        arrayPointer[index] = new listNode<keyType, valType>(i);
        temp = arrayPointer[index];
        numAddedEl++;

    }
    return temp->data;

}

template<typename keyType, typename valType>
listNode<keyType, valType> *hashMapWithOpenAddressing<keyType, valType>::get(keyType key) {
    int index = getHash(key);
    listNode<keyType, valType> *temp = arrayPointer[index];
    if (temp && temp->keyVal == key) { return temp; }
    while (temp && (temp->keyVal != key)) {
        temp = temp->next;
    }
    return temp;

}

template<typename keyType, typename valType>
valType hashMapWithOpenAddressing<keyType, valType>::getVal(keyType key) {

    return get(key)->data;
}

template<typename keyType, typename valType>
void hashMapWithOpenAddressing<keyType, valType>::addElement(keyType key, valType val) {
    if (!isExsistInTable(key)) {
        if ((float) numAddedEl / tableSize >= 0.75) {
            relocateMemory();
            addNewEllement(key, val);
        } else {
            addNewEllement(key, val);
        }
    } else {
        std::cout << get(key)->keyVal;
        std::cout << "Error!: " << key << std::endl;
        return;

    }
}

template<typename keyType, typename valType>
void hashMapWithOpenAddressing<keyType, valType>::update(keyType key, valType newVal) {
    listNode<keyType, valType> *node = get(key);
    if (node) {
        node->data = newVal;

    } else {
        addEllement(key, newVal);
    }
}

template<typename keyType, typename valType>
void hashMapWithOpenAddressing<keyType, valType>::viewMap() {
    for (int i = 0; i < tableSize; i++) {
        listNode<keyType, valType> *t = arrayPointer[i];
        cout << i << ": ";
        while (t) {
            cout << t->data << " ";
            t = t->next;
        }
        cout << endl;


    }
}

template<typename keyType, typename valType>
int hashMapWithOpenAddressing<keyType, valType>::getMaxSize() {
    return tableSize;
}

template<typename keyType, typename valType>
int hashMapWithOpenAddressing<keyType, valType>::getSize() {
    return numAddedEl;

}


template<typename keyType, typename valType>
void hashMapWithOpenAddressing<keyType, valType>::destroyMap() {
    for (int i = 0; i < tableSize; i++) {
        listNode<keyType, valType> *t = arrayPointer[i];
        while (t) {
            arrayPointer[i] = arrayPointer[i]->next;
            delete t;
            t = arrayPointer[i];
        }
    }
    delete[] arrayPointer;
}

template<typename keyType, typename valType>
void hashMapWithOpenAddressing<keyType, valType>::addNewEllement(keyType key, valType value) {
    int index = getHash(key);
    listNode<keyType, valType> *t = arrayPointer[index];
    if (t) {
        while (t->next) {
            t = t->next;
        }
        t->next = new listNode<keyType, valType>(key, value);
        numAddedEl++;

    } else {
        arrayPointer[index] = new listNode<keyType, valType>(key, value);
        numAddedEl++;
    }

}

template<typename keyType, typename valType>
void hashMapWithOpenAddressing<keyType, valType>::addExsistElement(listNode<keyType, valType> *newEl,
                                                                   listNode<keyType, valType> **pointerOnNewTable) {
    int newIndex = getHash(newEl->keyVal);
    listNode<keyType, valType> *t = pointerOnNewTable[newIndex];
    if (t) {
        while (t->next) {
            t = t->next;
        }
        t->next = newEl;

    } else {
        pointerOnNewTable[newIndex] = newEl;
    }

}

template<typename keyType, typename valType>
void hashMapWithOpenAddressing<keyType, valType>::relocateMemory() {
    listNode<keyType, valType> **newTable = nullptr;
    int oldSize = tableSize;
    tableSize = (tableSize * 2);
    newTable = new listNode<keyType, valType> *[tableSize];
    for (int i = 0; i < tableSize; i++) {
        newTable[i] = nullptr;
    }
    for (int i = 0; i < oldSize; i++) {
        listNode<keyType, valType> *temp;
        while (arrayPointer[i]) {
            temp = arrayPointer[i];
            arrayPointer[i] = arrayPointer[i]->next;
            temp->next = nullptr;
            addExsistElement(temp, newTable);

        }
    }
    delete[]arrayPointer;
    arrayPointer = newTable;
}


template<typename keyType, typename valType>
int hashMapWithOpenAddressing<keyType, valType>::getHash(int key) {
    return abs((int) tableSize * ((key * constVal) - (int) (key * constVal)));

}

template<typename keyType, typename valType>
int hashMapWithOpenAddressing<keyType, valType>::getHash(double key) {
    return abs((int) (key * 10e+6) / tableSize);

}

template<typename keyType, typename valType>
int hashMapWithOpenAddressing<keyType, valType>::getHash(char key) {
    return abs((int) key % tableSize);

}

template<typename keyType, typename valType>
int hashMapWithOpenAddressing<keyType, valType>::getHash(string key) {
    unsigned long int hashSum = 0;
    for (int i = 0; i < key.size(); i++) {
        hashSum += getHash((int) key[i]);
    }
    return hashSum % tableSize;

}

template<typename keyType, typename valType>
bool hashMapWithOpenAddressing<keyType, valType>::isExsistInTable(keyType key) {
    if (!get(key)) {
        return false;
    } else {
        return true;
    }
}











