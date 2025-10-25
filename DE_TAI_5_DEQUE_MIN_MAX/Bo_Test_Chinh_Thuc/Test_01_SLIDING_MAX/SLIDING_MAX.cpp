#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Sliding Window Maximum - Bài toán cơ bản với Deque
vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
    deque<int> dq; // Monotonic decreasing deque (lưu chỉ số)
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // Xóa các phần tử nằm ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Duy trì tính giảm dần: xóa các phần tử nhỏ hơn hoặc bằng
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Thêm kết quả khi window đã đủ k phần tử
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    vector<int> result = slidingWindowMaximum(nums, k);
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}