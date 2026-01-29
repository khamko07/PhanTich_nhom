#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

class HeapSort {
private:
    vector<int> arr;
    bool debugMode;
    
public:
    HeapSort(bool debug = false) : debugMode(debug) {}
    
    void setArray(const vector<int>& input) {
        arr = input;
    }
    
    // Heapify a subtree rooted with node i
    void heapify(int n, int i) {
        int largest = i;    // Initialize largest as root
        int left = 2 * i + 1;   // left child
        int right = 2 * i + 2;  // right child
        
        // If left child is larger than root
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        
        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);
            
            if (debugMode) {
                cout << "Heapify: Swapped " << arr[largest] << " and " << arr[i] << endl;
                printArray("After heapify step");
            }
            
            // Recursively heapify the affected sub-tree
            heapify(n, largest);
        }
    }
    
    // Build max heap from array
    void buildMaxHeap() {
        if (debugMode) {
            cout << "=== BUILDING MAX HEAP ===" << endl;
            printArray("Initial array");
        }
        
        // Start from the last non-leaf node and heapify each node
        for (int i = arr.size() / 2 - 1; i >= 0; i--) {
            if (debugMode) {
                cout << "Heapifying subtree rooted at index " << i << endl;
            }
            heapify(arr.size(), i);
        }
        
        if (debugMode) {
            printArray("Max heap built");
            cout << "=========================" << endl;
        }
    }
    
    // Main heap sort function
    void sort() {
        int n = arr.size();
        
        // Build max heap
        buildMaxHeap();
        
        if (debugMode) {
            cout << "\n=== HEAP SORT PROCESS ===" << endl;
        }
        
        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--) {
            // Move current root to end
            swap(arr[0], arr[i]);
            
            if (debugMode) {
                cout << "Step " << (n - i) << ": Moved " << arr[i] 
                     << " to position " << i << endl;
                printArray("Array state");
            }
            
            // Call heapify on the reduced heap
            heapify(i, 0);
            
            if (debugMode) {
                printArray("After heapify");
                cout << "---" << endl;
            }
        }
        
        if (debugMode) {
            cout << "=========================" << endl;
        }
    }
    
    // Get sorted array
    vector<int> getSortedArray() const {
        return arr;
    }
    
    // Print array with optional title
    void printArray(const string& title = "") const {
        if (!title.empty()) {
            cout << title << ": ";
        }
        for (int x : arr) {
            cout << x << " ";
        }
        cout << endl;
    }
    
    // Visualize heap structure
    void visualizeHeap() const {
        cout << "\n=== HEAP VISUALIZATION ===" << endl;
        int n = arr.size();
        int level = 0;
        int levelSize = 1;
        int index = 0;
        
        while (index < n) {
            cout << "Level " << level << ": ";
            
            for (int i = 0; i < levelSize && index < n; i++, index++) {
                cout << arr[index] << " ";
            }
            cout << endl;
            
            level++;
            levelSize *= 2;
        }
        cout << "==========================" << endl;
    }
    
    // Check if array is a valid max heap
    bool isMaxHeap() const {
        int n = arr.size();
        
        for (int i = 0; i <= (n - 2) / 2; i++) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            
            if (left < n && arr[i] < arr[left]) {
                return false;
            }
            
            if (right < n && arr[i] < arr[right]) {
                return false;
            }
        }
        
        return true;
    }
    
    // Performance analysis
    void analyzePerformance(const vector<int>& testSizes) {
        cout << "\n=== HEAP SORT PERFORMANCE ANALYSIS ===" << endl;
        cout << "Size\t\tTime (ms)\tComparisons" << endl;
        cout << "----\t\t---------\t-----------" << endl;
        
        for (int size : testSizes) {
            // Generate random array
            vector<int> testArr(size);
            for (int i = 0; i < size; i++) {
                testArr[i] = rand() % 10000;
            }
            
            HeapSort sorter;
            sorter.setArray(testArr);
            
            auto start = chrono::high_resolution_clock::now();
            sorter.sort();
            auto end = chrono::high_resolution_clock::now();
            
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            
            cout << size << "\t\t" << duration.count() << "\t\t" 
                 << "O(n log n)" << endl;
        }
        cout << "=======================================" << endl;
    }
    
    // Compare with other sorting algorithms
    void compareWithOtherSorts(const vector<int>& testData) {
        cout << "\n=== SORTING ALGORITHMS COMPARISON ===" << endl;
        
        // Test Heap Sort
        vector<int> heapData = testData;
        HeapSort heapSorter;
        heapSorter.setArray(heapData);
        
        auto start = chrono::high_resolution_clock::now();
        heapSorter.sort();
        auto end = chrono::high_resolution_clock::now();
        auto heapTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Test STL sort (typically Introsort)
        vector<int> stlData = testData;
        start = chrono::high_resolution_clock::now();
        sort(stlData.begin(), stlData.end());
        end = chrono::high_resolution_clock::now();
        auto stlTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Test make_heap + sort_heap
        vector<int> stlHeapData = testData;
        start = chrono::high_resolution_clock::now();
        make_heap(stlHeapData.begin(), stlHeapData.end());
        sort_heap(stlHeapData.begin(), stlHeapData.end());
        end = chrono::high_resolution_clock::now();
        auto stlHeapTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "Array size: " << testData.size() << endl;
        cout << "Custom Heap Sort: " << heapTime.count() << " μs" << endl;
        cout << "STL sort():       " << stlTime.count() << " μs" << endl;
        cout << "STL heap sort:    " << stlHeapTime.count() << " μs" << endl;
        
        // Verify all results are the same
        bool allSame = (heapSorter.getSortedArray() == stlData) && (stlData == stlHeapData);
        cout << "Results match: " << (allSame ? "✅ Yes" : "❌ No") << endl;
        cout << "=====================================" << endl;
    }
    
    // Educational demonstration
    void demonstrateHeapProperties() {
        cout << "\n=== HEAP PROPERTIES DEMONSTRATION ===" << endl;
        
        // Show heap property
        buildMaxHeap();
        cout << "Max Heap Property: Parent >= Children" << endl;
        visualizeHeap();
        
        cout << "Verification:" << endl;
        int n = arr.size();
        for (int i = 0; i <= (n - 2) / 2; i++) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            
            cout << "Node " << i << " (value " << arr[i] << "): ";
            
            if (left < n) {
                cout << "Left child " << left << " (value " << arr[left] << ") ";
                cout << (arr[i] >= arr[left] ? "✅" : "❌") << " ";
            }
            
            if (right < n) {
                cout << "Right child " << right << " (value " << arr[right] << ") ";
                cout << (arr[i] >= arr[right] ? "✅" : "❌");
            }
            
            cout << endl;
        }
        
        cout << "Is valid max heap: " << (isMaxHeap() ? "✅ Yes" : "❌ No") << endl;
        cout << "=====================================" << endl;
    }
};

// Utility functions for testing
vector<int> generateRandomArray(int size, int maxValue = 100) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % maxValue + 1;
    }
    return arr;
}

vector<int> generateReverseSortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    return arr;
}

vector<int> generateNearlySortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    
    // Swap a few random elements
    for (int i = 0; i < size / 10; i++) {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        swap(arr[idx1], arr[idx2]);
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
    
    // Create heap sort instance
    HeapSort heapSort;
    heapSort.setArray(arr);
    
    // Sort the array
    heapSort.sort();
    
    // Output sorted array
    vector<int> sorted = heapSort.getSortedArray();
    for (int i = 0; i < n; i++) {
        cout << sorted[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment for debugging and analysis:
    
    // Debug mode demonstration
    // HeapSort debugSorter(true);
    // debugSorter.setArray({64, 34, 25, 12, 22, 11, 90});
    // debugSorter.sort();
    
    // Heap properties demonstration
    // HeapSort propDemo;
    // propDemo.setArray({64, 34, 25, 12, 22, 11, 90});
    // propDemo.demonstrateHeapProperties();
    
    // Performance analysis
    // HeapSort perfAnalyzer;
    // perfAnalyzer.analyzePerformance({100, 1000, 5000, 10000});
    
    // Comparison with other algorithms
    // auto testData = generateRandomArray(10000);
    // HeapSort comparator;
    // comparator.compareWithOtherSorts(testData);
    
    return 0;
}