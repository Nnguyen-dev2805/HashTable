/*
    Open Addressing

    An implementation of a hash-table
    using linear probing with a linked list.

    @author: Truong Nhat Nguyen, tnhatnguyen.dev2805@gmail.com
*/

#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <iomanip>

using namespace std;

template <typename K, typename V>
class Node
{
public:
    K key;
    V value;
    /*
        explicit dùng để ngăn chặn các chuyển đổi ngầm định xảy ra khi tạo các constructor
        Ex:
        class MyClass{
            public: MyClass(int x) value = x;
            private : int value;
        }
        int main(){
            MyClass obj = 42;
            Nếu không có explicit thì trình biên dịch thấy rằng bạn đang cố gắng gán giá trị int (42)
            cho một đối tượng kiểu myClass nên nó sẽ tự động gọi hàm khởi tạo
            Có explicit thì nó đảm bảo rằng các chuyển đổi như vậy không xảy ra trừ khi được gọi 1 cách rõ ràng
            MyClass obj(42);
        }

    */

    // constructor
    explicit Node(K key = K(), V value = V())
    {
        // Nếu không truyền tham số nó sẽ khởi tạo bởi giá trị mặc định của K,V
        this->key = key;
        this->value = value;
    }

    friend ostream &operator<<(ostream &os, const Node &node)
    {
        os << "[" << node.key << ":" << node.value << "]";
        return os;
    }
};

template <typename K, typename V>
class LinearProbingHashTable
{
private:
    // sets ACTIVE to 0, EMPTY to 1, and DELETED to 2
    enum NodeType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

    struct HashNode
    {
        Node<K, V> data;
        NodeType nodeInfo;

        // constructor
        HashNode(const Node<K, V> &node = Node<K, V>(), NodeType status = EMPTY)
        {
            data = node;
            nodeInfo = status;
        }
    };

    vector<HashNode> hash_table;
    int collection_size;

    // return index is ACTIVE
    bool isActive(int index);

    // finds empty spot
    int linearProbe(const K &key);

    // resize table
    void resizeTable();

    // find the next prime number
    int nextPrime(int num);

    // check number is prime
    bool isPrime(int num);

public:
    // hash function
    std::hash<K> hashCode;

    // constructor
    explicit LinearProbingHashTable(int TABLE_SIZE)
    {
        collection_size = 0;
        hash_table.resize(TABLE_SIZE);
    }

    // converts a hash value to an index
    int hashCodeToIndex(int hashedKey, int step);

    // make empty hash table
    void make_empty();

    // insert a new key-value pair into the collection
    bool insert(const K &key, const V &value);

    // remove a key-value pair from the collection
    bool remove(const K &key);

    // search for a key-value pair in the collection
    bool search(const K &key,V &value);

    // show all key-value in the collection
    void displayTable();
};

template <typename K, typename V>
bool LinearProbingHashTable<K, V>::isActive(int index)
{
    return hash_table[index].nodeInfo == ACTIVE;
}

template <typename K, typename V>
int LinearProbingHashTable<K, V>::linearProbe(const K &key)
{
    int step = 0;
    int index = hashCodeToIndex(key, step);
    while (hash_table[index].nodeInfo != EMPTY && hash_table[index].data.key != key)
    {
        step++;
        index = hashCodeToIndex(key, step);
    }
    return index;
}

template <typename K, typename V>
void LinearProbingHashTable<K, V>::resizeTable()
{
    vector<HashNode> old_table = hash_table;
    hash_table.resize(nextPrime(2 * old_table.size()));
    for (auto &node : hash_table)
    {
        node.nodeInfo = EMPTY;
    }
    collection_size = 0;

    for (auto &node : old_table)
    {
        if (node.nodeInfo == ACTIVE)
        {
            insert(node.data.key, node.data.value);
        }
    }
}

template <typename K, typename V>
int LinearProbingHashTable<K, V>::nextPrime(int num)
{
    if (num % 2 == 0)
        ++num;
    while (!isPrime(num))
        num += 2;
    return num;
}

template <typename K, typename V>
bool LinearProbingHashTable<K, V>::isPrime(int num)
{
    if (num <= 1)
        return false;
    if (num <= 3)
        return true;
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    for (int i = 5; i * i <= num; i += 6)
    {
        if ((num % i) == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

template <typename K, typename V>
int LinearProbingHashTable<K, V>::hashCodeToIndex(int hashedKey, int step)
{
    return static_cast<int>(((hashedKey & 0xFFFFFFFFFL) + step) % hash_table.size());
}

template <typename K, typename V>
void LinearProbingHashTable<K, V>::make_empty()
{
    collection_size = 0;
    for (int i = 0; i < hash_table.size(); i++)
    {
        hash_table[i].nodeInfo = EMPTY;
    }
}

template <typename K, typename V>
bool LinearProbingHashTable<K, V>::insert(const K &key, const V &value)
{
    int index = linearProbe(key);

    if (isActive(index))
    {
        return false; // not add duplicate keys
    }
    hash_table[index] = HashNode(Node<K, V>(key, value), ACTIVE);
    collection_size++;
    if (collection_size > hash_table.size() / 2)
    {
        resizeTable();
    }
    return true;
}

template <typename K, typename V>
bool LinearProbingHashTable<K, V>::remove(const K &key)
{
    int index = linearProbe(key);
    if (!isActive(index))
    {
        return false;
    }
    hash_table[index].nodeInfo = DELETED;
    return true;
}

template <typename K, typename V>
void LinearProbingHashTable<K, V>::displayTable()
{
    cout << "  +--------+--------+" << endl;
    for (int i = 0; i < hash_table.size(); i++)
    {
        cout << setw(2) << i << " |";

        if (hash_table[i].nodeInfo == EMPTY)
        {
            cout << " " << setw(6) << "" << " | " << setw(6) << "" << " |";
        }
        else if (hash_table[i].nodeInfo == ACTIVE)
        {
            cout << " " << setw(6) << left << hash_table[i].data.key
                 << " | " << setw(6) << right << hash_table[i].data.value << " |";
        }
        else if (hash_table[i].nodeInfo == DELETED)
        {
            cout << " " << setw(6) << "DEL" << " | " << setw(6) << "" << " |";
        }

        cout << endl;
        cout << "  +--------+--------+" << endl;
    }
}

template <typename K, typename V>
bool LinearProbingHashTable<K, V>::search(const K &key, V &value)
{
    int index = linearProbe(key);
    if (isActive(index))
    {
        value = hash_table[index].data.value;
        return true;
    }
    return false;
}