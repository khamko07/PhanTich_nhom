#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Monotonic Deque Applications - Tìm minimum trong window kết thúc tại mỗi vị trí
vector<int> findMinimumInWindows(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> result(n);
    deque<int> dq; // Monotonic increasing deque
    
    for (int i = 0; i < n; i++) {
        // Xóa các phần tử nằm ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Duy trì tính tăng dần
        while (!dq.empty() && nums[dq.back()] >= nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Tính minimum cho window kết thúc tại i
        if (i < k - 1) {
            // Window chưa đủ k phần tử, lấy min từ đầu đến i
            result[i] = nums[dq.front()];
        } else {
            // Window đủ k phần tử
            result[i] = nums[dq.front()];
        }
    }
    
    return result;
}

// Hàm bổ trợ: tìm maximum trong window kết thúc tại mỗi vị trí
vector<int> findMaximumInWindows(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> result(n);
    deque<int> dq; // Monotonic decreasing deque
    
    for (int i = 0; i < n; i++) {
        // Xóa các phần tử nằm ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Duy trì tính giảm dần
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Tính maximum cho window kết thúc tại i
        result[i] = nums[dq.front()];
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
    
    vector<int> minResults = findMinimumInWindows(nums, k);
    
    for (int i = 0; i < n; i++) {
        cout << minResults[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}