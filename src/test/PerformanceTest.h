#ifndef PERFORMANCE_TEST_H
#define PERFORMANCE_TEST_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include "../entities/header/Book.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief Structure to hold performance test results
 */
struct TestResult
{
    string testName;
    int inputSize;
    double averageTime; // in milliseconds
    bool passed;
    string expectedComplexity;
};

/**
 * @brief Structure to hold a single timing measurement
 */
struct TimingResult
{
    double time; // in milliseconds
    bool success;
};

/**
 * @brief Performance testing and validation class
 * Tests correctness and measures efficiency of data structures and algorithms
 */
class PerformanceTest
{
private:
    vector<TestResult> results;
    static const int NUM_RUNS = 3; // Number of runs for averaging

    // Test data generation
    vector<Book> generateBooks(int count);
    vector<string> generateRandomStrings(int count);

    // Timing utilities
    template <typename Func>
    double measureTime(Func func);

    double averageTimings(const vector<double> &timings);

public:
    PerformanceTest();

    // === CORRECTNESS TESTS (Test Case Validation) ===

    /**
     * @brief Test Case 1: Hash Table Insert and Search Correctness
     * Validates that hash table correctly stores and retrieves books
     * @return true if all assertions pass
     */
    bool testHashTableCorrectness();

    /**
     * @brief Test Case 2: Merge Sort Correctness
     * Validates that merge sort correctly orders books by different criteria
     * @return true if sorting produces correct order
     */
    bool testMergeSortCorrectness();

    /**
     * @brief Test Case 3: Trie Autocomplete Correctness
     * Validates that trie returns correct prefix matches
     * @return true if autocomplete returns expected results
     */
    bool testTrieCorrectness();

    // === PERFORMANCE TESTS (Efficiency Measurement) ===

    /**
     * @brief Performance Test 1: Hash Table Operations
     * Tests insert and search on N = 10³, 10⁴, 10⁵
     * Expected: O(1) average case for insert and search
     */
    void benchmarkHashTable();

    /**
     * @brief Performance Test 2: Merge Sort
     * Tests sorting on N = 10³, 10⁴, 10⁵
     * Expected: O(n log n)
     */
    void benchmarkMergeSort();

    /**
     * @brief Performance Test 3: Trie Operations
     * Tests insert and autocomplete on N = 10³, 10⁴, 10⁵
     * Expected: O(m) where m is length of string/prefix
     */
    void benchmarkTrie();

    /**
     * @brief Performance Test 4: Search Operations
     * Tests linear search vs hash-based search
     * Expected: O(n) for linear, O(1) for hash
     */
    void benchmarkSearch();

    // Reporting
    void printResults();
    void generateReport(const string &filename);

    // Run all tests
    void runAllTests();
};

#endif
