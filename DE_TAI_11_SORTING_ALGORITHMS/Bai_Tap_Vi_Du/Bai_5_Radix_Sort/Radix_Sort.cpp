#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
using namespace std;

class RadixSort {
private:
    vector<int> arr;
    bool debugMode;
    int base;
    
public:
    RadixSort(bool debug = false, int radix = 10) : debugMode(debug), base(radix) {}
    
    void setArray(const vector<int>& input) {
        arr = input;
    }
    
    // Get the maximum number to know number of digits
    int getMax() const {
        return *max_element(arr.begin(), arr.end());
    }
    
    // Counting sort for a specific digit position
    void countingSort(int exp) {
        vector<int> output(arr.size());
        vector<int> count(base, 0);
        
        if (debugMode) {
            cout << "Sorting by digit at position " << exp << endl;
            cout << "Current array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
        }
        
        // Store count of occurrences in count[]
        for (int i = 0; i < arr.size(); i++) {
            count[(arr[i] / exp) % base]++;
        }
        
        if (debugMode) {
            cout << "Digit frequency: ";
            for (int i = 0; i < base; i++) {
                if (count[i] > 0) {
                    cout << i << ":" << count[i] << " ";
                }
            }
            cout << endl;
        }
        
        // Change count[i] so that count[i] now contains actual
        // position of this digit in output[]
        for (int i = 1; i < base; i++) {
            count[i] += count[i - 1];
        }
        
        // Build the output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % base;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to current digit
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = output[i];
        }
        
        if (debugMode) {
            cout << "After sorting: ";
            for (int x : arr) cout << x << " ";
            cout << endl << "---" << endl;
        }
    }
    
    // Main radix sort function
    void sort() {
        if (arr.empty()) return;
        
        // Find the maximum number to know number of digits
        int maxNum = getMax();
        
        if (debugMode) {
            cout << "=== RADIX SORT PROCESS ===" << endl;
            cout << "Maximum number: " << maxNum << endl;
            cout << "Base: " << base << endl;
            cout << "Initial array: ";
            for (int x : arr) cout << x << " ";
            cout << endl << endl;
        }
        
        // Do counting sort for every digit. Note that instead
        // of passing digit number, exp is passed. exp is 10^i
        // where i is current digit number
        for (int exp = 1; maxNum / exp > 0; exp *= base) {
            countingSort(exp);
        }
        
        if (debugMode) {
            cout << "Final sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << endl;
            cout << "=========================" << endl;
        }
    }
    
    // Get sorted array
    vector<int> getSortedArray() const {
        return arr;
    }
    
    // Sort with different bases for comparison
    void sortWithDifferentBases(const vector<int>& input, const vector<int>& bases) {
        cout << "\n=== RADIX SORT WITH DIFFERENT BASES ===" << endl;
        
        for (int testBase : bases) {
            RadixSort sorter(false, testBase);
            sorter.setArray(input);
            
            auto start = chrono::high_resolution_clock::now();
            sorter.sort();
            auto end = chrono::high_resolution_clock::now();
            
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            
            cout << "Base " << testBase << ": " << duration.count() << " μs" << endl;
        }
        cout << "=======================================" << endl;
    }
    
    // Demonstrate step-by-step process
    void demonstrateStepByStep(const vector<int>& input) {
        cout << "\n=== STEP-BY-STEP DEMONSTRATION ===" << endl;
        
        setArray(input);
        int maxNum = getMax();
        
        cout << "Input: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
        
        cout << "Maximum number: " << maxNum << endl;
        cout << "Number of digits: " << to_string(maxNum).length() << endl;
        cout << endl;
        
        int step = 1;
        for (int exp = 1; maxNum / exp > 0; exp *= base) {
            cout << "Step " << step++ << ": Sort by " 
                 << (exp == 1 ? "units" : exp == 10 ? "tens" : exp == 100 ? "hundreds" : "digit") 
                 << " place" << endl;
            
            // Show which digit we're sorting by for each number
            cout << "Digits being sorted: ";
            for (int x : arr) {
                cout << ((x / exp) % base) << " ";
            }
            cout << endl;
            
            countingSort(exp);
            
            cout << "Result: ";
            for (int x : arr) cout << x << " ";
            cout << endl << endl;
        }
        
        cout << "===================================" << endl;
    }
    
    // Performance analysis
    void analyzePerformance(const vector<int>& testSizes) {
        cout << "\n=== RADIX SORT PERFORMANCE ANALYSIS ===" << endl;
        cout << "Size\t\tTime (ms)\tComplexity" << endl;
        cout << "----\t\t---------\t----------" << endl;
        
        for (int size : testSizes) {
            // Generate random array with numbers up to 10^6
            vector<int> testArr(size);
            for (int i = 0; i < size; i++) {
                testArr[i] = rand() % 1000000;
            }
            
            RadixSort sorter;
            sorter.setArray(testArr);
            
            auto start = chrono::high_resolution_clock::now();
            sorter.sort();
            auto end = chrono::high_resolution_clock::now();
            
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            
            cout << size << "\t\t" << duration.count() << "\t\t" 
                 << "O(d*(n+k))" << endl;
        }
        cout << "d = number of digits, k = range of digits (0-9)" << endl;
        cout << "=========================================" << endl;
    }
    
    // Compare with other sorting algorithms
    void compareWithOtherSorts(const vector<int>& testData) {
        cout << "\n=== SORTING ALGORITHMS COMPARISON ===" << endl;
        
        // Test Radix Sort
        vector<int> radixData = testData;
        RadixSort radixSorter;
        radixSorter.setArray(radixData);
        
        auto start = chrono::high_resolution_clock::now();
        radixSorter.sort();
        auto end = chrono::high_resolution_clock::now();
        auto radixTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Test STL sort (comparison-based)
        vector<int> stlData = testData;
        start = chrono::high_resolution_clock::now();
        sort(stlData.begin(), stlData.end());
        end = chrono::high_resolution_clock::now();
        auto stlTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Test counting sort (for comparison with another non-comparison sort)
        vector<int> countingData = testData;
        int maxVal = *max_element(countingData.begin(), countingData.end());
        
        start = chrono::high_resolution_clock::now();
        // Simple counting sort implementation
        vector<int> count(maxVal + 1, 0);
        for (int x : countingData) count[x]++;
        
        int idx = 0;
        for (int i = 0; i <= maxVal; i++) {
            while (count[i]-- > 0) {
                countingData[idx++] = i;
            }
        }
        end = chrono::high_resolution_clock::now();
        auto countingTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "Array size: " << testData.size() << endl;
        cout << "Max value: " << maxVal << endl;
        cout << "Radix Sort:    " << radixTime.count() << " μs" << endl;
        cout << "STL sort():    " << stlTime.count() << " μs" << endl;
        cout << "Counting Sort: " << countingTime.count() << " μs" << endl;
        
        // Verify all results are the same
        bool allSame = (radixSorter.getSortedArray() == stlData) && (stlData == countingData);
        cout << "Results match: " << (allSame ? "✅ Yes" : "❌ No") << endl;
        
        cout << "\nAnalysis:" << endl;
        cout << "- Radix Sort: O(d*(n+k)) where d=digits, k=base" << endl;
        cout << "- STL Sort: O(n log n) comparison-based" << endl;
        cout << "- Counting Sort: O(n+k) where k=range" << endl;
        cout << "=====================================" << endl;
    }
    
    // Educational demonstration of when to use radix sort
    void demonstrateUseCases() {
        cout << "\n=== RADIX SORT USE CASES ===" << endl;
        
        cout << "✅ Good for:" << endl;
        cout << "- Integers with limited digits" << endl;
        cout << "- Strings of fixed length" << endl;
        cout << "- When range is not significantly larger than n" << endl;
        cout << "- Stable sorting required" << endl;
        
        cout << "\n❌ Not ideal for:" << endl;
        cout << "- Floating point numbers" << endl;
        cout << "- Very large integers (many digits)" << endl;
        cout << "- Small arrays (overhead not worth it)" << endl;
        cout << "- When memory is very limited" << endl;
        
        cout << "\n📊 Performance characteristics:" << endl;
        cout << "- Time: O(d*(n+k)) where d=digits, k=base" << endl;
        cout << "- Space: O(n+k)" << endl;
        cout << "- Stable: Yes" << endl;
        cout << "- In-place: No" << endl;
        cout << "- Comparison-based: No" << endl;
        
        cout << "============================" << endl;
    }
    
    // Test with different data patterns
    void testWithDifferentPatterns() {
        cout << "\n=== TESTING WITH DIFFERENT PATTERNS ===" << endl;
        
        // Test 1: Already sorted
        vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        RadixSort sorter1;
        sorter1.setArray(sorted);
        auto start = chrono::high_resolution_clock::now();
        sorter1.sort();
        auto end = chrono::high_resolution_clock::now();
        auto sortedTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Test 2: Reverse sorted
        vector<int> reverse = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        RadixSort sorter2;
        sorter2.setArray(reverse);
        start = chrono::high_resolution_clock::now();
        sorter2.sort();
        end = chrono::high_resolution_clock::now();
        auto reverseTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Test 3: All same elements
        vector<int> same(10, 5);
        RadixSort sorter3;
        sorter3.setArray(same);
        start = chrono::high_resolution_clock::now();
        sorter3.sort();
        end = chrono::high_resolution_clock::now();
        auto sameTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "Already sorted: " << sortedTime.count() << " μs" << endl;
        cout << "Reverse sorted: " << reverseTime.count() << " μs" << endl;
        cout << "All same:       " << sameTime.count() << " μs" << endl;
        
        cout << "\nObservation: Radix sort performance is relatively" << endl;
        cout << "consistent across different input patterns!" << endl;
        cout << "========================================" << endl;
    }
};

// Utility functions
vector<int> generateRandomArray(int size, int maxValue = 1000) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % maxValue;
    }
    return arr;
}

int main() {
    // Read input
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Create radix sort instance
    RadixSort radixSort;
    radixSort.setArray(arr);
    
    // Sort the array
    radixSort.sort();
    
    // Output sorted array
    vector<int> sorted = radixSort.getSortedArray();
    for (int i = 0; i < n; i++) {
        cout << sorted[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment for demonstrations and analysis:
    
    // Step-by-step demonstration
    // RadixSort demo(true);
    // demo.demonstrateStepByStep({170, 45, 75, 90, 2, 802, 24, 66});
    
    // Performance analysis
    // RadixSort perfAnalyzer;
    // perfAnalyzer.analyzePerformance({100, 1000, 5000, 10000});
    
    // Compare with other algorithms
    // auto testData = generateRandomArray(10000, 100000);
    // RadixSort comparator;
    // comparator.compareWithOtherSorts(testData);
    
    // Test different bases
    // RadixSort baseTest;
    // auto testData2 = generateRandomArray(1000, 10000);
    // baseTest.sortWithDifferentBases(testData2, {2, 8, 10, 16});
    
    // Use cases demonstration
    // RadixSort useCases;
    // useCases.demonstrateUseCases();
    
    // Pattern testing
    // RadixSort patternTest;
    // patternTest.testWithDifferentPatterns();
    
    return 0;
}