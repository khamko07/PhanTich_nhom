#include <iostream>
using namespace std;

// Recursive Thinking: Sử dụng tư duy đệ quy để giải bài toán
// Bài toán: Tính tổng các chữ số của một số nguyên dương

// Cách 1: Đệ quy đơn giản
int digitSumRecursive(int n) {
    // Trường hợp cơ sở: số có 1 chữ số
    if (n < 10) {
        return n;
    }
    
    // Trường hợp đệ quy: tách chữ số cuối và gọi đệ quy cho phần còn lại
    return (n % 10) + digitSumRecursive(n / 10);
}

// Cách 2: Đệ quy với debug info
int digitSumRecursiveDebug(int n, int depth = 0) {
    // In thông tin debug
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "digitSum(" << n << ")" << endl;
    
    // Trường hợp cơ sở
    if (n < 10) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "Base case: return " << n << endl;
        return n;
    }
    
    // Trường hợp đệ quy
    int lastDigit = n % 10;
    int remaining = n / 10;
    
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Split: " << n << " = " << remaining << " + " << lastDigit << endl;
    
    int result = lastDigit + digitSumRecursiveDebug(remaining, depth + 1);
    
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Return: " << lastDigit << " + " << (result - lastDigit) << " = " << result << endl;
    
    return result;
}

// Cách 3: Đệ quy đuôi (tail recursion)
int digitSumTailRecursive(int n, int accumulator = 0) {
    // Trường hợp cơ sở
    if (n == 0) {
        return accumulator;
    }
    
    // Gọi đệ quy với accumulator cập nhật
    return digitSumTailRecursive(n / 10, accumulator + (n % 10));
}

// Cách 4: Đệ quy với memoization (cho bài toán phức tạp hơn)
#include <unordered_map>
unordered_map<int, int> memo;

int digitSumMemoized(int n) {
    // Kiểm tra trong bộ nhớ đệm
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    
    // Trường hợp cơ sở
    if (n < 10) {
        memo[n] = n;
        return n;
    }
    
    // Tính toán và lưu vào bộ nhớ đệm
    int result = (n % 10) + digitSumMemoized(n / 10);
    memo[n] = result;
    
    return result;
}

// Hàm so sánh hiệu suất các cách tiếp cận
void compareApproaches(int n) {
    cout << "=== COMPARISON OF APPROACHES ===" << endl;
    cout << "Input: " << n << endl;
    
    int result1 = digitSumRecursive(n);
    cout << "Simple Recursive: " << result1 << endl;
    
    int result2 = digitSumTailRecursive(n);
    cout << "Tail Recursive: " << result2 << endl;
    
    int result3 = digitSumMemoized(n);
    cout << "Memoized: " << result3 << endl;
    
    cout << "===============================" << endl;
}

// Hàm kiểm tra tính đúng đắn
bool testDigitSum() {
    return (digitSumRecursive(12345) == 15) &&
           (digitSumRecursive(999) == 27) &&
           (digitSumRecursive(1) == 1) &&
           (digitSumRecursive(0) == 0);
}

int main() {
    int n;
    cin >> n;
    
    // Sử dụng đệ quy đơn giản
    int result = digitSumRecursive(n);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // cout << "\n=== DEBUG INFO ===" << endl;
    // digitSumRecursiveDebug(n);
    
    // Uncomment để so sánh các cách tiếp cận:
    // compareApproaches(n);
    
    // Uncomment để chạy test:
    // if (testDigitSum()) {
    //     cout << "All tests passed!" << endl;
    // } else {
    //     cout << "Some tests failed!" << endl;
    // }
    
    return 0;
}