#include <iostream>
#include <cmath>
using namespace std;

// Trial Division - Phương pháp kiểm tra nguyên tố cơ bản
bool isPrimeTrial(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    // Chỉ kiểm tra số lẻ từ 3 đến √n
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    
    return true;
}

// Phiên bản tối ưu hơn với early termination
bool isPrimeTrialOptimized(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Kiểm tra dạng 6k ± 1
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}

// Hàm debug để hiển thị quá trình kiểm tra
void debugTrialDivision(long long n) {
    cout << "=== DEBUG TRIAL DIVISION ===" << endl;
    cout << "Checking if " << n << " is prime" << endl;
    
    if (n < 2) {
        cout << n << " < 2, not prime" << endl;
        return;
    }
    
    if (n == 2) {
        cout << "2 is the only even prime" << endl;
        return;
    }
    
    if (n % 2 == 0) {
        cout << n << " is even, divisible by 2, not prime" << endl;
        return;
    }
    
    long long limit = sqrt(n);
    cout << "Checking odd divisors from 3 to " << limit << endl;
    
    int checks = 0;
    for (long long i = 3; i * i <= n; i += 2) {
        checks++;
        cout << "Check " << checks << ": " << n << " % " << i << " = " << (n % i);
        
        if (n % i == 0) {
            cout << " -> Found divisor! " << n << " = " << i << " × " << (n/i) << endl;
            cout << "Therefore, " << n << " is not prime" << endl;
            return;
        }
        cout << " -> Continue" << endl;
    }
    
    cout << "No divisors found after " << checks << " checks" << endl;
    cout << "Therefore, " << n << " is prime" << endl;
    cout << "===========================" << endl;
}

// So sánh hiệu suất giữa các phiên bản
void comparePerformance(long long n) {
    cout << "=== PERFORMANCE COMPARISON ===" << endl;
    
    auto start = chrono::high_resolution_clock::now();
    bool result1 = isPrimeTrial(n);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    start = chrono::high_resolution_clock::now();
    bool result2 = isPrimeTrialOptimized(n);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Basic trial division: " << result1 << " (" << duration1.count() << " μs)" << endl;
    cout << "Optimized version: " << result2 << " (" << duration2.count() << " μs)" << endl;
    cout << "Speedup: " << (double)duration1.count() / duration2.count() << "x" << endl;
    cout << "Results match: " << (result1 == result2 ? "YES" : "NO") << endl;
    cout << "==============================" << endl;
}

int main() {
    long long n;
    cin >> n;
    
    bool result = isPrimeTrialOptimized(n);
    cout << (result ? "YES" : "NO") << endl;
    
    // Uncomment để xem debug info:
    // debugTrialDivision(n);
    
    // Uncomment để so sánh hiệu suất:
    // comparePerformance(n);
    
    return 0;
}