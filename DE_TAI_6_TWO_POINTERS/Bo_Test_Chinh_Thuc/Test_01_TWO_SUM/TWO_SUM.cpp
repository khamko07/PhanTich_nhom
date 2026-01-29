#include <iostream>
#include <vector>
using namespace std;

// Two Sum trên mảng đã sắp xếp - Bài toán cơ bản với Two Pointers
pair<int, int> twoSum(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
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
    
    pair<int, int> result = twoSum(nums, target);
    cout << result.first << " " << result.second << endl;
    
    return 0;
}