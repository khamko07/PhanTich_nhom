#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Largest Rectangle in Histogram sử dụng Deque như Stack
int largestRectangleArea(vector<int>& heights) {
    deque<int> stack; // Sử dụng deque như stack
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i <= n; i++) {
        int currentHeight = (i == n) ? 0 : heights[i];
        
        while (!stack.empty() && heights[stack.back()] > currentHeight) {
            int height = heights[stack.back()];
            stack.pop_back();
            
            int width = stack.empty() ? i : i - stack.back() - 1;
            maxArea = max(maxArea, height * width);
        }
        
        stack.push_back(i);
    }
    
    return maxArea;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    
    cout << largestRectangleArea(heights) << endl;
    
    return 0;
}