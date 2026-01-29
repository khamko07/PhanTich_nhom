#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Range Minimum Query với Deque (cho các truy vấn liên tiếp)
class RangeMinimumQuery {
private:
    vector<int> arr;
    
public:
    RangeMinimumQuery(vector<int>& nums) : arr(nums) {}
    
    // Truy vấn minimum trong khoảng [left, right] sử dụng deque
    int queryRange(int left, int right) {
        deque<int> dq;
        
        // Xử lý phần tử đầu tiên
        dq.push_back(left);
        int minVal = arr[left];
        
        // Xử lý các phần tử còn lại
        for (int i = left + 1; i <= right; i++) {
            // Duy trì tính tăng dần trong deque
            while (!dq.empty() && arr[dq.back()] >= arr[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
            
            // Minimum luôn ở đầu deque
            minVal = arr[dq.front()];
        }
        
        return minVal;
    }
    
    // Phương pháp đơn giản để so sánh
    int queryRangeSimple(int left, int right) {
        int minVal = arr[left];
        for (int i = left + 1; i <= right; i++) {
            minVal = min(minVal, arr[i]);
        }
        return minVal;
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    RangeMinimumQuery rmq(arr);
    
    for (int i = 0; i < q; i++) {
        int left, right;
        cin >> left >> right;
        
        // Chuyển về chỉ số 0-based
        left--; right--;
        
        cout << rmq.queryRange(left, right) << endl;
    }
    
    return 0;
}