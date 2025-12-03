#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include "SinglyList.h"

class HashTable {
private:
    static const int TABLE_SIZE = 101;
    SinglyLinkedList* buckets;
    int size;

    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }

public:
    HashTable() : size(0) {
        buckets = new SinglyLinkedList[TABLE_SIZE];
    }

    ~HashTable() {
        delete[] buckets;
    }

    void insert(const std::string& key, const std::string& value) {
        int index = hashFunction(key);
        buckets[index].push_back(key); 
        size++;
    }

    bool contains(const std::string& key) const {
        int index = hashFunction(key);
        return buckets[index].find(key) != nullptr;
    }

    void remove(const std::string& key) {
        int index = hashFunction(key);
        buckets[index].remove_value(key);
        size--; 
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            buckets[i].clear();
        }
        size = 0;
    }

    const SinglyLinkedList& getBucket(int index) const { return buckets[index]; }
};

#endif