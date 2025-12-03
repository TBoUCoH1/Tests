#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <string>

class DynamicArray {
private:
    std::string* data;
    int size;
    int capacity;

    void resize() {
        int new_capacity = capacity * 2;
        std::string* new_data = new std::string[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicArray(int initial_capacity = 4) : size(0), capacity(initial_capacity) {
        if (capacity <= 0) capacity = 4;
        data = new std::string[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(const std::string& value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }

    void insert(int index, const std::string& value) {
        if (index < 0 || index > size) return;
        if (size >= capacity) resize();
        
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    std::string get(int index) const {
        if (index < 0 || index >= size) return "";
        return data[index];
    }

    void remove_at(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void set(int index, const std::string& value) {
        if (index < 0 || index >= size) return;
        data[index] = value;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void clear() {
        delete[] data;
        size = 0;
        capacity = 4;
        data = new std::string[capacity];
    }
    
    int get_size() const { return size; }
    int get_capacity() const { return capacity; }
};

#endif