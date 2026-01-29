#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

class BubbleSort {
public:
    // Bubble Sort cơ bản
    static void basicBubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    
    // Bubble Sort tối ưu với early termination
    static void optimizedBubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            // Nếu không có hoán đổi nào, mảng đã sắp xếp
            if (!swapped) {
                break;
            }
        }
    }
    
    // Bubble Sort với đếm số lần so sánh và hoán đổi
    static pair<int, int> bubbleSortWithStats(vector<int>& arr) {
        int n = arr.size();
        int comparisons = 0;
        int swaps = 0;
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swaps++;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        
        return {comparisons, swaps};
    }
    
    // Debug function để hiển thị từng bước
    static void debugBubbleSort(vector<int>& arr) {
        cout << "=== DEBUG BUBBLE SORT ===" << endl;
        cout << "Initial array: ";
        printArray(arr);
        
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            cout << "\nPass " << (i + 1) << ":" << endl;
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                cout << "Comparing " << arr[j] << " and " << arr[j + 1];
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                    cout << " -> Swap!" << endl;
                } else {
                    cout << " -> No swap" << endl;
                }
                cout << "Array: ";
                printArray(arr);
            }
            
            if (!swapped) {
                cout << "No swaps in this pass - array is sorted!" << endl;
                break;
            }
        }
        cout << "=========================" << endl;
    }
    
    // Cocktail Shaker Sort (bidirectional bubble sort)
    static void cocktailShakerSort(vector<int>& arr) {
        int n = arr.size();
        bool swapped = true;
        int start = 0;
        int end = n - 1;
        
        while (swapped) {
            swapped = false;
            
            // Forward pass
            for (int i = start; i < end; i++) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            
            if (!swapped) break;
            
            end--;
            swapped = false;
            
            // Backward pass
            for (int i = end - 1; i >= start; i--) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            
            start++;
        }
    }
    
private:
    static void printArray(const vector<int>& arr) {
        for (int x : arr) {
            cout << x << " ";
        }
        cout << endl;
    }
};

// Hàm so sánh hiệu suất các biến thể bubble sort
void performanceComparison(vector<int> testData) {
    cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
    cout << "Array size: " << testData.size() << endl;
    
    // Test Basic Bubble Sort
    vector<int> arr1 = testData;
    auto start = chrono::high_resolution_clock::now();
    BubbleSort::basicBubbleSort(arr1);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test Optimized Bubble Sort
    vector<int> arr2 = testData;
    start = chrono::high_resolution_clock::now();
    BubbleSort::optimizedBubbleSort(arr2);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test Cocktail Shaker Sort
    vector<int> arr3 = testData;
    start = chrono::high_resolution_clock::now();
    BubbleSort::cocktailShakerSort(arr3);
    end = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test with statistics
    vector<int> arr4 = testData;
    auto stats = BubbleSort::bubbleSortWithStats(arr4);
    
    cout << "Basic Bubble Sort: " << duration1.count() << " μs" << endl;
    cout << "Optimized Bubble Sort: " << duration2.count() << " μs" << endl;
    cout << "Cocktail Shaker Sort: " << duration3.count() << " μs" << endl;
    cout << "Comparisons: " << stats.first << ", Swaps: " << stats.second << endl;
    cout << "===============================" << endl;
}

// Hàm test với các loại dữ liệu khác nhau
void testDifferentDataTypes() {
    cout << "\n=== TESTING DIFFERENT DATA TYPES ===" << endl;
    
    // Test với mảng đã sắp xếp
    cout << "1. Already sorted array:" << endl;
    vector<int> sorted = {1, 2, 3, 4, 5};
    auto stats1 = BubbleSort::bubbleSortWithStats(sorted);
    cout << "Comparisons: " << stats1.first << ", Swaps: " << stats1.second << endl;
    
    // Test với mảng sắp xếp ngược
    cout << "\n2. Reverse sorted array:" << endl;
    vector<int> reverse = {5, 4, 3, 2, 1};
    auto stats2 = BubbleSort::bubbleSortWithStats(reverse);
    cout << "Comparisons: " << stats2.first << ", Swaps: " << stats2.second << endl;
    
    // Test với mảng ngẫu nhiên
    cout << "\n3. Random array:" << endl;
    vector<int> random = {3, 1, 4, 1, 5, 9, 2, 6};
    auto stats3 = BubbleSort::bubbleSortWithStats(random);
    cout << "Comparisons: " << stats3.first << ", Swaps: " << stats3.second << endl;
    
    // Test với mảng có nhiều phần tử trùng
    cout << "\n4. Array with duplicates:" << endl;
    vector<int> duplicates = {3, 1, 3, 1, 3, 1, 3};
    auto stats4 = BubbleSort::bubbleSortWithStats(duplicates);
    cout << "Comparisons: " << stats4.first << ", Swaps: " << stats4.second << endl;
    
    cout << "====================================" << endl;
}

// Hàm so sánh với std::sort
void compareWithStdSort(vector<int> testData) {
    cout << "\n=== COMPARISON WITH STD::SORT ===" << endl;
    
    // Test Bubble Sort
    vector<int> arr1 = testData;
    auto start = chrono::high_resolution_clock::now();
    BubbleSort::optimizedBubbleSort(arr1);
    auto end = chrono::high_resolution_clock::now();
    auto bubbleTime = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test std::sort
    vector<int> arr2 = testData;
    start = chrono::high_resolution_clock::now();
    sort(arr2.begin(), arr2.end());
    end = chrono::high_resolution_clock::now();
    auto stdTime = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Bubble Sort: " << bubbleTime.count() << " μs" << endl;
    cout << "std::sort: " << stdTime.count() << " μs" << endl;
    cout << "Speed ratio: " << (double)bubbleTime.count() / stdTime.count() << "x" << endl;
    cout << "=================================" << endl;
}

// Hàm tạo dữ liệu test
vector<int> generateTestData(int size, string type) {
    vector<int> data;
    
    if (type == "random") {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 1000);
        
        for (int i = 0; i < size; i++) {
            data.push_back(dis(gen));
        }
    } else if (type == "sorted") {
        for (int i = 1; i <= size; i++) {
            data.push_back(i);
        }
    } else if (type == "reverse") {
        for (int i = size; i >= 1; i--) {
            data.push_back(i);
        }
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
    
    BubbleSort::optimizedBubbleSort(arr);
    
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // vector<int> debugArr = {64, 34, 25, 12, 22, 11, 90};
    // BubbleSort::debugBubbleSort(debugArr);
    
    // Test performance với dữ liệu khác nhau:
    // testDifferentDataTypes();
    
    // So sánh hiệu suất:
    // vector<int> testData = generateTestData(1000, "random");
    // performanceComparison(testData);
    // compareWithStdSort(testData);
    
    return 0;
}