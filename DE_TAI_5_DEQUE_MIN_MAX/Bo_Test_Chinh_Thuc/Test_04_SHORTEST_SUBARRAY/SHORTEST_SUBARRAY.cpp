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
    
    deque<int> dq; // Monotonic increasing deque cho prefix sum
    int minLength = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        // Tìm subarray có sum >= k
        while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= k) {
            minLength = min(minLength, i - dq.front());
            dq.pop_front();
        }
        
        // Duy trì tính tăng dần của prefix sum
        while (!dq.empty() && prefixSum[dq.back()] >= prefixSum[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return minLength == INT_MAX ? -1 : minLength;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    cout << shortestSubarray(nums, k) << endl;
    
    return 0;
}