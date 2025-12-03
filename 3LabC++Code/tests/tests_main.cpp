#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <string>
#include <algorithm>

#include "DynamicArray.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "HashTableOpen.h"
#include "BinarySearchTree.h"
#include "Serialization.h"

using namespace std;

string randomString(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(length);
    for (int i = 0; i < length; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

random_device rd;
mt19937 gen(rd());

// 1. DYNAMIC ARRAY TESTS

TEST(DynamicArrayTest, EdgeCases) {
    DynamicArray arr;
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_EQ(arr.get(0), "");
    EXPECT_EQ(arr.get(-1), "");

    arr.remove_at(0);
    EXPECT_EQ(arr.get_size(), 0);

    arr.insert(10, "fail");
    EXPECT_EQ(arr.get_size(), 0);
}

TEST(DynamicArrayTest, ResizeLogic) {
    DynamicArray arr(2);
    arr.push_back("1");
    arr.push_back("2");
    arr.push_back("3");
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr.get(2), "3");
}

TEST(DynamicArrayTest, SetAndCapacity) {
    DynamicArray arr;
    arr.push_back("A");
    arr.push_back("B");
    arr.push_back("C");
    
    arr.set(1, "X");
    EXPECT_EQ(arr.get(1), "X");
    
    arr.set(-1, "fail");
    arr.set(100, "fail");
    EXPECT_EQ(arr.get(1), "X");
    
    EXPECT_GT(arr.get_capacity(), 0);
}

TEST(DynamicArrayTest, RandomStress) {
    DynamicArray myArr;
    vector<string> stdVec;
    uniform_int_distribution<> opDist(0, 3);
    
    for (int i = 0; i < 1000; ++i) {
        int op = opDist(gen);
        string val = randomString(5);

        if (op == 0) {
            myArr.push_back(val);
            stdVec.push_back(val);
        } else if (op == 1) {
            int idx = stdVec.empty() ? 0 : rand() % stdVec.size();
            myArr.insert(idx, val);
            stdVec.insert(stdVec.begin() + idx, val);
        } else if (op == 2) {
            if (!stdVec.empty()) {
                int idx = rand() % stdVec.size();
                myArr.remove_at(idx);
                stdVec.erase(stdVec.begin() + idx);
            }
        } else {
            if (!stdVec.empty()) {
                int idx = rand() % stdVec.size();
                EXPECT_EQ(myArr.get(idx), stdVec[idx]);
            }
        }
        EXPECT_EQ(myArr.get_size(), stdVec.size());
    }
    myArr.clear();
    EXPECT_EQ(myArr.get_size(), 0);
}

// 2. SINGLY LINKED LIST TESTS

TEST(SinglyListTest, BasicAndEdge) {
    SinglyLinkedList list;
    list.pop_front();
    list.remove_value("missing");
    
    list.push_front("A");
    list.push_back("B");
    
    auto node = list.find("A");
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->key, "A");
    
    node = list.find("Z");
    EXPECT_EQ(node, nullptr);
    
    list.remove_value("A");
    EXPECT_EQ(list.find("A"), nullptr);
    EXPECT_NE(list.find("B"), nullptr);
}

TEST(SinglyListTest, InsertAndDelete) {
    SinglyLinkedList list;
    
    list.push_back("A");
    list.push_back("B");
    list.push_back("C");
    EXPECT_EQ(list.get_size(), 3);
    
    EXPECT_TRUE(list.insert_after("A", "A1"));
    EXPECT_NE(list.find("A1"), nullptr);
    EXPECT_EQ(list.get_size(), 4);
    
    EXPECT_TRUE(list.insert_before("C", "B1"));
    EXPECT_NE(list.find("B1"), nullptr);
    EXPECT_EQ(list.get_size(), 5);
    
    EXPECT_TRUE(list.insert_before("A", "Z"));
    EXPECT_EQ(list.getHead()->key, "Z");
    
    EXPECT_FALSE(list.insert_after("MISSING", "X"));
    EXPECT_FALSE(list.insert_before("MISSING", "X"));
    
    EXPECT_TRUE(list.delete_after("A"));
    EXPECT_EQ(list.find("A1"), nullptr);
    
    EXPECT_TRUE(list.delete_before("C"));
    EXPECT_EQ(list.find("B1"), nullptr);
    
    EXPECT_FALSE(list.delete_after("MISSING"));
    EXPECT_FALSE(list.delete_before("MISSING"));
    EXPECT_FALSE(list.delete_before("Z"));
    
    list.clear();
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    list.pop_back();
    EXPECT_EQ(list.find("3"), nullptr);
    EXPECT_NE(list.find("2"), nullptr);
    
    list.pop_back();
    list.pop_back();
    EXPECT_TRUE(list.isEmpty());
    list.pop_back();
}

TEST(SinglyListTest, RandomStress) {
    SinglyLinkedList list;
    std::list<string> stdList;
    uniform_int_distribution<> opDist(0, 2);

    for (int i = 0; i < 500; ++i) {
        int op = opDist(gen);
        string val = randomString(3);

        if (op == 0) {
            list.push_front(val);
            stdList.push_front(val);
        } else if (op == 1) {
            list.push_back(val);
            stdList.push_back(val);
        } else {
            list.pop_front();
            if (!stdList.empty()) stdList.pop_front();
        }
    }
    if (!stdList.empty()) {
        EXPECT_NE(list.find(stdList.front()), nullptr);
    }
    list.clear();
}

// 3. DOUBLY LINKED LIST TESTS

TEST(DoublyListTest, BasicAndEdge) {
    DoublyLinkedList list;
    list.pop_back();
    
    list.push_front("A");
    list.push_back("B");
    
    list.pop_back();
    list.remove_value("A");
    
    list.push_back("C");
    list.remove_value("C");
    
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    list.remove_value("2");
    list.pop_front();
    list.pop_back();
}

TEST(DoublyListTest, InsertAndDelete) {
    DoublyLinkedList list;
    
    list.push_back("A");
    list.push_back("B");
    list.push_back("C");
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_NE(list.getTail(), nullptr);
    EXPECT_EQ(list.getTail()->data, "C");
    
    EXPECT_NE(list.find("B"), nullptr);
    EXPECT_EQ(list.find("Z"), nullptr);
    
    EXPECT_TRUE(list.insert_after("A", "A1"));
    EXPECT_NE(list.find("A1"), nullptr);
    EXPECT_EQ(list.get_size(), 4);
    
    EXPECT_TRUE(list.insert_after("C", "D"));
    EXPECT_EQ(list.getTail()->data, "D");
    
    EXPECT_TRUE(list.insert_before("B", "A2"));
    EXPECT_NE(list.find("A2"), nullptr);
    
    EXPECT_TRUE(list.insert_before("A", "Z"));
    EXPECT_EQ(list.getHead()->data, "Z");
    
    EXPECT_FALSE(list.insert_after("MISSING", "X"));
    EXPECT_FALSE(list.insert_before("MISSING", "X"));
    
    list.clear();
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    
    EXPECT_TRUE(list.delete_after("1"));
    EXPECT_EQ(list.find("2"), nullptr);
    
    list.clear();
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    
    EXPECT_TRUE(list.delete_after("2"));
    EXPECT_EQ(list.getTail()->data, "2");
    
    list.clear();
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    
    EXPECT_TRUE(list.delete_before("3"));
    EXPECT_EQ(list.find("2"), nullptr);
    
    list.clear();
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    
    EXPECT_TRUE(list.delete_before("2"));
    EXPECT_EQ(list.getHead()->data, "2");
    
    EXPECT_FALSE(list.delete_after("MISSING"));
    EXPECT_FALSE(list.delete_before("MISSING"));
    EXPECT_FALSE(list.delete_before("2"));
    EXPECT_FALSE(list.delete_after("3"));
    
    EXPECT_FALSE(list.isEmpty());
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyListTest, RandomStress) {
    DoublyLinkedList list;
    std::list<string> stdList;
    uniform_int_distribution<> opDist(0, 4);

    for (int i = 0; i < 500; ++i) {
        int op = opDist(gen);
        string val = randomString(3);

        if (op == 0) { list.push_front(val); stdList.push_front(val); }
        else if (op == 1) { list.push_back(val); stdList.push_back(val); }
        else if (op == 2) { list.pop_front(); if(!stdList.empty()) stdList.pop_front(); }
        else if (op == 3) { list.pop_back(); if(!stdList.empty()) stdList.pop_back(); }
        else {
             if (!stdList.empty()) {
                 string target = stdList.front(); 
                 list.remove_value(target);
                 auto it = find(stdList.begin(), stdList.end(), target);
                 if (it != stdList.end()) stdList.erase(it);
             }
        }
    }
    list.clear();
}

// 4. STACK TESTS

TEST(StackTest, BasicOperations) {
    Stack s;
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.pop(), "");
    
    s.push("A");
    EXPECT_FALSE(s.isEmpty());
    EXPECT_EQ(s.peek(), "A");
    
    s.push("B");
    EXPECT_EQ(s.pop(), "B");
    EXPECT_EQ(s.pop(), "A");
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, RandomStress) {
    Stack myStack;
    stack<string> stdStack;
    uniform_int_distribution<> opDist(0, 1);

    for (int i = 0; i < 1000; ++i) {
        if (opDist(gen) == 0) {
            string val = randomString(4);
            myStack.push(val);
            stdStack.push(val);
        } else {
            string v1 = myStack.pop();
            string v2 = "";
            if (!stdStack.empty()) {
                v2 = stdStack.top();
                stdStack.pop();
            }
            EXPECT_EQ(v1, v2);
        }
    }
}

// 5. QUEUE TESTS

TEST(QueueTest, BasicOperations) {
    Queue q;
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.pop(), "");
    
    q.push("A");
    q.push("B");
    
    EXPECT_EQ(q.peek(), "A");
    EXPECT_EQ(q.pop(), "A");
    EXPECT_EQ(q.peek(), "B");
    EXPECT_EQ(q.pop(), "B");
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, RandomStress) {
    Queue myQueue;
    queue<string> stdQueue;
    uniform_int_distribution<> opDist(0, 1);

    for (int i = 0; i < 1000; ++i) {
        if (opDist(gen) == 0) {
            string val = randomString(4);
            myQueue.push(val);
            stdQueue.push(val);
        } else {
            string v1 = myQueue.pop();
            string v2 = "";
            if (!stdQueue.empty()) {
                v2 = stdQueue.front();
                stdQueue.pop();
            }
            EXPECT_EQ(v1, v2);
        }
    }
}

// 6. HASH TABLE (CHAINING) TESTS

TEST(HashTableTest, BasicOperations) {
    HashTable ht;
    ht.insert("key1", "ignored");
    EXPECT_TRUE(ht.contains("key1"));
    EXPECT_FALSE(ht.contains("key2"));
    
    ht.remove("key1");
    EXPECT_FALSE(ht.contains("key1"));
    
    ht.remove("missing");
}

TEST(HashTableTest, CollisionHandling) {
    HashTable ht;
    for(int i=0; i<200; ++i) {
        ht.insert(to_string(i), "");
    }
    
    for(int i=0; i<200; ++i) {
        EXPECT_TRUE(ht.contains(to_string(i)));
    }
}

TEST(HashTableTest, RandomStress) {
    HashTable ht;
    unordered_set<string> stdSet;
    uniform_int_distribution<> opDist(0, 2);

    for (int i = 0; i < 1000; ++i) {
        int op = opDist(gen);
        string key = randomString(3);

        if (op == 0) {
            ht.insert(key, "");
            stdSet.insert(key);
        } else if (op == 1) {
            ht.remove(key);
            stdSet.erase(key);
        } else {
            EXPECT_EQ(ht.contains(key), (stdSet.find(key) != stdSet.end()));
        }
    }
    ht.clear();
}

// 7. HASH TABLE (OPEN ADDRESSING) TESTS

TEST(HashTableOpenTest, BasicOperations) {
    HashTableOpen ht;
    ht.insert("apple", "red");
    EXPECT_EQ(ht.get("apple"), "red");
    EXPECT_EQ(ht.get("banana"), "");
    
    ht.insert("apple", "green");
    EXPECT_EQ(ht.get("apple"), "green");
    
    ht.remove("apple");
    EXPECT_EQ(ht.get("apple"), "");
    
    ht.insert("a", "1");
    ht.insert("b", "2");
    ht.remove("a");
    EXPECT_EQ(ht.get("b"), "2");
}

TEST(HashTableOpenTest, StressWithLoad) {
    HashTableOpen ht(1000);
    unordered_map<string, string> stdMap;
    uniform_int_distribution<> opDist(0, 2);

    for (int i = 0; i < 500; ++i) {
        int op = opDist(gen);
        string key = randomString(3);
        string val = randomString(3);

        if (op == 0) {
            ht.insert(key, val);
            stdMap[key] = val;
        } else if (op == 1) {
            ht.remove(key);
            stdMap.erase(key);
        } else {
            string res = ht.get(key);
            if (stdMap.find(key) != stdMap.end()) {
                EXPECT_EQ(res, stdMap[key]);
            } else {
                EXPECT_EQ(res, "");
            }
        }
    }
}

// 8. BINARY SEARCH TREE TESTS

TEST(BSTTest, BasicOperations) {
    BinarySearchTree bst;
    EXPECT_TRUE(bst.isEmpty());
    
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    
    EXPECT_TRUE(bst.contains(30));
    EXPECT_FALSE(bst.contains(99));
    
    bst.remove(30);
    EXPECT_FALSE(bst.contains(30));
    
    bst.remove(50);
    EXPECT_FALSE(bst.contains(50));
    EXPECT_TRUE(bst.contains(70));
}

// BST COVERAGE BOOSTER

TEST(BSTTest, CoverageHardCases) {
    {
        BinarySearchTree t;
        t.insert(10);
        t.insert(20); 
        t.remove(10);
        EXPECT_FALSE(t.contains(10));
        EXPECT_TRUE(t.contains(20));
    }

    {
        BinarySearchTree t;
        t.insert(10);
        t.insert(5);
        t.remove(10);
        EXPECT_FALSE(t.contains(10));
        EXPECT_TRUE(t.contains(5));
    }

    {
        BinarySearchTree t;
        t.insert(50);
        t.insert(30);
        t.insert(70);
        t.insert(20);
        t.insert(40);
        t.remove(30);
        EXPECT_FALSE(t.contains(30));
        EXPECT_TRUE(t.contains(20));
        EXPECT_TRUE(t.contains(40));
        EXPECT_TRUE(t.contains(50));
    }
    
    {
        BinarySearchTree t;
        t.insert(2);
        t.insert(1);
        t.insert(3);
        testing::internal::CaptureStdout();
        t.print();
        string output = testing::internal::GetCapturedStdout();
        EXPECT_NE(output, "");
    }
}

TEST(BSTTest, RandomStress) {
    BinarySearchTree bst;
    set<int> stdSet;
    uniform_int_distribution<> opDist(0, 2);
    uniform_int_distribution<> valDist(1, 1000);

    for (int i = 0; i < 1000; ++i) {
        int op = opDist(gen);
        int val = valDist(gen);

        if (op == 0) {
            bst.insert(val);
            stdSet.insert(val);
        } else if (op == 1) {
            bst.remove(val);
            stdSet.erase(val);
        } else {
            EXPECT_EQ(bst.contains(val), (stdSet.find(val) != stdSet.end()));
        }
    }
    bst.clear();
    EXPECT_TRUE(bst.isEmpty());
}


// 9. SERIALIZATION TESTS


TEST(SerializationTest, DynamicArrayTextFormat) {
    DynamicArray arr;
    arr.push_back("hello");
    arr.push_back("world");
    arr.push_back("test");
    
    saveToText(arr, "test_array.txt");
    
    DynamicArray arr2;
    loadFromText(arr2, "test_array.txt");
    
    EXPECT_EQ(arr2.get_size(), 3);
    EXPECT_EQ(arr2.get(0), "hello");
    EXPECT_EQ(arr2.get(1), "world");
    EXPECT_EQ(arr2.get(2), "test");
}

TEST(SerializationTest, DynamicArrayBinaryFormat) {
    DynamicArray arr;
    arr.push_back("binary");
    arr.push_back("data");
    
    saveToBinary(arr, "test_array.bin");
    
    DynamicArray arr2;
    loadFromBinary(arr2, "test_array.bin");
    
    EXPECT_EQ(arr2.get_size(), 2);
    EXPECT_EQ(arr2.get(0), "binary");
    EXPECT_EQ(arr2.get(1), "data");
}

TEST(SerializationTest, SinglyListTextFormat) {
    SinglyLinkedList list;
    list.push_back("one");
    list.push_back("two");
    list.push_back("three");
    
    saveToText(list, "test_singly.txt");
    
    SinglyLinkedList list2;
    loadFromText(list2, "test_singly.txt");
    
    EXPECT_NE(list2.find("one"), nullptr);
    EXPECT_NE(list2.find("two"), nullptr);
    EXPECT_NE(list2.find("three"), nullptr);
}

TEST(SerializationTest, SinglyListBinaryFormat) {
    SinglyLinkedList list;
    list.push_back("alpha");
    list.push_back("beta");
    
    saveToBinary(list, "test_singly.bin");
    
    SinglyLinkedList list2;
    loadFromBinary(list2, "test_singly.bin");
    
    EXPECT_NE(list2.find("alpha"), nullptr);
    EXPECT_NE(list2.find("beta"), nullptr);
}

TEST(SerializationTest, DoublyListTextFormat) {
    DoublyLinkedList list;
    list.push_back("first");
    list.push_back("second");
    
    saveToText(list, "test_doubly.txt");
    
    DoublyLinkedList list2;
    loadFromText(list2, "test_doubly.txt");
    
    LNode* head = list2.getHead();
    EXPECT_NE(head, nullptr);
    EXPECT_EQ(head->data, "first");
}

TEST(SerializationTest, DoublyListBinaryFormat) {
    DoublyLinkedList list;
    list.push_back("x");
    list.push_back("y");
    list.push_back("z");
    
    saveToBinary(list, "test_doubly.bin");
    
    DoublyLinkedList list2;
    loadFromBinary(list2, "test_doubly.bin");
    
    LNode* head = list2.getHead();
    EXPECT_NE(head, nullptr);
    EXPECT_EQ(head->data, "x");
}

TEST(SerializationTest, StackTextFormat) {
    Stack s;
    s.push("bottom");
    s.push("middle");
    s.push("top");
    
    saveToText(s, "test_stack.txt");
    
    Stack s2;
    loadFromText(s2, "test_stack.txt");
    
    EXPECT_EQ(s2.pop(), "top");
    EXPECT_EQ(s2.pop(), "middle");
    EXPECT_EQ(s2.pop(), "bottom");
}

TEST(SerializationTest, StackBinaryFormat) {
    Stack s;
    s.push("a");
    s.push("b");
    
    saveToBinary(s, "test_stack.bin");
    
    Stack s2;
    loadFromBinary(s2, "test_stack.bin");
    
    EXPECT_EQ(s2.pop(), "b");
    EXPECT_EQ(s2.pop(), "a");
}

TEST(SerializationTest, QueueTextFormat) {
    Queue q;
    q.push("first");
    q.push("second");
    q.push("third");
    
    saveToText(q, "test_queue.txt");
    
    Queue q2;
    loadFromText(q2, "test_queue.txt");
    
    EXPECT_EQ(q2.pop(), "first");
    EXPECT_EQ(q2.pop(), "second");
    EXPECT_EQ(q2.pop(), "third");
}

TEST(SerializationTest, QueueBinaryFormat) {
    Queue q;
    q.push("item1");
    q.push("item2");
    
    saveToBinary(q, "test_queue.bin");
    
    Queue q2;
    loadFromBinary(q2, "test_queue.bin");
    
    EXPECT_EQ(q2.pop(), "item1");
    EXPECT_EQ(q2.pop(), "item2");
}

TEST(SerializationTest, HashTableTextFormat) {
    HashTable ht;
    ht.insert("key1", "");
    ht.insert("key2", "");
    ht.insert("key3", "");
    
    saveToText(ht, "test_hashtable.txt");
    
    HashTable ht2;
    loadFromText(ht2, "test_hashtable.txt");
    
    EXPECT_TRUE(ht2.contains("key1"));
    EXPECT_TRUE(ht2.contains("key2"));
    EXPECT_TRUE(ht2.contains("key3"));
}

TEST(SerializationTest, HashTableBinaryFormat) {
    HashTable ht;
    ht.insert("abc", "");
    ht.insert("xyz", "");
    
    saveToBinary(ht, "test_hashtable.bin");
    
    HashTable ht2;
    loadFromBinary(ht2, "test_hashtable.bin");
    
    EXPECT_TRUE(ht2.contains("abc"));
    EXPECT_TRUE(ht2.contains("xyz"));
}

TEST(SerializationTest, HashTableOpenTextFormat) {
    HashTableOpen ht;
    ht.insert("name", "John");
    ht.insert("age", "30");
    
    saveToText(ht, "test_htopen.txt");
    
    HashTableOpen ht2;
    loadFromText(ht2, "test_htopen.txt");
    
    EXPECT_EQ(ht2.get("name"), "John");
    EXPECT_EQ(ht2.get("age"), "30");
}

TEST(SerializationTest, HashTableOpenBinaryFormat) {
    HashTableOpen ht;
    ht.insert("color", "red");
    ht.insert("size", "large");
    
    saveToBinary(ht, "test_htopen.bin");
    
    HashTableOpen ht2;
    loadFromBinary(ht2, "test_htopen.bin");
    
    EXPECT_EQ(ht2.get("color"), "red");
    EXPECT_EQ(ht2.get("size"), "large");
}

TEST(SerializationTest, BSTTextFormat) {
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    
    saveToText(bst, "test_bst.txt");
    
    BinarySearchTree bst2;
    loadFromText(bst2, "test_bst.txt");
    
    EXPECT_TRUE(bst2.contains(50));
    EXPECT_TRUE(bst2.contains(30));
    EXPECT_TRUE(bst2.contains(70));
    EXPECT_TRUE(bst2.contains(20));
    EXPECT_TRUE(bst2.contains(40));
}

TEST(SerializationTest, BSTBinaryFormat) {
    BinarySearchTree bst;
    bst.insert(100);
    bst.insert(50);
    bst.insert(150);
    
    saveToBinary(bst, "test_bst.bin");
    
    BinarySearchTree bst2;
    loadFromBinary(bst2, "test_bst.bin");
    
    EXPECT_TRUE(bst2.contains(100));
    EXPECT_TRUE(bst2.contains(50));
    EXPECT_TRUE(bst2.contains(150));
    EXPECT_FALSE(bst2.contains(999));
}

// 10. PRINT FUNCTIONS COVERAGE TESTS

TEST(PrintTest, DynamicArrayPrint) {
    DynamicArray arr;
    arr.push_back("A");
    arr.push_back("B");
    
    testing::internal::CaptureStdout();
    arr.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("A"), string::npos);
    EXPECT_NE(output.find("B"), string::npos);
}

TEST(PrintTest, SinglyListPrint) {
    SinglyLinkedList list;
    list.push_back("X");
    list.push_back("Y");
    
    testing::internal::CaptureStdout();
    list.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("X"), string::npos);
    EXPECT_NE(output.find("Y"), string::npos);
    
    testing::internal::CaptureStdout();
    list.print_recursive(list.getHead());
    output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("X"), string::npos);
}

TEST(PrintTest, DoublyListPrint) {
    DoublyLinkedList list;
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    
    testing::internal::CaptureStdout();
    list.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("1"), string::npos);
    EXPECT_NE(output.find("3"), string::npos);
    
    testing::internal::CaptureStdout();
    list.print_backward();
    output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("3"), string::npos);
    EXPECT_NE(output.find("1"), string::npos);
}

TEST(PrintTest, StackPrint) {
    Stack s;
    s.push("bottom");
    s.push("top");
    
    testing::internal::CaptureStdout();
    s.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("top"), string::npos);
    EXPECT_NE(output.find("bottom"), string::npos);
}

TEST(PrintTest, QueuePrint) {
    Queue q;
    q.push("first");
    q.push("last");
    
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("first"), string::npos);
    EXPECT_NE(output.find("last"), string::npos);
}

TEST(PrintTest, HashTableOpenPrint) {
    HashTableOpen ht;
    ht.insert("key", "value");
    
    testing::internal::CaptureStdout();
    ht.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
