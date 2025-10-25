#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Optimization Techniques: Tối ưu hóa từ O(n²) xuống O(n)
// Bài toán: Tìm số lượng cặp có hiệu bằng k

// Cách 1: Brute Force - O(n²)
int countPairsBruteForce(vector<int>& arr, int k) {
    int count = 0;
    int n = arr.size();
    
    // Duyệt tất cả các cặp
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (abs(arr[i] - arr[j]) == k) {
                count++;
            }
        }
    }
    
    return count;
}

// Cách 2: Hash Set - O(n)
int countPairsOptimal(vector<int>& arr, int k) {
    unordered_set<int> numSet;
    int count = 0;
    
    // Thêm tất cả phần tử vào set
    for (int num : arr) {
        numSet.insert(num);
    }
    
    // Với mỗi phần tử, kiểm tra xem num+k hoặc num-k có trong set không
    for (int num : arr) {
        // Chỉ đếm một chiều để tránh đếm trùng
        if (numSet.count(num + k)) {
            count++;
        }
    }
    
    return count;
}

// Cách 3: Two Pointers (sau khi sắp xếp) - O(n log n)
int countPairsTwoPointers(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
    
    int count = 0;
    int left = 0, right = 1;
    int n = arr.size();
    
    while (right < n) {
        int diff = arr[right] - arr[left];
        
        if (diff == k) {
            count++;
            left++;
            right++;
        } else if (diff < k) {
            right++;
        } else {
            left++;
            if (left == right) {
                right++;
            }
        }
    }
    
    return count;
}

// Hàm đo thời gian thực thi (để so sánh hiệu suất)
#include <chrono>

void measurePerformance(vector<int>& arr, int k) {
    auto start = chrono::high_resolution_clock::now();
    
    // Test Brute Force
    start = chrono::high_resolution_clock::now();
    int result1 = countPairsBruteForce(arr, k);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test Optimal
    start = chrono::high_resolution_clock::now();
    int result2 = countPairsOptimal(arr, k);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test Two Pointers
    vector<int> arrCopy = arr; // Tạo bản sao vì sắp xếp sẽ thay đổi mảng
    start = chrono::high_resolution_clock::now();
    int result3 = countPairsTwoPointers(arrCopy, k);
    end = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "=== PERFORMANCE COMPARISON ===" << endl;
    cout << "Brute Force: " << result1 << " pairs, " << duration1.count() << " μs" << endl;
    cout << "Hash Set: " << result2 << " pairs, " << duration2.count() << " μs" << endl;
    cout << "Two Pointers: " << result3 << " pairs, " << duration3.count() << " μs" << endl;
    cout << "=============================" << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Sử dụng thuật toán tối ưu
    int result = countPairsOptimal(arr, k);
    cout << result << endl;
    
    // Uncomment để xem so sánh hiệu suất:
    // measurePerformance(arr, k);
    
    return 0;
}