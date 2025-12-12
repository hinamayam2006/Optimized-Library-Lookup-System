#include "test/PerformanceTest.h"
#include <iostream>

using namespace std;

/**
 * @brief Test Runner for Library Management System
 *
 * This program runs comprehensive tests including:
 * 1. Correctness validation (3+ test cases)
 * 2. Performance benchmarking (multiple input sizes)
 * 3. Big-O complexity verification
 * 4. Averaged results over multiple runs
 */
int main()
{
    cout << R"(
    ╔════════════════════════════════════════════════════════════╗
    ║   Library Management System - Test Suite                  ║
    ║   Data Structures & Algorithms Performance Analysis       ║
    ╚════════════════════════════════════════════════════════════╝
    )" << endl;

    try
    {
        PerformanceTest tester;

        cout << "\nStarting comprehensive test suite..." << endl;
        cout << "This will test:\n";
        cout << "  ✓ Hash Table (Insert, Search, Update, Delete)\n";
        cout << "  ✓ Merge Sort (Sorting correctness)\n";
        cout << "  ✓ Trie (Autocomplete functionality)\n";
        cout << "  ✓ Performance on N = 1,000, 10,000, 100,000\n";
        cout << "  ✓ Average over 3+ runs per test\n\n";

        cout << "Press Enter to continue...";
        cin.get();

        // Run all tests
        tester.runAllTests();

        cout << "\n\n"
             << R"(
    ╔════════════════════════════════════════════════════════════╗
    ║              Test Suite Execution Complete                 ║
    ╚════════════════════════════════════════════════════════════╝
        )" << endl;

        cout << "\nNext steps:\n";
        cout << "  1. Review the performance_report.txt for detailed results\n";
        cout << "  2. Compare actual timing with theoretical Big-O predictions\n";
        cout << "  3. Verify all correctness tests passed\n\n";
    }
    catch (const exception &e)
    {
        cerr << "\n✗ Error during test execution: " << e.what() << endl;
        return 1;
    }

    return 0;
}
