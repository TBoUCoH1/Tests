#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <fstream>
#include <string>
#include <stdexcept>
#include "DynamicArray.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "HashTable.h"
#include "HashTableOpen.h"
#include "BinarySearchTree.h"
#include "Stack.h"
#include "Queue.h"

// DYNAMIC ARRAY SERIALIZATION

// Текстовый формат
inline void saveToText(const DynamicArray& arr, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    int size = arr.get_size();
    file << size << "\n";
    for (int i = 0; i < size; ++i) {
        file << arr.get(i) << "\n";
    }
    file.close();
}

inline void loadFromText(DynamicArray& arr, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    arr.clear();
    int size;
    file >> size;
    file.ignore();
    
    std::string line;
    for (int i = 0; i < size; ++i) {
        std::getline(file, line);
        arr.push_back(line);
    }
    file.close();
}

// Бинарный формат
inline void saveToBinary(const DynamicArray& arr, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    int size = arr.get_size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; ++i) {
        std::string str = arr.get(i);
        int len = str.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(str.c_str(), len);
    }
    file.close();
}

inline void loadFromBinary(DynamicArray& arr, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    arr.clear();
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; ++i) {
        int len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string str(len, '\0');
        file.read(&str[0], len);
        arr.push_back(str);
    }
    file.close();
}

// SINGLY LINKED LIST SERIALIZATION

// Текстовый формат
inline void saveToText(const SinglyLinkedList& list, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    FNode* temp = list.getHead();
    int count = 0;
    FNode* counter = temp;
    while (counter) { count++; counter = counter->next; }
    
    file << count << "\n";
    while (temp) {
        file << temp->key << "\n";
        temp = temp->next;
    }
    file.close();
}

inline void loadFromText(SinglyLinkedList& list, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    list.clear();
    int size;
    file >> size;
    file.ignore();
    
    std::string line;
    for (int i = 0; i < size; ++i) {
        std::getline(file, line);
        list.push_back(line);
    }
    file.close();
}

// Бинарный формат
inline void saveToBinary(const SinglyLinkedList& list, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    FNode* temp = list.getHead();
    int count = 0;
    FNode* counter = temp;
    while (counter) { count++; counter = counter->next; }
    
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    while (temp) {
        int len = temp->key.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(temp->key.c_str(), len);
        temp = temp->next;
    }
    file.close();
}

inline void loadFromBinary(SinglyLinkedList& list, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    list.clear();
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; ++i) {
        int len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string str(len, '\0');
        file.read(&str[0], len);
        list.push_back(str);
    }
    file.close();
}

// DOUBLY LINKED LIST SERIALIZATION

// Текстовый формат
inline void saveToText(const DoublyLinkedList& list, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    LNode* temp = list.getHead();
    int count = 0;
    LNode* counter = temp;
    while (counter) { count++; counter = counter->next; }
    
    file << count << "\n";
    while (temp) {
        file << temp->data << "\n";
        temp = temp->next;
    }
    file.close();
}

inline void loadFromText(DoublyLinkedList& list, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    list.clear();
    int size;
    file >> size;
    file.ignore();
    
    std::string line;
    for (int i = 0; i < size; ++i) {
        std::getline(file, line);
        list.push_back(line);
    }
    file.close();
}

// Бинарный формат
inline void saveToBinary(const DoublyLinkedList& list, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    LNode* temp = list.getHead();
    int count = 0;
    LNode* counter = temp;
    while (counter) { count++; counter = counter->next; }
    
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    while (temp) {
        int len = temp->data.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(temp->data.c_str(), len);
        temp = temp->next;
    }
    file.close();
}

inline void loadFromBinary(DoublyLinkedList& list, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    list.clear();
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; ++i) {
        int len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string str(len, '\0');
        file.read(&str[0], len);
        list.push_back(str);
    }
    file.close();
}

// STACK SERIALIZATION

// Текстовый формат
inline void saveToText(Stack& stack, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    Stack temp;
    int count = 0;
    
    while (!stack.isEmpty()) {
        temp.push(stack.pop());
        count++;
    }
    
    std::string* items = new std::string[count];
    int idx = 0;
    while (!temp.isEmpty()) {
        items[idx++] = temp.pop();
    }
    
    for (int i = count - 1; i >= 0; --i) {
        stack.push(items[i]);
    }
    
    file << count << "\n";
    for (int i = count - 1; i >= 0; --i) {
        file << items[i] << "\n";
    }
    
    delete[] items;
    file.close();
}

inline void loadFromText(Stack& stack, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    while (!stack.isEmpty()) stack.pop();
    
    int size;
    file >> size;
    file.ignore();
    
    std::string* items = new std::string[size];
    for (int i = 0; i < size; ++i) {
        std::getline(file, items[i]);
    }
    
    for (int i = size - 1; i >= 0; --i) {
        stack.push(items[i]);
    }
    delete[] items;
    file.close();
}

// Бинарный формат
inline void saveToBinary(Stack& stack, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    Stack temp;
    int count = 0;
    
    while (!stack.isEmpty()) {
        temp.push(stack.pop());
        count++;
    }
    
    std::string* items = new std::string[count];
    int idx = 0;
    while (!temp.isEmpty()) {
        items[idx++] = temp.pop();
    }
    
    for (int i = count - 1; i >= 0; --i) {
        stack.push(items[i]);
    }
    
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (int i = count - 1; i >= 0; --i) {
        int len = items[i].length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(items[i].c_str(), len);
    }
    
    delete[] items;
    file.close();
}

inline void loadFromBinary(Stack& stack, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    while (!stack.isEmpty()) stack.pop();
    
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    std::string* items = new std::string[size];
    for (int i = 0; i < size; ++i) {
        int len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        items[i].resize(len);
        file.read(&items[i][0], len);
    }
    
    for (int i = size - 1; i >= 0; --i) {
        stack.push(items[i]);
    }
    delete[] items;
    file.close();
}

// QUEUE SERIALIZATION

// Текстовый формат
inline void saveToText(Queue& queue, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    Queue temp;
    int count = 0;
    
    while (!queue.isEmpty()) {
        std::string val = queue.pop();
        temp.push(val);
        count++;
    }
    
    file << count << "\n";
    while (!temp.isEmpty()) {
        std::string val = temp.pop();
        file << val << "\n";
        queue.push(val);
    }
    file.close();
}

inline void loadFromText(Queue& queue, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    while (!queue.isEmpty()) queue.pop();
    
    int size;
    file >> size;
    file.ignore();
    
    std::string line;
    for (int i = 0; i < size; ++i) {
        std::getline(file, line);
        queue.push(line);
    }
    file.close();
}

// Бинарный формат
inline void saveToBinary(Queue& queue, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    Queue temp;
    int count = 0;
    
    while (!queue.isEmpty()) {
        std::string val = queue.pop();
        temp.push(val);
        count++;
    }
    
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    while (!temp.isEmpty()) {
        std::string val = temp.pop();
        int len = val.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(val.c_str(), len);
        queue.push(val);
    }
    file.close();
}

inline void loadFromBinary(Queue& queue, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    while (!queue.isEmpty()) queue.pop();
    
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; ++i) {
        int len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string str(len, '\0');
        file.read(&str[0], len);
        queue.push(str);
    }
    file.close();
}

// HASH TABLE (CHAINING) SERIALIZATION

// Текстовый формат
inline void saveToText(const HashTable& ht, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    int count = 0;
    for (int i = 0; i < 101; ++i) {
        FNode* temp = ht.getBucket(i).getHead();
        while (temp) { count++; temp = temp->next; }
    }
    
    file << count << "\n";
    for (int i = 0; i < 101; ++i) {
        FNode* temp = ht.getBucket(i).getHead();
        while (temp) {
            file << temp->key << "\n";
            temp = temp->next;
        }
    }
    file.close();
}

inline void loadFromText(HashTable& ht, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    ht.clear();
    int size;
    file >> size;
    file.ignore();
    
    std::string line;
    for (int i = 0; i < size; ++i) {
        std::getline(file, line);
        ht.insert(line, "");
    }
    file.close();
}

// Бинарный формат
inline void saveToBinary(const HashTable& ht, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    int count = 0;
    for (int i = 0; i < 101; ++i) {
        FNode* temp = ht.getBucket(i).getHead();
        while (temp) { count++; temp = temp->next; }
    }
    
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (int i = 0; i < 101; ++i) {
        FNode* temp = ht.getBucket(i).getHead();
        while (temp) {
            int len = temp->key.length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(len));
            file.write(temp->key.c_str(), len);
            temp = temp->next;
        }
    }
    file.close();
}

inline void loadFromBinary(HashTable& ht, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    ht.clear();
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; ++i) {
        int len;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string str(len, '\0');
        file.read(&str[0], len);
        ht.insert(str, "");
    }
    file.close();
}

// HASH TABLE OPEN ADDRESSING SERIALIZATION

// Текстовый формат
inline void saveToText(const HashTableOpen& ht, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    auto keys = ht.getAllKeys();
    file << keys.size() << "\n";
    for (const auto& key : keys) {
        file << key << "\n" << ht.get(key) << "\n";
    }
    file.close();
}

inline void loadFromText(HashTableOpen& ht, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    ht.clear();
    int size;
    file >> size;
    file.ignore();
    
    for (int i = 0; i < size; ++i) {
        std::string key, value;
        std::getline(file, key);
        std::getline(file, value);
        ht.insert(key, value);
    }
    file.close();
}

// Бинарный формат
inline void saveToBinary(const HashTableOpen& ht, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    auto keys = ht.getAllKeys();
    int count = keys.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& key : keys) {
        int keyLen = key.length();
        file.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
        file.write(key.c_str(), keyLen);
        
        std::string value = ht.get(key);
        int valLen = value.length();
        file.write(reinterpret_cast<const char*>(&valLen), sizeof(valLen));
        file.write(value.c_str(), valLen);
    }
    file.close();
}

inline void loadFromBinary(HashTableOpen& ht, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    
    ht.clear();
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; ++i) {
        int keyLen;
        file.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
        std::string key(keyLen, '\0');
        file.read(&key[0], keyLen);
        
        int valLen;
        file.read(reinterpret_cast<char*>(&valLen), sizeof(valLen));
        std::string value(valLen, '\0');
        file.read(&value[0], valLen);
        
        ht.insert(key, value);
    }
    file.close();
}

// BINARY SEARCH TREE SERIALIZATION

namespace BSTSerializer {
    inline void saveNodeText(std::ofstream& file, TreeNode* node) {
        if (node == nullptr) {
            file << "#\n";
            return;
        }
        file << node->key << "\n";
        saveNodeText(file, node->left);
        saveNodeText(file, node->right);
    }
    
    inline TreeNode* loadNodeText(std::ifstream& file) {
        std::string line;
        if (!std::getline(file, line) || line == "#") {
            return nullptr;
        }
        int key = std::stoi(line);
        TreeNode* node = new TreeNode(key);
        node->left = loadNodeText(file);
        node->right = loadNodeText(file);
        return node;
    }
    
    inline void saveNodeBinary(std::ofstream& file, TreeNode* node) {
        if (node == nullptr) {
            int marker = -2147483648;
            file.write(reinterpret_cast<const char*>(&marker), sizeof(marker));
            return;
        }
        int key = node->key;
        file.write(reinterpret_cast<const char*>(&key), sizeof(key));
        saveNodeBinary(file, node->left);
        saveNodeBinary(file, node->right);
    }
    
    inline TreeNode* loadNodeBinary(std::ifstream& file) {
        int key;
        file.read(reinterpret_cast<char*>(&key), sizeof(key));
        if (key == -2147483648) {
            return nullptr;
        }
        TreeNode* node = new TreeNode(key);
        node->left = loadNodeBinary(file);
        node->right = loadNodeBinary(file);
        return node;
    }
}

// Текстовый формат
inline void saveToText(const BinarySearchTree& bst, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    BSTSerializer::saveNodeText(file, bst.getRoot());
    file.close();
}

inline void loadFromText(BinarySearchTree& bst, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    bst.clear();
    bst.setRoot(BSTSerializer::loadNodeText(file));
    file.close();
}

// Бинарный формат
inline void saveToBinary(const BinarySearchTree& bst, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    BSTSerializer::saveNodeBinary(file, bst.getRoot());
    file.close();
}

inline void loadFromBinary(BinarySearchTree& bst, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);
    bst.clear();
    bst.setRoot(BSTSerializer::loadNodeBinary(file));
    file.close();
}

#endif
