#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Subarray Sum Equals K sử dụng Prefix Sum và Hash Map
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1; // Prefix sum = 0 xuất hiện 1 lần
    
    int prefixSum = 0, count = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        prefixSum += nums[i];
        
        // Tìm xem có prefix sum nào = (prefixSum - k) không
        if (prefixSumCount.count(prefixSum - k)) {
            count += prefixSumCount[prefixSum - k];
        }
        
        // Thêm prefix sum hiện tại vào map
        prefixSumCount[prefixSum]++;
    }
    
    return count;
}

// Phương pháp brute force để so sánh
int subarraySumBruteForce(vector<int>& nums, int k) {
    int count = 0;
    int n = nums.size();
    
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum == k) {
                count++;
            }
        }
    }
    
    return count;
}

// Hàm debug để hiển thị quá trình
void debugSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;
    
    cout << "=== DEBUG SUBARRAY SUM ===" << endl;
    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    cout << "Target k: " << k << endl << endl;
    
    int prefixSum = 0, count = 0;
    
    cout << "Initial: prefixSumCount[0] = 1" << endl << endl;
    
    for (int i = 0; i < nums.size(); i++) {
        prefixSum += nums[i];
        
        cout << "Step " << i + 1 << ": nums[" << i << "] = " << nums[i] << endl;
        cout << "  prefixSum = " << prefixSum << endl;
        cout << "  Looking for prefixSum - k = " << prefixSum << " - " << k << " = " << (prefixSum - k) << endl;
        
        if (prefixSumCount.count(prefixSum - k)) {
            int found = prefixSumCount[prefixSum - k];
            count += found;
            cout << "  Found " << found << " occurrence(s) of " << (prefixSum - k) << endl;
            cout << "  Added " << found << " subarray(s), total count = " << count << endl;
        } else {
            cout << "  Not found" << endl;
        }
        
        prefixSumCount[prefixSum]++;
        cout << "  prefixSumCount[" << prefixSum << "] = " << prefixSumCount[prefixSum] << endl;
        
        cout << "  Current map: ";
        for (auto& p : prefixSumCount) {
            cout << "(" << p.first << ":" << p.second << ") ";
        }
        cout << endl << endl;
    }
    
    cout << "Final result: " << count << endl;
    cout << "=========================" << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int result = subarraySum(nums, k);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // debugSubarraySum(nums, k);
    
    // Uncomment để so sánh với brute force:
    // int bruteResult = subarraySumBruteForce(nums, k);
    // cout << "Brute force result: " << bruteResult << endl;
    // cout << "Results match: " << (result == bruteResult ? "YES" : "NO") << endl;
    
    return 0;
}