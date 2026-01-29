#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Cách tiếp cận 1: Brute Force - O(n²)
pair<int, int> twoSumBruteForce(vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Cách tiếp cận 2: Hash Table - O(n)
pair<int, int> twoSumOptimal(vector<int>& nums, int target) {
    unordered_map<int, int> numMap;
    
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i};
        }
        
        numMap[nums[i]] = i;
    }
    
    return {-1, -1};
}

int main() {
    int n, target;
    cin >> n >> target;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    // Sử dụng cách tiếp cận tối ưu
    pair<int, int> result = twoSumOptimal(nums, target);
    
    cout << result.first << " " << result.second << endl;
    
    return 0;
}