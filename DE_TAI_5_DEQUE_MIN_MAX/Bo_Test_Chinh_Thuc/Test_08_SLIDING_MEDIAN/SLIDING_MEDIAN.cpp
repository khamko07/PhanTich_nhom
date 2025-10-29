#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>
using namespace std;

// Sliding Window Median - Bài toán nâng cao
class SlidingWindowMedian {
private:
    multiset<int> left, right; // left: nửa nhỏ, right: nửa lớn
    int k;
    
    void balance() {
        // Đảm bảo left.size() == right.size() hoặc left.size() == right.size() + 1
        if (left.size() > right.size() + 1) {
            right.insert(*left.rbegin());
            left.erase(left.find(*left.rbegin()));
        } else if (right.size() > left.size()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    }
    
    void addNumber(int num) {
        if (left.empty() || num <= *left.rbegin()) {
            left.insert(num);
        } else {
            right.insert(num);
        }
        balance();
    }
    
    void removeNumber(int num) {
        if (left.count(num)) {
            left.erase(left.find(num));
        } else {
            right.erase(right.find(num));
        }
        balance();
    }
    
    double getMedian() {
        if (k % 2 == 1) {
            return *left.rbegin();
        } else {
            return (*left.rbegin() + *right.begin()) / 2.0;
        }
    }
    
public:
    SlidingWindowMedian(int windowSize) : k(windowSize) {}
    
    vector<double> medianSlidingWindow(vector<int>& nums) {
        vector<double> result;
        
        for (int i = 0; i < nums.size(); i++) {
            addNumber(nums[i]);
            
            if (i >= k) {
                removeNumber(nums[i - k]);
            }
            
            if (i >= k - 1) {
                result.push_back(getMedian());
            }
        }
        
        return result;
    }
};

// Phương pháp đơn giản sử dụng sorting (cho window nhỏ)
vector<int> slidingWindowMedianSimple(vector<int>& nums, int k) {
    vector<int> result;
    
    for (int i = 0; i <= (int)nums.size() - k; i++) {
        vector<int> window;
        for (int j = i; j < i + k; j++) {
            window.push_back(nums[j]);
        }
        
        sort(window.begin(), window.end());
        
        // Lấy median (làm tròn xuống nếu k chẵn)
        int median = window[(k - 1) / 2];
        result.push_back(median);
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
    
    // Sử dụng phương pháp đơn giản cho bài này
    vector<int> result = slidingWindowMedianSimple(nums, k);
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}