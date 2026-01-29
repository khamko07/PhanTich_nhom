#include <iostream>
#include <vector>
#include <deque>
#include <climits>
using namespace std;

// Shortest Subarray with Sum at Least K
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefixSum(n + 1, 0);
    
    // Tính prefix sum
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    
    deque<int> dq; // Lưu chỉ số của prefix sum
    int minLength = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        // Kiểm tra xem có thể tạo subarray với sum >= k không
        while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= k) {
            minLength = min(minLength, i - dq.front());
            dq.pop_front();
        }
        
        // Duy trì tính tăng dần của prefix sum trong deque
        // Xóa các prefix sum lớn hơn hoặc bằng prefix sum hiện tại
        while (!dq.empty() && prefixSum[dq.back()] >= prefixSum[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return minLength == INT_MAX ? -1 : minLength;
}

// Phương pháp brute force để so sánh (chỉ dùng cho mảng nhỏ)
int shortestSubarrayBruteForce(vector<int>& nums, int k) {
    int n = nums.size();
    int minLength = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum >= k) {
                minLength = min(minLength, j - i + 1);
                break;
            }
        }
    }
    
    return minLength == INT_MAX ? -1 : minLength;
}

// Hàm debug để hiển thị quá trình
void debugShortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefixSum(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    
    cout << "=== DEBUG SHORTEST SUBARRAY ===" << endl;
    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    cout << "Target sum: " << k << endl;
    cout << "Prefix sums: ";
    for (long long x : prefixSum) cout << x << " ";
    cout << endl << endl;
    
    deque<int> dq;
    int minLength = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        cout << "Step " << i + 1 << ": Processing prefixSum[" << i << "] = " << prefixSum[i] << endl;
        
        // Kiểm tra subarray
        while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= k) {
            int length = i - dq.front();
            cout << "  Found subarray [" << dq.front() << ", " << i-1 << "] with sum " 
                 << (prefixSum[i] - prefixSum[dq.front()]) << ", length = " << length << endl;
            minLength = min(minLength, length);
            dq.pop_front();
        }
        
        // Duy trì tính tăng dần
        while (!dq.empty() && prefixSum[dq.back()] >= prefixSum[i]) {
            cout << "  Remove index " << dq.back() << " (prefixSum = " << prefixSum[dq.back()] << ")" << endl;
            dq.pop_back();
        }
        
        dq.push_back(i);
        cout << "  Add index " << i << endl;
        
        cout << "  Deque: ";
        for (int idx : dq) cout << idx << "(" << prefixSum[idx] << ") ";
        cout << endl;
        cout << "  Current min length: " << (minLength == INT_MAX ? -1 : minLength) << endl << endl;
    }
    
    cout << "Final result: " << (minLength == INT_MAX ? -1 : minLength) << endl;
    cout << "===============================" << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int result = shortestSubarray(nums, k);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // debugShortestSubarray(nums, k);
    
    // Uncomment để so sánh với brute force (chỉ với mảng nhỏ):
    // if (n <= 20) {
    //     int bruteResult = shortestSubarrayBruteForce(nums, k);
    //     cout << "Brute force result: " << bruteResult << endl;
    //     cout << "Results match: " << (result == bruteResult ? "YES" : "NO") << endl;
    // }
    
    return 0;
}