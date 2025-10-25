#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Atomic Code Functions - Các hàm cơ bản không thể chia nhỏ thêm

// Atomic 1: Tìm phần tử lớn nhất trong mảng
int findMaxElement(const vector<int>& arr) {
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// Atomic 2: Đảo ngược mảng
vector<int> reverseArray(const vector<int>& arr) {
    vector<int> reversed = arr;
    int n = reversed.size();
    
    for (int i = 0; i < n / 2; i++) {
        swap(reversed[i], reversed[n - 1 - i]);
    }
    
    return reversed;
}

// Atomic 3: Kiểm tra mảng có được sắp xếp tăng dần không
bool isSortedAscending(const vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// Atomic 4: Đếm số phần tử chẵn
int countEvenNumbers(const vector<int>& arr) {
    int count = 0;
    for (int num : arr) {
        if (num % 2 == 0) {
            count++;
        }
    }
    return count;
}

// Atomic 5: Tính tổng mảng
int calculateSum(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // 1. Phần tử lớn nhất
    int maxElement = findMaxElement(arr);
    cout << maxElement << endl;
    
    // 2. Mảng đảo ngược
    vector<int> reversed = reverseArray(arr);
    for (int i = 0; i < n; i++) {
        cout << reversed[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // 3. Kiểm tra sắp xếp
    bool sorted = isSortedAscending(arr);
    cout << (sorted ? "YES" : "NO") << endl;
    
    // 4. Số phần tử chẵn
    int evenCount = countEvenNumbers(arr);
    cout << evenCount << endl;
    
    // 5. Tổng mảng
    int sum = calculateSum(arr);
    cout << sum << endl;
    
    return 0;
}