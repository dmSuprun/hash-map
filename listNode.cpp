//
// Created by Dima on 15/07/2024.
//

#include "listNode.h"
template<typename keyType, typename valType>
listNode<keyType,valType >::listNode(keyType keyVal, valType value) {
    this->keyVal = keyVal;
    this->data = value;
    next = nullptr;

}
template<typename keyType, typename valType>
listNode<keyType,valType >::listNode(keyType keyVal) {
    this->keyVal = keyVal;
    next = nullptr;

}