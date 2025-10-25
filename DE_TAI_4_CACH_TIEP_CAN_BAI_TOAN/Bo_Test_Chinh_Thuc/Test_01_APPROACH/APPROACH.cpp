#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Giải bài toán Two Sum với hai cách tiếp cận

// Cách 1: Brute Force - O(n²)
pair<int, int> twoSumBruteForce(vector<int>& nums, int target) {
    int n = nums.size();
    
    // Duyệt tất cả các cặp phần tử
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    
    return {-1, -1}; // Không tìm thấy
}

// Cách 2: Hash Table - O(n)
pair<int, int> twoSumOptimal(vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex;
    
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        
        // Kiểm tra xem complement có trong map không
        if (numToIndex.find(complement) != numToIndex.end()) {
            return {numToIndex[complement], i};
        }
        
        // Lưu số hiện tại và chỉ số vào map
        numToIndex[nums[i]] = i;
    }
    
    return {-1, -1}; // Không tìm thấy
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