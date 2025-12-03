#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#include <iostream>
#include <string>

struct FNode {
    std::string key;
    FNode* next;
    FNode(std::string k, FNode* n = nullptr) : key(k), next(n) {}
};

class SinglyLinkedList {
private:
    FNode* head;
    size_t size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    ~SinglyLinkedList() {
        clear();
    }

    void push_front(const std::string& key) {
        head = new FNode(key, head);
        size++;
    }

    void push_back(const std::string& key) {
        if (!head) {
            push_front(key);
            return;
        }
        FNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new FNode(key);
        size++;
    }

    void pop_front() {
        if (!head) return;
        FNode* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void remove_value(const std::string& value) {
        if (!head) return;
        if (head->key == value) {
            pop_front();
            return;
        }
        FNode* current = head;
        while (current->next && current->next->key != value) {
            current = current->next;
        }
        if (current->next) {
            FNode* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
            size--;
        }
    }

    FNode* find(const std::string& value) const {
        FNode* temp = head;
        while (temp) {
            if (temp->key == value) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            size--;
            return;
        }
        FNode* temp = head;
        while (temp->next->next)
            temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
        size--;
    }

    bool insert_after(const std::string& target, const std::string& key) {
        FNode* node = find(target);
        if (!node) return false;
        node->next = new FNode(key, node->next);
        size++;
        return true;
    }

    bool insert_before(const std::string& target, const std::string& key) {
        if (!head) return false;
        if (head->key == target) {
            push_front(key);
            return true;
        }
        FNode* prev = head;
        FNode* curr = head->next;
        while (curr && curr->key != target) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return false;
        prev->next = new FNode(key, curr);
        size++;
        return true;
    }

    bool delete_after(const std::string& target) {
        FNode* node = find(target);
        if (!node || !node->next) return false;
        FNode* toDelete = node->next;
        node->next = toDelete->next;
        delete toDelete;
        size--;
        return true;
    }

    bool delete_before(const std::string& target) {
        if (!head || head->key == target) return false;
        FNode* prevPrev = nullptr;
        FNode* prev = head;
        FNode* curr = head->next;
        while (curr && curr->key != target) {
            prevPrev = prev;
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return false;
        if (!prevPrev) {
            pop_front();
        } else {
            prevPrev->next = curr;
            delete prev;
            size--;
        }
        return true;
    }

    void print() const {
        FNode* temp = head;
        while (temp) {
            std::cout << "\"" << temp->key << "\" ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void print_recursive(FNode* node) const {
        if (!node) {
            std::cout << std::endl;
            return;
        }
        std::cout << "\"" << node->key << "\" ";
        print_recursive(node->next);
    }

    void clear() {
        while (head) pop_front();
    }

    bool isEmpty() const { return head == nullptr; }

    FNode* getHead() const { return head; }
    size_t get_size() const { return size; }
};

#endif