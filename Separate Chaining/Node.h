/*
    An implementation of a hash-table
    using separate chaining with a linked list.

    @author: Truong Nhat Nguyen, tnhatnguyen.dev2805@gmail.com
*/

#pragma once
#include <iostream>
#include <functional>
using namespace std;
template <typename K, typename V>

// linked list node structure
class Node
{
public:
    int hash;
    K key;
    V value;
    Node *next;

    // hash function
    std::hash<K> hashCode;

    // constructor
    Node(K key, V value);

    // assignment operator
    bool operator==(const Node &other);

    // operator <<
    template <typename A, typename B>
    friend ostream &operator<<(ostream &os, const Node<A, B> &node);
};

template <typename K, typename V>
Node<K, V>::Node(K key, V value)
{
    this->hash = hashCode(key);
    this->key = key;
    this->value = value;
    this->next = nullptr;
}

template <typename K, typename V>
bool Node<K, V>::operator==(const Node &other)
{
    if (hash != other.hash)
        return false;
    return key == other.key;
}

template <typename A, typename B>
ostream &operator<<(ostream &os, const Node<A, B> &node)
{
    return os << "( " << node.key << " => " << node.value << " )";
}