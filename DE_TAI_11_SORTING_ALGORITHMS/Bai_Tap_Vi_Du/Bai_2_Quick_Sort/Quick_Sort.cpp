#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <stack>
using namespace std;

class QuickSort {
public:
    // Quick Sort cơ bản với Lomuto partition
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    // Hoare partition scheme (hiệu quả hơn)
    static int hoarePartition(vector<int>& arr, int low, int high) {
        int pivot = arr[low];
        int i = low - 1;
        int j = high + 1;
        
        while (true) {
            do {
                i++;
            } while (arr[i] < pivot);
            
            do {
                j--;
            } while (arr[j] > pivot);
            
            if (i >= j) {
                return j;
            }
            
            swap(arr[i], arr[j]);
        }
    }
    
    // Quick Sort với Hoare partition
    static void quickSortHoare(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = hoarePartition(arr, low, high);
            
            quickSortHoare(arr, low, pi);
            quickSortHoare(arr, pi + 1, high);
        }
    }
    
    // Randomized Quick Sort
    static void randomizedQuickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = randomizedPartition(arr, low, high);
            
            randomizedQuickSort(arr, low, pi - 1);
            randomizedQuickSort(arr, pi + 1, high);
        }
    }
    
    // Iterative Quick Sort (tránh stack overflow)
    static void iterativeQuickSort(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return;
        
        stack<pair<int, int>> st;
        st.push({0, n - 1});
        
        while (!st.empty()) {
            auto [low, high] = st.top();
            st.pop();
            
            if (low < high) {
                int pi = partition(arr, low, high);
                
                st.push({low, pi - 1});
                st.push({pi + 1, high});
            }
        }
    }
    
    // 3-way Quick Sort (Dutch National Flag) - tốt cho nhiều duplicate
    static void threeWayQuickSort(vector<int>& arr, int low, int high) {
        if (low >= high) return;
        
        auto [lt, gt] = threeWayPartition(arr, low, high);
        
        threeWayQuickSort(arr, low, lt - 1);
        threeWayQuickSort(arr, gt + 1, high);
    }
    
    // Hybrid Quick Sort với Insertion Sort cho mảng nhỏ
    static void hybridQuickSort(vector<int>& arr, int low, int high) {
        const int THRESHOLD = 10;
        
        if (high - low + 1 <= THRESHOLD) {
            insertionSort(arr, low, high);
        } else if (low < high) {
            int pi = partition(arr, low, high);
            
            hybridQuickSort(arr, low, pi - 1);
            hybridQuickSort(arr, pi + 1, high);
        }
    }
    
    // Debug function để hiển thị quá trình partition
    static void debugQuickSort(vector<int>& arr, int low, int high, int depth = 0) {
        string indent(depth * 2, ' ');
        cout << indent << "QuickSort(" << low << ", " << high << "): ";
        printRange(arr, low, high);
        
        if (low < high) {
            int pi = debugPartition(arr, low, high, depth);
            cout << indent << "Pivot at index " << pi << ", value " << arr[pi] << endl;
            
            debugQuickSort(arr, low, pi - 1, depth + 1);
            debugQuickSort(arr, pi + 1, high, depth + 1);
        }
    }
    
    // Tìm k-th smallest element (QuickSelect)
    static int quickSelect(vector<int>& arr, int low, int high, int k) {
        if (low == high) {
            return arr[low];
        }
        
        int pi = randomizedPartition(arr, low, high);
        
        if (k == pi) {
            return arr[pi];
        } else if (k < pi) {
            return quickSelect(arr, low, pi - 1, k);
        } else {
            return quickSelect(arr, pi + 1, high, k);
        }
    }
    
private:
    // Lomuto partition scheme
    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    // Randomized partition
    static int randomizedPartition(vector<int>& arr, int low, int high) {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dis(low, high);
        
        int randomIndex = dis(gen);
        swap(arr[randomIndex], arr[high]);
        
        return partition(arr, low, high);
    }
    
    // 3-way partition (Dutch National Flag)
    static pair<int, int> threeWayPartition(vector<int>& arr, int low, int high) {
        int pivot = arr[low];
        int lt = low;      // arr[low..lt-1] < pivot
        int i = low + 1;   // arr[lt..i-1] == pivot
        int gt = high;     // arr[gt+1..high] > pivot
        
        while (i <= gt) {
            if (arr[i] < pivot) {
                swap(arr[lt++], arr[i++]);
            } else if (arr[i] > pivot) {
                swap(arr[i], arr[gt--]);
            } else {
                i++;
            }
        }
        
        return {lt, gt};
    }
    
    // Insertion sort cho mảng nhỏ
    static void insertionSort(vector<int>& arr, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    // Debug partition với visualization
    static int debugPartition(vector<int>& arr, int low, int high, int depth) {
        string indent(depth * 2, ' ');
        int pivot = arr[high];
        cout << indent << "Partitioning with pivot " << pivot << endl;
        
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                if (i != j) {
                    swap(arr[i], arr[j]);
                    cout << indent << "Swap " << arr[j] << " and " << arr[i] << ": ";
                    printRange(arr, low, high);
                }
            }
        }
        
        swap(arr[i + 1], arr[high]);
        cout << indent << "Place pivot: ";
        printRange(arr, low, high);
        
        return i + 1;
    }
    
    static void printRange(const vector<int>& arr, int low, int high) {
        cout << "[";
        for (int i = low; i <= high; i++) {
            cout << arr[i];
            if (i < high) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// Hàm so sánh hiệu suất các biến thể Quick Sort
void performanceComparison(vector<int> testData) {
    cout << "\n=== QUICK SORT PERFORMANCE COMPARISON ===" << endl;
    cout << "Array size: " << testData.size() << endl;
    
    // Test Basic Quick Sort
    vector<int> arr1 = testData;
    auto start = chrono::high_resolution_clock::now();
    QuickSort::quickSort(arr1, 0, arr1.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test Randomized Quick Sort
    vector<int> arr2 = testData;
    start = chrono::high_resolution_clock::now();
    QuickSort::randomizedQuickSort(arr2, 0, arr2.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test 3-way Quick Sort
    vector<int> arr3 = testData;
    start = chrono::high_resolution_clock::now();
    QuickSort::threeWayQuickSort(arr3, 0, arr3.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test Hybrid Quick Sort
    vector<int> arr4 = testData;
    start = chrono::high_resolution_clock::now();
    QuickSort::hybridQuickSort(arr4, 0, arr4.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto duration4 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test Iterative Quick Sort
    vector<int> arr5 = testData;
    start = chrono::high_resolution_clock::now();
    QuickSort::iterativeQuickSort(arr5);
    end = chrono::high_resolution_clock::now();
    auto duration5 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Basic Quick Sort: " << duration1.count() << " μs" << endl;
    cout << "Randomized Quick Sort: " << duration2.count() << " μs" << endl;
    cout << "3-way Quick Sort: " << duration3.count() << " μs" << endl;
    cout << "Hybrid Quick Sort: " << duration4.count() << " μs" << endl;
    cout << "Iterative Quick Sort: " << duration5.count() << " μs" << endl;
    cout << "=========================================" << endl;
}

// Test QuickSelect
void testQuickSelect() {
    cout << "\n=== QUICK SELECT TEST ===" << endl;
    
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    for (int k = 0; k < arr.size(); k++) {
        vector<int> temp = arr;
        int kthSmallest = QuickSort::quickSelect(temp, 0, temp.size() - 1, k);
        cout << (k + 1) << "-th smallest element: " << kthSmallest << endl;
    }
    
    cout << "=========================" << endl;
}

// Test với worst case (sorted array)
void testWorstCase() {
    cout << "\n=== WORST CASE TEST ===" << endl;
    
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Testing with sorted array (worst case for basic QuickSort)" << endl;
    
    // Basic QuickSort (có thể chậm)
    vector<int> arr1 = sorted;
    auto start = chrono::high_resolution_clock::now();
    QuickSort::quickSort(arr1, 0, arr1.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Randomized QuickSort (tránh worst case)
    vector<int> arr2 = sorted;
    start = chrono::high_resolution_clock::now();
    QuickSort::randomizedQuickSort(arr2, 0, arr2.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Basic QuickSort: " << duration1.count() << " μs" << endl;
    cout << "Randomized QuickSort: " << duration2.count() << " μs" << endl;
    cout << "Improvement: " << (double)duration1.count() / duration2.count() << "x" << endl;
    cout << "===========================" << endl;
}

// Hàm tạo dữ liệu test với nhiều duplicate
vector<int> generateDataWithDuplicates(int size) {
    vector<int> data;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5); // Chỉ 5 giá trị khác nhau
    
    for (int i = 0; i < size; i++) {
        data.push_back(dis(gen));
    }
    
    return data;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    QuickSort::quickSort(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // vector<int> debugArr = {10, 7, 8, 9, 1, 5};
    // cout << "Debug QuickSort process:" << endl;
    // QuickSort::debugQuickSort(debugArr, 0, debugArr.size() - 1);
    
    // Test QuickSelect:
    // testQuickSelect();
    
    // Test worst case:
    // testWorstCase();
    
    // Performance comparison:
    // vector<int> testData = generateDataWithDuplicates(1000);
    // performanceComparison(testData);
    
    return 0;
}