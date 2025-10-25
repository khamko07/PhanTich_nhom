#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Sliding Window Maximum sử dụng Deque
vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
    deque<int> dq; // Lưu chỉ số của các phần tử
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // Xóa các chỉ số nằm ngoài window hiện tại
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Duy trì tính giảm dần trong deque
        // Xóa các phần tử nhỏ hơn hoặc bằng phần tử hiện tại
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
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

// Hàm debug để hiển thị trạng thái deque
void debugSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    
    cout << "=== DEBUG SLIDING WINDOW ===" << endl;
    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    cout << "Window size: " << k << endl << endl;
    
    for (int i = 0; i < nums.size(); i++) {
        cout << "Step " << i + 1 << ": Processing nums[" << i << "] = " << nums[i] << endl;
        
        // Xóa các chỉ số nằm ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            cout << "  Remove index " << dq.front() << " (out of window)" << endl;
            dq.pop_front();
        }
        
        // Xóa các phần tử nhỏ hơn
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            cout << "  Remove index " << dq.back() << " (value " << nums[dq.back()] << " <= " << nums[i] << ")" << endl;
            dq.pop_back();
        }
        
        dq.push_back(i);
        cout << "  Add index " << i << endl;
        
        cout << "  Deque indices: ";
        for (int idx : dq) cout << idx << " ";
        cout << endl;
        
        cout << "  Deque values: ";
        for (int idx : dq) cout << nums[idx] << " ";
        cout << endl;
        
        if (i >= k - 1) {
            cout << "  Window [" << (i - k + 1) << ", " << i << "] max = " << nums[dq.front()] << endl;
        }
        
        cout << endl;
    }
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
    
    // Uncomment để xem debug info:
    // debugSlidingWindow(nums, k);
    
    return 0;
}