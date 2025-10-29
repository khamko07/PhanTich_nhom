#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Constrained Subsequence Sum với Deque Optimization
int constrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> dq; // Monotonic decreasing deque cho dp values
    
    int maxSum = nums[0];
    
    for (int i = 0; i < n; i++) {
        // Xóa các chỉ số nằm ngoài khoảng k
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        // Tính dp[i]
        dp[i] = nums[i];
        if (!dq.empty()) {
            dp[i] = max(dp[i], nums[i] + dp[dq.front()]);
        }
        
        maxSum = max(maxSum, dp[i]);
        
        // Duy trì tính giảm dần trong deque
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        
        // Chỉ thêm nếu dp[i] > 0
        if (dp[i] > 0) {
            dq.push_back(i);
        }
    }
    
    return maxSum;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    cout << constrainedSubsetSum(nums, k) << endl;
    
    return 0;
}