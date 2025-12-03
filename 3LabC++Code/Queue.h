#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

struct QNode {
    std::string data;
    QNode* next;
    QNode(std::string val) : data(val), next(nullptr) {}
};

class Queue {
private:
    QNode* head;
    QNode* tail;
    size_t size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        clear();
    }

    void push(const std::string& value) {
        QNode* newNode = new QNode(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    std::string pop() {
        if (!head) return "";
        std::string val = head->data;
        QNode* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        size--;
        return val;
    }

    std::string peek() const {
        if (!head) return "";
        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print() const {
        QNode* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void clear() {
        while (head) pop();
    }

    size_t get_size() const { return size; }
};

#endif