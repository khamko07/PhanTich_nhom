#include <iostream>
#include <vector>
using namespace std;

// Coding Kata: Bubble Sort với đếm số lần hoán đổi
pair<vector<int>, int> bubbleSort(vector<int> arr) {
    int n = arr.size();
    int swapCount = 0;
    
    // Thuật toán Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Hoán đổi
                swap(arr[j], arr[j + 1]);
                swapCount++;
            }
        }
    }
    
    return {arr, swapCount};
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Thực hiện sắp xếp và đếm hoán đổi
    auto result = bubbleSort(arr);
    vector<int> sortedArr = result.first;
    int swapCount = result.second;
    
    // In mảng đã sắp xếp
    for (int i = 0; i < n; i++) {
        cout << sortedArr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // In số lần hoán đổi
    cout << swapCount << endl;
    
    return 0;
}