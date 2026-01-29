#include <iostream>
#include <vector>
using namespace std;

// Container With Most Water sử dụng Two Pointers
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        // Tính diện tích hiện tại
        int width = right - left;
        int currentHeight = min(height[left], height[right]);
        int currentArea = width * currentHeight;
        
        maxWater = max(maxWater, currentArea);
        
        // Di chuyển pointer có chiều cao nhỏ hơn
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxWater;
}

// Phương pháp brute force để so sánh
int maxAreaBruteForce(vector<int>& height) {
    int maxWater = 0;
    int n = height.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int width = j - i;
            int currentHeight = min(height[i], height[j]);
            int area = width * currentHeight;
            maxWater = max(maxWater, area);
        }
    }
    
    return maxWater;
}

// Hàm debug để hiển thị quá trình
void debugMaxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    
    cout << "=== DEBUG CONTAINER WATER ===" << endl;
    cout << "Heights: ";
    for (int h : height) cout << h << " ";
    cout << endl << endl;
    
    int step = 1;
    while (left < right) {
        int width = right - left;
        int currentHeight = min(height[left], height[right]);
        int currentArea = width * currentHeight;
        
        cout << "Step " << step++ << ": ";
        cout << "left=" << left << "(" << height[left] << "), ";
        cout << "right=" << right << "(" << height[right] << ")" << endl;
        cout << "  Width=" << width << ", Height=" << currentHeight;
        cout << ", Area=" << currentArea << endl;
        
        maxWater = max(maxWater, currentArea);
        
        if (height[left] < height[right]) {
            cout << "  Move left (smaller height)" << endl;
            left++;
        } else {
            cout << "  Move right (smaller or equal height)" << endl;
            right--;
        }
        
        cout << "  Current max area: " << maxWater << endl << endl;
    }
    
    cout << "Final max area: " << maxWater << endl;
    cout << "============================" << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> height(n);
    for (int i = 0; i < n; i++) {
        cin >> height[i];
    }
    
    int result = maxArea(height);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // debugMaxArea(height);
    
    // Uncomment để so sánh với brute force:
    // int bruteResult = maxAreaBruteForce(height);
    // cout << "Brute force result: " << bruteResult << endl;
    // cout << "Results match: " << (result == bruteResult ? "YES" : "NO") << endl;
    
    return 0;
}