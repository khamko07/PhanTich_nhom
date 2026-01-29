#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Sliding Window Minimum sử dụng Deque
vector<int> slidingWindowMinimum(vector<int>& nums, int k) {
    deque<int> dq; // Lưu chỉ số của các phần tử
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // Xóa các chỉ số nằm ngoài window hiện tại
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Duy trì tính tăng dần trong deque (cho minimum)
        // Xóa các phần tử lớn hơn hoặc bằng phần tử hiện tại
        while (!dq.empty() && nums[dq.back()] >= nums[i]) {
            dq.pop_back();
        }
        
        // Thêm chỉ số hiện tại vào deque
        dq.push_back(i);
        
        // Nếu đã có đủ k phần tử, thêm kết quả
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// So sánh với phương pháp brute force
vector<int> slidingWindowMinimumBruteForce(vector<int>& nums, int k) {
    vector<int> result;
    
    for (int i = 0; i <= (int)nums.size() - k; i++) {
        int minVal = nums[i];
        for (int j = i; j < i + k; j++) {
            minVal = min(minVal, nums[j]);
        }
        result.push_back(minVal);
    }
    
    return result;
}

// Hàm kiểm tra tính đúng đắn
bool testCorrectness(vector<int>& nums, int k) {
    vector<int> result1 = slidingWindowMinimum(nums, k);
    vector<int> result2 = slidingWindowMinimumBruteForce(nums, k);
    
    if (result1.size() != result2.size()) {
        return false;
    }
    
    for (int i = 0; i < result1.size(); i++) {
        if (result1[i] != result2[i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    vector<int> result = slidingWindowMinimum(nums, k);
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment để kiểm tra tính đúng đắn:
    // if (testCorrectness(nums, k)) {
    //     cout << "Test passed!" << endl;
    // } else {
    //     cout << "Test failed!" << endl;
    // }
    
    return 0;
}