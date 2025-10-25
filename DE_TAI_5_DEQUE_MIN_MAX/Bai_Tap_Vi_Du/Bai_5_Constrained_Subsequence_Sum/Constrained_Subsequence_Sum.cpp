#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Constrained Subsequence Sum với Deque Optimization
int constrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> dq; // Lưu chỉ số, duy trì tính giảm dần của dp values
    
    int maxSum = nums[0];
    
    for (int i = 0; i < n; i++) {
        // Xóa các chỉ số nằm ngoài khoảng k
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        // dp[i] = max(nums[i], nums[i] + max(dp[j])) với j trong [i-k, i-1]
        dp[i] = nums[i];
        if (!dq.empty()) {
            dp[i] = max(dp[i], nums[i] + dp[dq.front()]);
        }
        
        maxSum = max(maxSum, dp[i]);
        
        // Duy trì tính giảm dần trong deque
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        
        // Chỉ thêm vào deque nếu dp[i] > 0 (có thể đóng góp tích cực)
        if (dp[i] > 0) {
            dq.push_back(i);
        }
    }
    
    return maxSum;
}

// Phương pháp DP thông thường (O(nk))
int constrainedSubsetSumDP(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    
    int maxSum = nums[0];
    
    for (int i = 0; i < n; i++) {
        dp[i] = nums[i];
        
        // Tìm max trong khoảng [i-k, i-1]
        for (int j = max(0, i - k); j < i; j++) {
            if (dp[j] > 0) {
                dp[i] = max(dp[i], nums[i] + dp[j]);
            }
        }
        
        maxSum = max(maxSum, dp[i]);
    }
    
    return maxSum;
}

// Hàm debug để hiển thị quá trình DP
void debugConstrainedSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> dq;
    
    cout << "=== DEBUG CONSTRAINED SUM ===" << endl;
    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    cout << "Constraint k: " << k << endl << endl;
    
    int maxSum = nums[0];
    
    for (int i = 0; i < n; i++) {
        cout << "Step " << i + 1 << ": Processing nums[" << i << "] = " << nums[i] << endl;
        
        // Xóa các chỉ số ngoài khoảng
        while (!dq.empty() && dq.front() < i - k) {
            cout << "  Remove index " << dq.front() << " (out of range)" << endl;
            dq.pop_front();
        }
        
        // Tính dp[i]
        dp[i] = nums[i];
        if (!dq.empty()) {
            int bestPrev = dp[dq.front()];
            dp[i] = max(dp[i], nums[i] + bestPrev);
            cout << "  Best previous dp value: " << bestPrev << " at index " << dq.front() << endl;
        }
        
        cout << "  dp[" << i << "] = " << dp[i] << endl;
        maxSum = max(maxSum, dp[i]);
        
        // Cập nhật deque
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            cout << "  Remove index " << dq.back() << " (dp = " << dp[dq.back()] << ")" << endl;
            dq.pop_back();
        }
        
        if (dp[i] > 0) {
            dq.push_back(i);
            cout << "  Add index " << i << " to deque" << endl;
        } else {
            cout << "  Skip adding index " << i << " (dp[i] <= 0)" << endl;
        }
        
        cout << "  Deque: ";
        for (int idx : dq) cout << idx << "(" << dp[idx] << ") ";
        cout << endl;
        cout << "  Current max sum: " << maxSum << endl << endl;
    }
    
    cout << "Final result: " << maxSum << endl;
    cout << "DP array: ";
    for (int x : dp) cout << x << " ";
    cout << endl;
    cout << "============================" << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int result = constrainedSubsetSum(nums, k);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // debugConstrainedSum(nums, k);
    
    // Uncomment để so sánh với DP thông thường:
    // int dpResult = constrainedSubsetSumDP(nums, k);
    // cout << "DP result: " << dpResult << endl;
    // cout << "Results match: " << (result == dpResult ? "YES" : "NO") << endl;
    
    return 0;
}