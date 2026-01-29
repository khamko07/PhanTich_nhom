#include <iostream>
#include <vector>
using namespace std;

// Coding Kata: Bubble Sort với đếm số lần hoán đổi
// Thực hành làm nhiều lần để nhuần nhuyễn

class BubbleSortKata {
private:
    int swapCount;
    
public:
    BubbleSortKata() : swapCount(0) {}
    
    // Hàm hoán đổi với đếm
    void swapElements(vector<int>& arr, int i, int j) {
        if (i != j) {
            swap(arr[i], arr[j]);
            swapCount++;
        }
    }
    
    // Thuật toán Bubble Sort
    vector<int> sort(vector<int> arr) {
        swapCount = 0;
        int n = arr.size();
        
        // Bubble Sort với tối ưu hóa
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swapElements(arr, j, j + 1);
                    swapped = true;
                }
            }
            
            // Nếu không có hoán đổi nào, mảng đã sắp xếp
            if (!swapped) {
                break;
            }
        }
        
        return arr;
    }
    
    int getSwapCount() const {
        return swapCount;
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    BubbleSortKata kata;
    vector<int> sortedArr = kata.sort(arr);
    
    // In mảng đã sắp xếp
    for (int i = 0; i < n; i++) {
        cout << sortedArr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // In số lần hoán đổi
    cout << kata.getSwapCount() << endl;
    
    return 0;
}