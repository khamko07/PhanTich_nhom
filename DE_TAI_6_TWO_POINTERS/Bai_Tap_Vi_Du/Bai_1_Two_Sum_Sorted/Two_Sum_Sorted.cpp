#include <iostream>
#include <vector>
using namespace std;

// Two Sum trên mảng đã sắp xếp sử dụng Two Pointers
pair<int, int> twoSum(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;  // Cần tổng lớn hơn, di chuyển left
        } else {
            right--; // Cần tổng nhỏ hơn, di chuyển right
        }
    }
    
    return {-1, -1}; // Không tìm thấy
}

// Hàm debug để hiển thị quá trình tìm kiếm
void debugTwoSum(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    cout << "=== DEBUG TWO SUM ===" << endl;
    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    cout << "Target: " << target << endl << endl;
    
    int step = 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        
        cout << "Step " << step++ << ": ";
        cout << "left=" << left << "(" << nums[left] << "), ";
        cout << "right=" << right << "(" << nums[right] << "), ";
        cout << "sum=" << sum << endl;
        
        if (sum == target) {
            cout << "Found! Indices: " << left << ", " << right << endl;
            break;
        } else if (sum < target) {
            cout << "Sum < target, move left pointer" << endl;
            left++;
        } else {
            cout << "Sum > target, move right pointer" << endl;
            right--;
        }
        cout << endl;
    }
    
    if (left >= right) {
        cout << "Not found!" << endl;
    }
    
    cout << "===================" << endl;
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
    
    // Uncomment để xem debug info:
    // debugTwoSum(nums, target);
    
    return 0;
}