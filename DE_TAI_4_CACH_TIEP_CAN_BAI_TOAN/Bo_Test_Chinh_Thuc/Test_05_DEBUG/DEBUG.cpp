#include <iostream>
#include <vector>
using namespace std;

// Debug Strategy: Tìm và sửa lỗi trong code tính tổng số chẵn

// Code gốc có lỗi (đã comment):
/*
int sumEvenBuggy(vector<int>& arr) {
    int sum = 0;
    for (int i = 1; i <= arr.size(); i++) {    // Lỗi 1: i bắt đầu từ 1, i <= size()
        if (arr[i] % 2 = 0) {                  // Lỗi 2: dùng = thay vì ==
            sum += arr[i];
        }
    }
    return sum;
}
*/

// Code đã sửa lỗi:
int sumEvenFixed(vector<int>& arr) {
    int sum = 0;
    
    // Sửa lỗi 1: i bắt đầu từ 0, i < arr.size()
    for (int i = 0; i < arr.size(); i++) {
        // Sửa lỗi 2: sử dụng == để so sánh
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    
    return sum;
}

// Hàm debug với thông tin chi tiết
int sumEvenWithDebug(vector<int>& arr) {
    int sum = 0;
    cout << "=== DEBUG INFO ===" << endl;
    cout << "Array size: " << arr.size() << endl;
    
    for (int i = 0; i < arr.size(); i++) {
        cout << "Checking arr[" << i << "] = " << arr[i];
        
        if (arr[i] % 2 == 0) {
            sum += arr[i];
            cout << " (even, added to sum)" << endl;
        } else {
            cout << " (odd, skipped)" << endl;
        }
        
        cout << "Current sum: " << sum << endl;
    }
    
    cout << "Final sum: " << sum << endl;
    cout << "=================" << endl;
    
    return sum;
}

// Hàm kiểm tra tính đúng đắn
bool testSumEven() {
    vector<int> testCase1 = {1, 2, 3, 4, 5};
    int expected1 = 6; // 2 + 4
    int result1 = sumEvenFixed(testCase1);
    
    vector<int> testCase2 = {2, 4, 6, 8};
    int expected2 = 20; // 2 + 4 + 6 + 8
    int result2 = sumEvenFixed(testCase2);
    
    vector<int> testCase3 = {1, 3, 5, 7};
    int expected3 = 0; // không có số chẵn
    int result3 = sumEvenFixed(testCase3);
    
    return (result1 == expected1) && (result2 == expected2) && (result3 == expected3);
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Sử dụng hàm đã sửa lỗi
    int result = sumEvenFixed(arr);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // sumEvenWithDebug(arr);
    
    // Uncomment để chạy test:
    // if (testSumEven()) {
    //     cout << "All tests passed!" << endl;
    // } else {
    //     cout << "Some tests failed!" << endl;
    // }
    
    return 0;
}