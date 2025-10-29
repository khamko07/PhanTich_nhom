#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
using namespace std;

class BigOAnalysis {
private:
    bool debugMode;
    
public:
    BigOAnalysis(bool debug = false) : debugMode(debug) {}
    
    // O(1) - Constant Time
    int constantTime(const vector<int>& arr) {
        if (debugMode) {
            cout << "=== O(1) - Constant Time ===" << endl;
            cout << "Operations: 1 (regardless of input size)" << endl;
        }
        
        return arr.empty() ? 0 : arr[0];
    }
    
    // O(log n) - Logarithmic Time
    int logarithmicTime(const vector<int>& arr, int target) {
        if (debugMode) {
            cout << "=== O(log n) - Logarithmic Time ===" << endl;
            cout << "Binary Search - divides search space by half each step" << endl;
        }
        
        int left = 0, right = arr.size() - 1;
        int operations = 0;
        
        while (left <= right) {
            operations++;
            int mid = left + (right - left) / 2;
            
            if (debugMode) {
                cout << "Step " << operations << ": Checking position " << mid 
                     << " (value: " << arr[mid] << ")" << endl;
            }
            
            if (arr[mid] == target) {
                if (debugMode) {
                    cout << "Found target in " << operations << " operations" << endl;
                    cout << "Theoretical max: " << (int)ceil(log2(arr.size())) << " operations" << endl;
                }
                return mid;
            }
            
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (debugMode) {
            cout << "Target not found after " << operations << " operations" << endl;
        }
        
        return -1;
    }
    
    // O(n) - Linear Time
    int linearTime(const vector<int>& arr, int target) {
        if (debugMode) {
            cout << "=== O(n) - Linear Time ===" << endl;
            cout << "Linear Search - checks each element once" << endl;
        }
        
        int operations = 0;
        
        for (int i = 0; i < arr.size(); i++) {
            operations++;
            
            if (debugMode && operations <= 10) {
                cout << "Step " << operations << ": Checking arr[" << i 
                     << "] = " << arr[i] << endl;
            }
            
            if (arr[i] == target) {
                if (debugMode) {
                    cout << "Found target after " << operations << " operations" << endl;
                }
                return i;
            }
        }
        
        if (debugMode) {
            cout << "Target not found after " << operations << " operations" << endl;
        }
        
        return -1;
    }
    
    // O(n log n) - Linearithmic Time
    void linearithmicTime(vector<int>& arr) {
        if (debugMode) {
            cout << "=== O(n log n) - Linearithmic Time ===" << endl;
            cout << "Merge Sort - divides array and merges sorted halves" << endl;
        }
        
        mergeSort(arr, 0, arr.size() - 1, 0);
    }
    
    // O(n²) - Quadratic Time
    void quadraticTime(vector<int>& arr) {
        if (debugMode) {
            cout << "=== O(n²) - Quadratic Time ===" << endl;
            cout << "Bubble Sort - nested loops for comparisons" << endl;
        }
        
        int n = arr.size();
        int operations = 0;
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                operations++;
                
                if (debugMode && operations <= 20) {
                    cout << "Comparing arr[" << j << "] = " << arr[j] 
                         << " with arr[" << (j+1) << "] = " << arr[j+1] << endl;
                }
                
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    
                    if (debugMode && operations <= 20) {
                        cout << "Swapped!" << endl;
                    }
                }
            }
        }
        
        if (debugMode) {
            cout << "Total operations: " << operations << endl;
            cout << "Theoretical: n(n-1)/2 = " << n * (n - 1) / 2 << endl;
        }
    }
    
    // O(2^n) - Exponential Time
    int exponentialTime(int n) {
        if (debugMode && n <= 10) {
            cout << "=== O(2^n) - Exponential Time ===" << endl;
            cout << "Fibonacci (naive) - each call branches into two" << endl;
            cout << "Computing fibonacci(" << n << ")" << endl;
        }
        
        if (n <= 1) return n;
        
        return exponentialTime(n - 1) + exponentialTime(n - 2);
    }
    
    // Performance comparison
    void compareComplexities(const vector<int>& testSizes) {
        cout << "\n=== COMPLEXITY COMPARISON ===" << endl;
        cout << "Size\t\tO(1)\t\tO(log n)\tO(n)\t\tO(n log n)\tO(n²)" << endl;
        cout << "----\t\t----\t\t--------\t----\t\t----------\t-----" << endl;
        
        for (int n : testSizes) {
            // Generate test data
            vector<int> arr(n);
            for (int i = 0; i < n; i++) {
                arr[i] = i;
            }
            
            // O(1)
            auto start = chrono::high_resolution_clock::now();
            constantTime(arr);
            auto end = chrono::high_resolution_clock::now();
            auto o1_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
            
            // O(log n)
            start = chrono::high_resolution_clock::now();
            logarithmicTime(arr, n - 1);
            end = chrono::high_resolution_clock::now();
            auto olog_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
            
            // O(n)
            start = chrono::high_resolution_clock::now();
            linearTime(arr, n - 1);
            end = chrono::high_resolution_clock::now();
            auto on_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
            
            // O(n log n)
            vector<int> arr_copy = arr;
            reverse(arr_copy.begin(), arr_copy.end()); // Make it unsorted
            start = chrono::high_resolution_clock::now();
            sort(arr_copy.begin(), arr_copy.end());
            end = chrono::high_resolution_clock::now();
            auto onlogn_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
            
            // O(n²) - Only for small sizes
            long long on2_time = -1;
            if (n <= 10000) {
                arr_copy = arr;
                reverse(arr_copy.begin(), arr_copy.end());
                start = chrono::high_resolution_clock::now();
                quadraticTime(arr_copy);
                end = chrono::high_resolution_clock::now();
                on2_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
            }
            
            cout << n << "\t\t" << o1_time << "\t\t" << olog_time << "\t\t" 
                 << on_time << "\t\t" << onlogn_time << "\t\t";
            
            if (on2_time != -1) {
                cout << on2_time;
            } else {
                cout << "Too slow";
            }
            cout << endl;
        }
        
        cout << "\nNote: Times in microseconds. O(n²) skipped for large inputs." << endl;
        cout << "=============================" << endl;
    }
    
    // Theoretical vs Actual analysis
    void theoreticalAnalysis(int n) {
        cout << "\n=== THEORETICAL ANALYSIS FOR n = " << n << " ===" << endl;
        
        cout << "O(1):        1 operation" << endl;
        cout << "O(log n):    " << (int)ceil(log2(n)) << " operations" << endl;
        cout << "O(n):        " << n << " operations" << endl;
        cout << "O(n log n):  " << (long long)(n * log2(n)) << " operations" << endl;
        cout << "O(n²):       " << (long long)n * n << " operations" << endl;
        
        if (n <= 30) {
            cout << "O(2^n):      " << (1LL << n) << " operations" << endl;
        } else {
            cout << "O(2^n):      > 10^9 operations (too large to compute)" << endl;
        }
        
        if (n <= 10) {
            long long factorial = 1;
            for (int i = 1; i <= n; i++) {
                factorial *= i;
            }
            cout << "O(n!):       " << factorial << " operations" << endl;
        } else {
            cout << "O(n!):       > 10^9 operations (too large to compute)" << endl;
        }
        
        cout << "=============================================" << endl;
    }
    
    // Space complexity analysis
    void spaceComplexityDemo() {
        cout << "\n=== SPACE COMPLEXITY DEMONSTRATION ===" << endl;
        
        int n = 1000;
        
        // O(1) space
        cout << "O(1) Space - Finding maximum:" << endl;
        vector<int> arr(n, 1);
        int maxVal = arr[0];  // Only 1 extra variable
        for (int x : arr) {
            maxVal = max(maxVal, x);
        }
        cout << "Uses constant extra space regardless of input size" << endl;
        
        // O(n) space
        cout << "\nO(n) Space - Creating copy:" << endl;
        vector<int> copy = arr;  // n extra space
        cout << "Uses " << copy.size() * sizeof(int) << " bytes for copy" << endl;
        
        // O(log n) space - Recursive call stack
        cout << "\nO(log n) Space - Binary search recursion:" << endl;
        cout << "Maximum call stack depth: " << (int)ceil(log2(n)) << endl;
        
        // O(n²) space
        cout << "\nO(n²) Space - 2D matrix:" << endl;
        int small_n = 100;  // Use smaller n for demo
        vector<vector<int>> matrix(small_n, vector<int>(small_n, 0));
        cout << "Uses " << matrix.size() * matrix[0].size() * sizeof(int) 
             << " bytes for " << small_n << "x" << small_n << " matrix" << endl;
        
        cout << "=======================================" << endl;
    }
    
private:
    void mergeSort(vector<int>& arr, int left, int right, int depth) {
        if (left < right) {
            if (debugMode && depth < 3) {
                cout << "Dividing: [" << left << ", " << right << "]" << endl;
            }
            
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, depth + 1);
            mergeSort(arr, mid + 1, right, depth + 1);
            merge(arr, left, mid, right, depth);
        }
    }
    
    void merge(vector<int>& arr, int left, int mid, int right, int depth) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];
        
        for (int i = 0; i < temp.size(); i++) {
            arr[left + i] = temp[i];
        }
        
        if (debugMode && depth < 3) {
            cout << "Merged: ";
            for (int i = left; i <= right; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
};

// Utility functions for testing
vector<int> generateSortedArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    return arr;
}

vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
    return arr;
}

int main() {
    // Read input for basic functionality
    int n, target;
    cin >> n >> target;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    BigOAnalysis analyzer;
    
    // Perform different complexity operations
    cout << "Constant time result: " << analyzer.constantTime(arr) << endl;
    cout << "Binary search result: " << analyzer.logarithmicTime(arr, target) << endl;
    cout << "Linear search result: " << analyzer.linearTime(arr, target) << endl;
    
    // Uncomment for detailed analysis and demonstrations:
    
    // Debug mode demonstration
    // BigOAnalysis debugAnalyzer(true);
    // vector<int> testArr = {1, 3, 5, 7, 9, 11, 13, 15};
    // debugAnalyzer.logarithmicTime(testArr, 7);
    
    // Performance comparison
    // analyzer.compareComplexities({100, 1000, 10000, 100000});
    
    // Theoretical analysis
    // analyzer.theoreticalAnalysis(1000);
    
    // Space complexity demonstration
    // analyzer.spaceComplexityDemo();
    
    // Exponential time example (be careful with large n!)
    // if (n <= 35) {
    //     cout << "Fibonacci(" << n << ") = " << analyzer.exponentialTime(n) << endl;
    // }
    
    return 0;
}