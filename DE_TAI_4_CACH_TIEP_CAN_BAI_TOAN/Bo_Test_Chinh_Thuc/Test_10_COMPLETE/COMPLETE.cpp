#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Complete Problem Solving: Bài toán tổng hợp
// Tìm đường đi từ góc trên trái đến góc dưới phải với tổng lớn nhất
// Chỉ được di chuyển xuống dưới hoặc sang phải

// Cách tiếp cận 1: Đệ quy đơn giản (có thể bị timeout với ma trận lớn)
int maxPathSumRecursive(vector<vector<int>>& matrix, int row, int col) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    // Trường hợp cơ sở: đến đích
    if (row == n - 1 && col == m - 1) {
        return matrix[row][col];
    }
    
    // Nếu vượt quá biên
    if (row >= n || col >= m) {
        return INT_MIN; // Giá trị rất nhỏ để loại bỏ đường đi này
    }
    
    // Thử cả hai hướng: xuống dưới và sang phải
    int downPath = maxPathSumRecursive(matrix, row + 1, col);
    int rightPath = maxPathSumRecursive(matrix, row, col + 1);
    
    return matrix[row][col] + max(downPath, rightPath);
}

// Cách tiếp cận 2: Dynamic Programming (Bottom-up)
int maxPathSumDP(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    // Tạo bảng DP
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    // Khởi tạo điểm bắt đầu
    dp[0][0] = matrix[0][0];
    
    // Điền hàng đầu tiên (chỉ có thể đi từ trái sang phải)
    for (int j = 1; j < m; j++) {
        dp[0][j] = dp[0][j-1] + matrix[0][j];
    }
    
    // Điền cột đầu tiên (chỉ có thể đi từ trên xuống dưới)
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + matrix[i][0];
    }
    
    // Điền phần còn lại của bảng
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = matrix[i][j] + max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    return dp[n-1][m-1];
}

// Cách tiếp cận 3: DP tối ưu không gian (chỉ dùng 1 hàng)
int maxPathSumOptimized(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    // Chỉ cần lưu trữ một hàng
    vector<int> dp(m, 0);
    
    // Khởi tạo hàng đầu tiên
    dp[0] = matrix[0][0];
    for (int j = 1; j < m; j++) {
        dp[j] = dp[j-1] + matrix[0][j];
    }
    
    // Xử lý từng hàng tiếp theo
    for (int i = 1; i < n; i++) {
        dp[0] += matrix[i][0]; // Cột đầu tiên
        
        for (int j = 1; j < m; j++) {
            dp[j] = matrix[i][j] + max(dp[j], dp[j-1]);
        }
    }
    
    return dp[m-1];
}

// Hàm truy vết đường đi (để hiển thị đường đi tối ưu)
void printPath(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    vector<vector<int>> dp(n, vector<int>(m, 0));
    vector<vector<char>> path(n, vector<char>(m, ' '));
    
    // Tính DP và lưu hướng đi
    dp[0][0] = matrix[0][0];
    
    for (int j = 1; j < m; j++) {
        dp[0][j] = dp[0][j-1] + matrix[0][j];
        path[0][j] = 'R'; // Right
    }
    
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + matrix[i][0];
        path[i][0] = 'D'; // Down
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (dp[i-1][j] > dp[i][j-1]) {
                dp[i][j] = matrix[i][j] + dp[i-1][j];
                path[i][j] = 'D';
            } else {
                dp[i][j] = matrix[i][j] + dp[i][j-1];
                path[i][j] = 'R';
            }
        }
    }
    
    // Truy vết đường đi
    cout << "=== OPTIMAL PATH ===" << endl;
    cout << "Max sum: " << dp[n-1][m-1] << endl;
    cout << "Path: ";
    
    vector<pair<int, int>> pathCoords;
    int i = n - 1, j = m - 1;
    pathCoords.push_back({i, j});
    
    while (i > 0 || j > 0) {
        if (path[i][j] == 'D') {
            i--;
        } else {
            j--;
        }
        pathCoords.push_back({i, j});
    }
    
    reverse(pathCoords.begin(), pathCoords.end());
    
    for (int k = 0; k < pathCoords.size(); k++) {
        cout << "(" << pathCoords[k].first << "," << pathCoords[k].second << ")";
        if (k < pathCoords.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    cout << "Values: ";
    for (int k = 0; k < pathCoords.size(); k++) {
        int r = pathCoords[k].first;
        int c = pathCoords[k].second;
        cout << matrix[r][c];
        if (k < pathCoords.size() - 1) cout << " + ";
    }
    cout << " = " << dp[n-1][m-1] << endl;
    cout << "===================" << endl;
}

// Hàm so sánh hiệu suất các cách tiếp cận
void compareApproaches(vector<vector<int>>& matrix) {
    cout << "=== APPROACH COMPARISON ===" << endl;
    
    // DP approach
    int result1 = maxPathSumDP(matrix);
    cout << "Dynamic Programming: " << result1 << endl;
    
    // Optimized approach
    int result2 = maxPathSumOptimized(matrix);
    cout << "Space Optimized: " << result2 << endl;
    
    // Recursive (chỉ với ma trận nhỏ)
    if (matrix.size() <= 10 && matrix[0].size() <= 10) {
        int result3 = maxPathSumRecursive(matrix, 0, 0);
        cout << "Recursive: " << result3 << endl;
    } else {
        cout << "Recursive: Skipped (too large)" << endl;
    }
    
    cout << "==========================" << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // Sử dụng cách tiếp cận tối ưu
    int result = maxPathSumDP(matrix);
    cout << result << endl;
    
    // Uncomment để xem đường đi chi tiết:
    // printPath(matrix);
    
    // Uncomment để so sánh các cách tiếp cận:
    // compareApproaches(matrix);
    
    return 0;
}