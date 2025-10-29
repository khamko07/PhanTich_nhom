#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Maximum Rectangle in Binary Matrix sử dụng Largest Rectangle in Histogram
class MaxRectangle {
private:
    // Tính largest rectangle trong histogram
    int largestRectangleArea(vector<int>& heights) {
        deque<int> stack;
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
    
public:
    int maximalRectangle(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> heights(m, 0);
        int maxArea = 0;
        
        for (int i = 0; i < n; i++) {
            // Cập nhật heights cho hàng hiện tại
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 1) {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }
            
            // Tính largest rectangle cho histogram hiện tại
            int area = largestRectangleArea(heights);
            maxArea = max(maxArea, area);
        }
        
        return maxArea;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    
    MaxRectangle solver;
    cout << solver.maximalRectangle(matrix) << endl;
    
    return 0;
}