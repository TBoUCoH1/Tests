#include <benchmark/benchmark.h>
#include <vector>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include <stack>
#include <queue>
#include <list>
#include "DynamicArray.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "HashTable.h"

// 1. Benchmark: DynamicArray vs std::vector
static void BM_DynamicArray_Push(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DynamicArray arr;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) arr.push_back("test");
    }
}
BENCHMARK(BM_DynamicArray_Push)->Range(8, 1024);

static void BM_StdVector_Push(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<std::string> vec;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) vec.push_back("test");
    }
}
BENCHMARK(BM_StdVector_Push)->Range(8, 1024);

// 2. Benchmark: SinglyList Push Front (O(1))
static void BM_SinglyList_PushFront(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        SinglyLinkedList list;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) list.push_front("test");
    }
}
BENCHMARK(BM_SinglyList_PushFront)->Range(8, 1024);

// 3. Benchmark: SinglyList Pop Back (O(n))
static void BM_SinglyList_PopBack(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        SinglyLinkedList list;
        for (int i = 0; i < state.range(0); ++i) list.push_front("test");
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) list.pop_back();
    }
}
BENCHMARK(BM_SinglyList_PopBack)->Range(8, 512);

// 4. Benchmark: SinglyList Insert After
static void BM_SinglyList_InsertAfter(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        SinglyLinkedList list;
        list.push_back("target");
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.insert_after("target", "new");
        }
    }
}
BENCHMARK(BM_SinglyList_InsertAfter)->Range(8, 1024);

// 5. Benchmark: DoublyList Push Back
static void BM_DoublyList_PushBack(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DoublyLinkedList list;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) list.push_back("test");
    }
}
BENCHMARK(BM_DoublyList_PushBack)->Range(8, 1024);

// 6. Benchmark: DoublyList vs std::list Push Back
static void BM_StdList_PushBack(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::list<std::string> list;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) list.push_back("test");
    }
}
BENCHMARK(BM_StdList_PushBack)->Range(8, 1024);

// 7. Benchmark: DoublyList Pop Back (O(1))
static void BM_DoublyList_PopBack(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DoublyLinkedList list;
        for (int i = 0; i < state.range(0); ++i) list.push_back("test");
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) list.pop_back();
    }
}
BENCHMARK(BM_DoublyList_PopBack)->Range(8, 1024);

// 8. Benchmark: DoublyList Insert After
static void BM_DoublyList_InsertAfter(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        DoublyLinkedList list;
        list.push_back("target");
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            list.insert_after("target", "new");
        }
    }
}
BENCHMARK(BM_DoublyList_InsertAfter)->Range(8, 1024);

// STACK BENCHMARKS

static void BM_MyStack_Push(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Stack s;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            s.push("data");
        }
    }
}
BENCHMARK(BM_MyStack_Push)->Range(8, 4096);

static void BM_StdStack_Push(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::stack<std::string> s;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            s.push("data");
        }
    }
}
BENCHMARK(BM_StdStack_Push)->Range(8, 4096);


// QUEUE BENCHMARKS

static void BM_MyQueue_Push(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Queue q;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            q.push("data");
        }
    }
}
BENCHMARK(BM_MyQueue_Push)->Range(8, 4096);

static void BM_StdQueue_Push(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::queue<std::string> q;
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); ++i) {
            q.push("data");
        }
    }
}
BENCHMARK(BM_StdQueue_Push)->Range(8, 4096);

BENCHMARK_MAIN();