# Performance Testing & Validation Guide

This document explains the testing requirements and how to run the comprehensive test suite for the Library Management System.

## 📋 Requirements Explanation

### iv. Test Cases for Validation

**What it means:** Create at least 3 test cases that verify your algorithms work correctly.

**Implementation:**

- **Test Case 1:** Hash Table Correctness

  - Validates insert, search, update, and delete operations
  - Checks that data is stored and retrieved accurately
  - Tests edge cases (non-existent keys, empty operations)

- **Test Case 2:** Merge Sort Correctness

  - Validates that sorting produces correct order
  - Tests sorting by different criteria (title, year, author)
  - Verifies edge cases (single element, empty array)

- **Test Case 3:** Trie Autocomplete Correctness
  - Validates prefix matching returns correct results
  - Tests different prefixes and edge cases
  - Verifies empty prefix and non-existent prefix handling

### v. Algorithm Efficiency Measurement

**What it means:** Measure actual runtime performance and compare with theoretical Big-O complexity.

**Requirements:**

- Test on **at least 3 input sizes**: N = 10³ (1,000), 10⁴ (10,000), 10⁵ (100,000)
- Run each test **≥3 times** and report the average
- Compare results with expected Big-O notation

**Implementation:**

1. **Hash Table Performance** - Expected: O(1)

   - Measure insert time for N books
   - Measure search time for N lookups
   - Verify time per operation stays constant as N grows

2. **Merge Sort Performance** - Expected: O(n log n)

   - Measure sort time for N books
   - Verify time grows proportionally to n × log(n)
   - Compare with theoretical prediction

3. **Trie Performance** - Expected: O(m) where m = string length

   - Measure insert time for N words
   - Measure autocomplete time
   - Verify time depends on string length, not dataset size

4. **Search Comparison** - O(1) vs O(n)
   - Compare hash-based search vs linear search
   - Show speedup increases with dataset size

## 🚀 How to Build and Run Tests

### Step 1: Build the Test Executable

```bash
cd build
cmake ..
cmake --build .
```

This creates two executables:

- `LibrarySystem.exe` - Main GUI application
- `LibrarySystemTest.exe` - Test suite (console)

### Step 2: Run the Tests

```bash
# From build directory
./LibrarySystemTest.exe

# Or with full path
D:\HP\Projects\DSAE\Optimized-Library-Lookup-System\build\LibrarySystemTest.exe
```

### Step 3: Review Results

The test suite will:

1. Display results in the console with colored output
2. Generate `performance_report.txt` with detailed metrics
3. Show pass/fail status for each test

## 📊 Understanding the Output

### Correctness Tests Output

```
=== TEST CASE 1: Hash Table Correctness ===
[1.1] Testing Insert and Search...
✓ Insert and Search: PASSED
  - Successfully inserted 3 books
  - All books retrieved correctly

[1.2] Testing Search for non-existent key...
✓ Non-existent key: PASSED
  - Correctly returned nullptr for missing key
```

### Performance Test Output

```
=== PERFORMANCE BENCHMARK 1: Hash Table Operations ===
Expected Complexity: O(1) average case for insert/search
Testing on input sizes: 10³, 10⁴, 10⁵

--- Testing with N = 1000 books ---
  Run 1/3...
  Run 2/3...
  Run 3/3...

  Results for N = 1000:
    Insert time: 2.345 ms
    Search time: 1.234 ms
    Avg time per insert: 0.002 ms
    Avg time per search: 0.001 ms
```

## 📈 Interpreting Big-O Results

### O(1) - Constant Time (Hash Table)

- Time per operation should stay roughly the same
- N = 1,000: ~0.002 ms per operation
- N = 100,000: ~0.002 ms per operation
- ✓ Confirms O(1) behavior

### O(n log n) - Merge Sort

- Time should grow proportionally to n × log(n)
- N = 1,000: ~5 ms (1,000 × log₂(1,000) ≈ 10,000)
- N = 10,000: ~60 ms (10,000 × log₂(10,000) ≈ 130,000)
- N = 100,000: ~800 ms (100,000 × log₂(100,000) ≈ 1,660,000)
- Ratio of times should match ratio of n log n values

### O(m) - Trie Operations

- Time depends on string length (m), not dataset size
- Insert 1,000 words vs 100,000 words
- Time per operation stays similar (depends on avg word length)
- ✓ Confirms O(m) behavior

## 📁 Test Files Structure

```
src/
├── test/
│   ├── PerformanceTest.h         # Test class header
│   └── PerformanceTest.cpp       # Test implementation
└── test_main.cpp                 # Test runner entry point

build/
└── performance_report.txt        # Generated after running tests
```

## 🧪 Test Coverage

### Data Structures Tested

- ✅ Hash Table (insert, search, update, delete)
- ✅ Merge Sort (sorting correctness and performance)
- ✅ Trie (autocomplete and prefix matching)
- ✅ Linked List (indirectly through hash table chaining)

### Algorithms Validated

- ✅ Hash function distribution
- ✅ Merge sort correctness
- ✅ Binary search (in sorted arrays)
- ✅ Trie prefix matching

### Input Sizes Tested

- ✅ N = 1,000 (10³)
- ✅ N = 10,000 (10⁴)
- ✅ N = 100,000 (10⁵)

### Averaging

- ✅ Each test runs 3 times
- ✅ Results are averaged for accuracy

## 📝 Sample Test Report

```
PERFORMANCE TEST SUMMARY
==========================================================

Test Name                          Input Size      Avg Time (ms)   Complexity
---------------------------------------------------------------------------------
Hash Table (N=1000)                1000            3.456           O(1) per operation
Hash Table (N=10000)               10000           34.123          O(1) per operation
Hash Table (N=100000)              100000          342.567         O(1) per operation
Merge Sort (N=1000)                1000            5.234           O(n log n)
Merge Sort (N=10000)               10000           67.890          O(n log n)
Merge Sort (N=100000)              100000          856.123         O(n log n)
Trie (N=1000)                      1000            2.345           O(m) per operation
Trie (N=10000)                     10000           23.456          O(m) per operation
Trie (N=100000)                    100000          234.567         O(m) per operation
Search Comparison (N=1000)         1000            0.123           O(1) vs O(n)
Search Comparison (N=10000)        10000           0.234           O(1) vs O(n)
Search Comparison (N=100000)       100000          0.456           O(1) vs O(n)

==========================================================
```

## ✅ Validation Checklist

After running tests, verify:

- [ ] All 3 correctness tests pass
- [ ] Hash table shows O(1) behavior (constant time per operation)
- [ ] Merge sort shows O(n log n) growth pattern
- [ ] Trie shows O(m) behavior (independent of dataset size)
- [ ] Each test runs 3+ times and reports average
- [ ] Tests cover input sizes: 10³, 10⁴, 10⁵
- [ ] performance_report.txt is generated
- [ ] Results match theoretical complexity predictions

## 🔧 Troubleshooting

### If tests fail to compile:

```bash
# Clean and rebuild
cd build
rm -rf *
cmake ..
cmake --build .
```

### If tests crash:

- Check data/ directory exists
- Ensure sufficient memory for large datasets
- Review error messages in console

### If performance seems off:

- Close other applications
- Run multiple times for consistent results
- Check CPU usage during tests

## 📚 References

- **Big-O Notation:** Describes worst-case time complexity
- **Hash Tables:** O(1) average, O(n) worst case
- **Merge Sort:** O(n log n) in all cases
- **Trie:** O(m) where m is string length

## 🎯 Meeting Requirements

This implementation satisfies the requirements:

✅ **iv. At least three test cases:**

- Hash Table correctness
- Merge Sort correctness
- Trie autocomplete correctness

✅ **v. Big-O measurement:**

- Tests on N = 10³, 10⁴, 10⁵
- Average over ≥3 runs
- Compares with theoretical complexity
- Reports detailed timing metrics

## 🚀 Next Steps

1. **Run the tests:** `./build/LibrarySystemTest.exe`
2. **Review results:** Check console output and performance_report.txt
3. **Analyze complexity:** Compare timing ratios with Big-O predictions
4. **Document findings:** Use results in your project report
5. **Include in submission:** Add test code and results to documentation
