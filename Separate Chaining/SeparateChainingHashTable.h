/*
    An implementation of a hash-table
    using separate chaining with a linked list.

    @author: Truong Nhat Nguyen, tnhatnguyen.dev2805@gmail.com
*/

#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <iomanip>
#include <math.h>
#include "Node.h"
using namespace std;

template <typename K, typename V>
class SeparateChainingHashTable
{
private:
    // inline đảm bảo rằng biến tĩnh có thể được định nghĩa và sử dụng
    // nhiều lần trong các file biên dịch khác nhau mà không gây lỗi liên kết

    inline static constexpr int DEFAUT_CAPACITY = 11;
    inline static constexpr double DEFAUT_LOAD_FACTOR = 0.5;

    double loadFactor;

    // number of k-v pairs in the collection
    int collection_size = 0;

    // number of hash table buckets
    int table_capacity;

    // hash table array load factor (set at 50% for resizing)
    double threshold;

    // hash table array
    Node<K, V> **hash_table;

    // make empty hash table
    void make_empty();

    // Resizes the internal table holding buckets of entries
    void resizeTable();

public:
    // Hash Function
    std::hash<K> hashCode;

    // constructor
    SeparateChainingHashTable();
    SeparateChainingHashTable(int capacity);
    SeparateChainingHashTable(double loadFactor, int capacity);

    // copy constructor
    SeparateChainingHashTable(const SeparateChainingHashTable<K, V> &other);

    // hash table assignment operator
    SeparateChainingHashTable<K, V> &operator=(const SeparateChainingHashTable<K, V> &other);

    // delete a linked list
    ~SeparateChainingHashTable();

    // return number of elements currently inside the hashtable
    int size() const;

    // returns true/false depending on whether hash_table is empty
    bool isEmpty();

    // converts a hash value to an index
    int hashCodeToIndex(int hashedKey);

    // returns all of the keys in the collection
    void keys(vector<K> &all_keys);

    // insert a new key-value pair into the collection
    void insert(const K &key, const V &value);

    // remove a key-value pair from the collection
    void remove(const K &key);

    // search the value with the key in the collection
    V *search(const K &key);

    // find and return the value associated with the key
    bool find(const K &search_key, V &the_val);

    // show all key-value in the collection
    void displayTable();
};

// implement the above functions here....

template <typename K, typename V>
SeparateChainingHashTable<K, V>::SeparateChainingHashTable()
    : SeparateChainingHashTable(DEFAUT_LOAD_FACTOR, DEFAUT_CAPACITY) {}

template <typename K, typename V>
SeparateChainingHashTable<K, V>::SeparateChainingHashTable(int capacity)
    : SeparateChainingHashTable(DEFAUT_LOAD_FACTOR, capacity) {}

template <typename K, typename V>
SeparateChainingHashTable<K, V>::SeparateChainingHashTable(double loadFactor, int capacity)
{
    if (capacity < 0)
        throw invalid_argument("Capacity must be non-negative!");
    if (capacity <= 0 || isnan(loadFactor) || isinf(loadFactor))
    {
        throw invalid_argument("Load factor must be positive and finite");
    }

    this->loadFactor = loadFactor;
    this->table_capacity = max(capacity, DEFAUT_CAPACITY);
    this->threshold = (int)(table_capacity * loadFactor);

    hash_table = new Node<K, V> *[table_capacity];

    for (int i = 0; i < table_capacity; i++)
    {
        hash_table[i] = nullptr;
    }
}

template <typename K, typename V>
SeparateChainingHashTable<K, V>::SeparateChainingHashTable(const SeparateChainingHashTable<K, V> &other)
{
    *this = other;
}

template <typename K, typename V>
SeparateChainingHashTable<K, V> &SeparateChainingHashTable<K, V>::operator=(const SeparateChainingHashTable<K, V> &other)
{
    if (*this == other)
    {
        return *this;
    }

    // empty everything and then add everything form the hash table
    make_empty();

    Node<K, V> *temp;
    for (int i = 0; i < other.table_capacity; i++)
    {
        temp = other.hash_table[i];
        while (temp != nullptr)
        {
            add(temp->key, temp->value);
            temp = temp->next;
        }
    }
    return *this;
}

// destructor
template <typename K, typename V>
SeparateChainingHashTable<K, V>::~SeparateChainingHashTable()
{
    make_empty();
}

template <typename K, typename V>
int SeparateChainingHashTable<K, V>::size() const
{
    return this->collection_size;
}

template <typename K, typename V>
bool SeparateChainingHashTable<K, V>::isEmpty()
{
    return this->collection_size == 0;
}

template <typename K, typename V>
void SeparateChainingHashTable<K, V>::keys(vector<K> &all_keys)
{
    Node<K, V> *temp;
    for (int i = 0; i < table_capacity; i++)
    {
        temp = hash_table[i];
        while (temp != nullptr)
        {
            all_keys.push_back(temp->key);
            temp = temp->next;
        }
    }
}

template <typename K, typename V>
int SeparateChainingHashTable<K, V>::hashCodeToIndex(int hashedKey)
{
    // 0xFFFFFFFFFL dùng để tránh hashedKey là số âm
    return (int)((hashedKey & 0xFFFFFFFFFL) % table_capacity);
}

template <typename K, typename V>
void SeparateChainingHashTable<K, V>::insert(const K &key, const V &value)
{
    collection_size++;
    // if collection_size > 50% table_capacity then resize table
    if (collection_size > threshold)
    {
        resizeTable();
    }

    int index = hashCodeToIndex(hashCode(key));

    // push_front
    Node<K, V> *newNode = new Node<K, V>(key, value);
    newNode->next = hash_table[index];
    hash_table[index] = newNode;
}

template <typename K, typename V>
void SeparateChainingHashTable<K, V>::remove(const K &key)
{
    int index = hashCodeToIndex(hashCode(key));

    // create a temp node to hold the key and val
    Node<K, V> *firstPtr = hash_table[index];
    if (hash_table[index] == nullptr)
    {
        cout << "Data not found!" << endl;
        return;
    }
    // if node is first in bucket
    if (firstPtr->key == key)
    {
        if (firstPtr->next == nullptr) // if it is alone
        {
            delete firstPtr;
            hash_table[index] = nullptr;
        }
        else // if there is more nodes in it
        {
            hash_table[index] = firstPtr->next;
            delete firstPtr;
        }
        collection_size--;
    }
    else // if it isn't the first one
    {
        Node<K, V> *temp = hash_table[index]->next;
        while (temp != nullptr)
        {
            // if its at the end of the list
            if (temp->key == key && temp->next == nullptr)
            {
                firstPtr->next = nullptr;
                delete temp;
                collection_size--;
            }
            // if its somewhere in the middle
            else if (temp->key == key)
            {
                firstPtr->next = temp->next;
                delete temp;
                collection_size--;
            }
            temp = temp->next;
            firstPtr = firstPtr->next;
        }
    }
}

template <typename K, typename V>
V *SeparateChainingHashTable<K, V>::search(const K &key)
{
    int index = hashCodeToIndex(hashCode(key));
    Node<K, V> *temp = hash_table[index];

    while (temp != nullptr)
    {
        if (temp->key == key)
        {
            return &(temp->value);
        }
        temp = temp->next;
    }
    return nullptr;
}
template <typename K, typename V>
bool SeparateChainingHashTable<K, V>::find(const K &search_key, V &the_val)
{
    int index = hashCodeToIndex(hashCode(search_key));
    if (hash_table[index] == nullptr)
        return false;
    else
    {
        Node<K, V> *temp = hash_table[index];
        while (temp != nullptr)
        {
            if (temp->key == search_key)
            {
                the_val = temp->value;
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

template <typename K, typename V>
void SeparateChainingHashTable<K, V>::displayTable()
{
    for (int i = 0; i < table_capacity; i++)
    { // visit every node in table
        cout << "  +--------+--------+" << endl;
        cout << i << " |";
        Node<K, V> *temp = hash_table[i];
        if (temp == nullptr)
        {
            cout << " " << setw(6) << "" << " | " << setw(6) << "" << " |";
        }
        else
        {
            cout << " " << setw(6) << left << temp->key << " | " << setw(6) << right << temp->value << " |";
            for (temp = temp->next; temp != nullptr; temp = temp->next)
            {
                cout << " --> " << "[ " << temp->key << " | " << temp->value << " ]";
            }
        }

        cout << endl;
    }
    cout << "  +--------+--------+" << endl;
}

template <typename K, typename V>
void SeparateChainingHashTable<K, V>::make_empty()
{
    // go through and delete everything
    Node<K, V> *next;
    for (int i = 0; i < table_capacity; i++)
    {
        Node<K, V> *temp = hash_table[i];
        while (hash_table[i] != nullptr)
        {
            next = temp->next;
            delete temp;
            temp = next;
            hash_table[i] = temp;
        }
    }
    delete[] hash_table;
}

template <typename K, typename V>
void SeparateChainingHashTable<K, V>::resizeTable()
{
    int new_capacity;
    new_capacity = table_capacity * 2;

    // allocate memory for new table
    Node<K, V> **new_table = new Node<K, V> *[new_capacity];
    for (int i = 0; i < new_capacity; i++)
    {
        new_table[i] = nullptr;
    }

    vector<K> all_keys;
    keys(all_keys);
    V theVal;
    for (K key : all_keys)
    {
        int index = (int)((hashCode(key) & 0xFFFFFFFFFL) % new_capacity);
        bool flag = find(key, theVal);
        Node<K, V> *newNode = new Node<K, V>(key, theVal);
        // push_front
        newNode->next = new_table[index];
        new_table[index] = newNode;
    }
    make_empty();
    table_capacity = new_capacity;
    hash_table = new_table;
}