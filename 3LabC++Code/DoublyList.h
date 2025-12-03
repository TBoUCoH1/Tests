#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>
#include <string>

struct LNode {
    std::string data;
    LNode* next;
    LNode* prev;
    LNode(const std::string& val, LNode* nxt = nullptr, LNode* prv = nullptr) 
        : data(val), next(nxt), prev(prv) {}
};

class DoublyLinkedList {
private:
    LNode* head;
    LNode* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void push_front(const std::string& value) {
        LNode* newNode = new LNode(value, head, nullptr);
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
        size++;
    }

    void push_back(const std::string& value) {
        if (!tail) {
            push_front(value);
            return;
        }
        LNode* newNode = new LNode(value, nullptr, tail);
        tail->next = newNode;
        tail = newNode;
        size++;
    }

    void pop_front() {
        if (!head) return;
        LNode* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }

    void pop_back() {
        if (!tail) return;
        LNode* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        size--;
    }

    void remove_value(const std::string& value) {
        LNode* current = head;
        while (current) {
            if (current->data == value) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;
                
                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;

                delete current;
                size--;
                return;
            }
            current = current->next;
        }
    }

    LNode* find(const std::string& value) const {
        LNode* temp = head;
        while (temp) {
            if (temp->data == value) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    bool insert_after(const std::string& target, const std::string& value) {
        LNode* targetNode = find(target);
        if (!targetNode) return false;

        LNode* newNode = new LNode(value, targetNode->next, targetNode);
        
        if (targetNode->next) {
            targetNode->next->prev = newNode;
        } else {
            tail = newNode;
        }
        targetNode->next = newNode;
        size++;
        return true;
    }

    bool insert_before(const std::string& target, const std::string& value) {
        LNode* targetNode = find(target);
        if (!targetNode) return false;

        if (targetNode == head) {
            push_front(value);
            return true;
        }

        LNode* newNode = new LNode(value, targetNode, targetNode->prev);
        targetNode->prev->next = newNode;
        targetNode->prev = newNode;
        size++;
        return true;
    }

    bool delete_after(const std::string& target) {
        LNode* targetNode = find(target);
        if (!targetNode || !targetNode->next) return false;

        LNode* nodeToDelete = targetNode->next;
        targetNode->next = nodeToDelete->next;

        if (nodeToDelete->next) {
            nodeToDelete->next->prev = targetNode;
        } else {
            tail = targetNode;
        }
        delete nodeToDelete;
        size--;
        return true;
    }

    bool delete_before(const std::string& target) {
        LNode* targetNode = find(target);
        if (!targetNode || !targetNode->prev) return false;

        LNode* nodeToDelete = targetNode->prev;
        targetNode->prev = nodeToDelete->prev;

        if (nodeToDelete->prev) {
            nodeToDelete->prev->next = targetNode;
        } else {
            head = targetNode;
        }
        delete nodeToDelete;
        size--;
        return true;
    }

    void print() const {
        LNode* temp = head;
        while (temp) {
            std::cout << temp->data << " <-> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    void print_backward() const {
        LNode* temp = tail;
        while (temp) {
            std::cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        std::cout << "NULL" << std::endl;
    }

    void clear() {
        while (head) pop_front();
    }

    bool isEmpty() const { return head == nullptr; }

    LNode* getHead() const { return head; }
    LNode* getTail() const { return tail; }
    size_t get_size() const { return size; }
};

#endif