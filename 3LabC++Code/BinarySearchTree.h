#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertRec(TreeNode* node, int key) {
        if (node == nullptr) {
            return new TreeNode(key);
        }

        if (key < node->key) {
            node->left = insertRec(node->left, key);
        } else if (key > node->key) {
            node->right = insertRec(node->right, key);
        }
        return node;
    }

    TreeNode* findRec(TreeNode* node, int key) const {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return findRec(node->left, key);
        }
        return findRec(node->right, key);
    }

    TreeNode* findMin(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* removeRec(TreeNode* node, int key) {
        if (node == nullptr) return node;

        if (key < node->key) {
            node->left = removeRec(node->left, key);
        } else if (key > node->key) {
            node->right = removeRec(node->right, key);
        } else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->key = temp->key;
            node->right = removeRec(node->right, temp->key);
        }
        return node;
    }

    void printInOrder(TreeNode* node) const {
        if (node != nullptr) {
            printInOrder(node->left);
            std::cout << node->key << " ";
            printInOrder(node->right);
        }
    }

    void clearRec(TreeNode* node) {
        if (node != nullptr) {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        clear();
    }

    void insert(int key) {
        root = insertRec(root, key);
    }

    bool contains(int key) const {
        return findRec(root, key) != nullptr;
    }

    void remove(int key) {
        root = removeRec(root, key);
    }

    void print() const {
        printInOrder(root);
        std::cout << std::endl;
    }

    void clear() {
        clearRec(root);
        root = nullptr;
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }

    TreeNode* getRoot() const { return root; }
    void setRoot(TreeNode* newRoot) { root = newRoot; }
};

#endif
