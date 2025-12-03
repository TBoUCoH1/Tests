#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

struct SNode {
    std::string data;
    SNode* next;
    SNode(const std::string& val, SNode* nxt = nullptr) : data(val), next(nxt) {}
};

class Stack {
private:
    SNode* top;
    size_t size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        clear();
    }

    void push(const std::string& value) {
        top = new SNode(value, top);
        size++;
    }

    std::string pop() {
        if (!top) return "";
        std::string val = top->data;
        SNode* temp = top;
        top = top->next;
        delete temp;
        size--;
        return val;
    }

    std::string peek() const {
        if (!top) return "";
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void print() const {
        SNode* temp = top;
        while (temp) {
            std::cout << temp->data << std::endl;
            temp = temp->next;
        }
    }

    void clear() {
        while (top) pop();
    }

    size_t get_size() const { return size; }
};

#endif