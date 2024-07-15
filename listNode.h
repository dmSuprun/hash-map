//
// Created by Dima on 15/07/2024.
//

#ifndef HASHMAP_LISTNODE_H
#define HASHMAP_LISTNODE_H

template<typename keyType, typename valType>
struct listNode {
    keyType keyVal;
    valType data;
    listNode<keyType, valType> *next;

    listNode(keyType keyVal, valType value);

    listNode(keyType keyVal);
};

#include "listNode.cpp"
#endif //HASHMAP_LISTNODE_H
