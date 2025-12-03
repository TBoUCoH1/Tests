#ifndef HASHTABLEOPEN_H
#define HASHTABLEOPEN_H

#include <iostream>
#include <string>
#include <vector>

enum EntryStatus { EMPTY, OCCUPIED, DELETED };

struct HashEntry {
    std::string key;
    std::string value;
    EntryStatus status;
    HashEntry() : key(""), value(""), status(EMPTY) {}
};

class HashTableOpen {
private:
    HashEntry* table;
    int size;
    int capacity;

    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char c : key) hash = (hash * 31 + c) % capacity;
        return hash;
    }

public:
    HashTableOpen(int cap = 101) : size(0), capacity(cap) {
        table = new HashEntry[capacity];
    }

    ~HashTableOpen() {
        delete[] table;
    }

    void insert(const std::string& key, const std::string& value) {
        if (size >= capacity * 0.7) {
            std::cout << "Warning: Load factor high" << std::endl;
        }

        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1;

        while (table[index].status == OCCUPIED) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (originalIndex + i * i) % capacity;
            i++;
        }

        table[index].key = key;
        table[index].value = value;
        table[index].status = OCCUPIED;
        size++;
    }

    std::string get(const std::string& key) const {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1;

        while (table[index].status != EMPTY) {
            if (table[index].status == OCCUPIED && table[index].key == key) {
                return table[index].value;
            }
            index = (originalIndex + i * i) % capacity;
            i++;
            if (i > capacity) break;
        }
        return ""; 
    }

    void remove(const std::string& key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1;

        while (table[index].status != EMPTY) {
            if (table[index].status == OCCUPIED && table[index].key == key) {
                table[index].status = DELETED;
                size--;
                return;
            }
            index = (originalIndex + i * i) % capacity;
            i++;
        }
    }
    
    void print_stats() const {
        std::cout << "Size: " << size << ", Capacity: " << capacity 
                  << ", Load Factor: " << (double)size/capacity << std::endl;
    }

    void print() const {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].status == OCCUPIED) {
                std::cout << "[" << i << "] " << table[i].key << " => " << table[i].value << std::endl;
            }
        }
    }

    void clear() {
        for (int i = 0; i < capacity; ++i) {
            table[i].status = EMPTY;
            table[i].key = "";
            table[i].value = "";
        }
        size = 0;
    }

    std::vector<std::string> getAllKeys() const {
        std::vector<std::string> keys;
        for (int i = 0; i < capacity; ++i) {
            if (table[i].status == OCCUPIED) {
                keys.push_back(table[i].key);
            }
        }
        return keys;
    }
};

#endif