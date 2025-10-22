#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool is_safe(vector<int>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col) {
            return false;
        }
    }
    
    for (int i = 0; i < row; i++) {
        if (abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    
    return true;
}

int solve_nqueens(vector<int>& board, int row, int n) {
    if (row == n) {
        return 1;
    }
    
    int count = 0;
    for (int col = 0; col < n; col++) {
        if (is_safe(board, row, col, n)) {
            board[row] = col;
            count += solve_nqueens(board, row + 1, n);
        }
    }
    
    return count;
}

int main() {
    int n;
    cin >> n;
    vector<int> board(n, -1);
    cout << solve_nqueens(board, 0, n) << endl;
    return 0;
}