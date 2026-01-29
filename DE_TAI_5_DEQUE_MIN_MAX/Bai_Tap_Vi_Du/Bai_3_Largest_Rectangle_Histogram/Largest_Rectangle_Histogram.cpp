#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Largest Rectangle in Histogram sử dụng Deque như Stack
int largestRectangleArea(vector<int>& heights) {
    deque<int> stack; // Sử dụng deque như stack, lưu chỉ số
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i <= n; i++) {
        // Thêm chiều cao 0 ở cuối để xử lý các cột còn lại
        int currentHeight = (i == n) ? 0 : heights[i];
        
        // Khi gặp cột thấp hơn, tính diện tích các hình chữ nhật có thể tạo thành
        while (!stack.empty() && heights[stack.back()] > currentHeight) {
            int height = heights[stack.back()];
            stack.pop_back();
            
            // Tính chiều rộng
            int width = stack.empty() ? i : i - stack.back() - 1;
            
            // Cập nhật diện tích lớn nhất
            maxArea = max(maxArea, height * width);
        }
        
        stack.push_back(i);
    }
    
    return maxArea;
}

// Phương pháp brute force để so sánh
int largestRectangleAreaBruteForce(vector<int>& heights) {
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i < n; i++) {
        int minHeight = heights[i];
        for (int j = i; j < n; j++) {
            minHeight = min(minHeight, heights[j]);
            int area = minHeight * (j - i + 1);
            maxArea = max(maxArea, area);
        }
    }
    
    return maxArea;
}

// Hàm debug để hiển thị quá trình tính toán
void debugLargestRectangle(vector<int>& heights) {
    deque<int> stack;
    int maxArea = 0;
    int n = heights.size();
    
    cout << "=== DEBUG LARGEST RECTANGLE ===" << endl;
    cout << "Heights: ";
    for (int h : heights) cout << h << " ";
    cout << endl << endl;
    
    for (int i = 0; i <= n; i++) {
        int currentHeight = (i == n) ? 0 : heights[i];
        cout << "Step " << i + 1 << ": Processing height " << currentHeight << endl;
        
        while (!stack.empty() && heights[stack.back()] > currentHeight) {
            int height = heights[stack.back()];
            int index = stack.back();
            stack.pop_back();
            
            int width = stack.empty() ? i : i - stack.back() - 1;
            int area = height * width;
            
            cout << "  Calculate rectangle: height=" << height 
                 << ", width=" << width << ", area=" << area << endl;
            
            maxArea = max(maxArea, area);
        }
        
        if (i < n) {
            stack.push_back(i);
            cout << "  Push index " << i << " to stack" << endl;
        }
        
        cout << "  Current max area: " << maxArea << endl;
        cout << "  Stack: ";
        for (int idx : stack) cout << idx << "(" << heights[idx] << ") ";
        cout << endl << endl;
    }
    
    cout << "Final max area: " << maxArea << endl;
    cout << "==============================" << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    
    int result = largestRectangleArea(heights);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // debugLargestRectangle(heights);
    
    // Uncomment để so sánh với brute force:
    // int bruteResult = largestRectangleAreaBruteForce(heights);
    // cout << "Brute force result: " << bruteResult << endl;
    // cout << "Results match: " << (result == bruteResult ? "YES" : "NO") << endl;
    
    return 0;
}