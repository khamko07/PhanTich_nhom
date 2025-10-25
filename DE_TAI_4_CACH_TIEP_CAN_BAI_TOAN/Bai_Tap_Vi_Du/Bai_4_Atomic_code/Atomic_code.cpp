#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Atomic Code 1: Tìm phần tử lớn nhất
int findMax(const vector<int>& arr) {
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// Atomic Code 2: Đảo ngược mảng
vector<int> reverseArray(const vector<int>& arr) {
    vector<int> reversed = arr;
    int n = reversed.size();
    for (int i = 0; i < n / 2; i++) {
        swap(reversed[i], reversed[n - 1 - i]);
    }
    return reversed;
}

// Atomic Code 3: Kiểm tra mảng có sắp xếp hay không
bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // 1. Tìm phần tử lớn nhất
    int maxElement = findMax(arr);
    cout << maxElement << endl;
    
    // 2. Đảo ngược mảng
    vector<int> reversed = reverseArray(arr);
    for (int i = 0; i < n; i++) {
        cout << reversed[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // 3. Kiểm tra mảng gốc có sắp xếp hay không
    bool sorted = isSorted(arr);
    cout << (sorted ? "YES" : "NO") << endl;
    
    return 0;
}