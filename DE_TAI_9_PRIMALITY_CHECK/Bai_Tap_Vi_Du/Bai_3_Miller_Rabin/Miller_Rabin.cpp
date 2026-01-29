#include <iostream>
#include <vector>
#include <random>
using namespace std;

long long power(long long a, long long d, long long n) {
    long long result = 1;
    a %= n;
    while (d > 0) {
        if (d & 1) {
            result = (__int128)result * a % n;
        }
        a = (__int128)a * a % n;
        d >>= 1;
    }
    return result;
}

bool millerRabinTest(long long n, long long a) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    // Viết n-1 = d * 2^r với d lẻ
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    // Tính a^d mod n
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1) {
        return true;
    }
    
    // Lặp r-1 lần
    for (int i = 0; i < r - 1; i++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return true;
        }
    }
    
    return false;
}

bool isPrimeMillerRabin(long long n, int k = 10) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    
    // Sử dụng witnesses deterministic cho số nhỏ
    vector<long long> witnesses = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    for (int i = 0; i < min(k, (int)witnesses.size()); i++) {
        if (witnesses[i] >= n) break;
        if (!millerRabinTest(n, witnesses[i])) {
            return false;
        }
    }
    
    return true;
}

// Hàm debug để hiển thị quá trình Miller-Rabin
void debugMillerRabin(long long n, long long a) {
    cout << "=== DEBUG MILLER-RABIN TEST ===" << endl;
    cout << "Testing " << n << " with witness " << a << endl;
    
    if (n <= 1) {
        cout << n << " <= 1, not prime" << endl;
        return;
    }
    
    if (n == 2) {
        cout << "2 is prime" << endl;
        return;
    }
    
    if (n % 2 == 0) {
        cout << n << " is even, not prime" << endl;
        return;
    }
    
    // Viết n-1 = d * 2^r
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    cout << n << " - 1 = " << d << " * 2^" << r << endl;
    
    // Tính a^d mod n
    long long x = power(a, d, n);
    cout << a << "^" << d << " mod " << n << " = " << x << endl;
    
    if (x == 1 || x == n - 1) {
        cout << "x = 1 or x = n-1, possibly prime" << endl;
        return;
    }
    
    // Lặp r-1 lần
    for (int i = 0; i < r - 1; i++) {
        x = (__int128)x * x % n;
        cout << "x^2 mod " << n << " = " << x << endl;
        
        if (x == n - 1) {
            cout << "x = n-1, possibly prime" << endl;
            return;
        }
    }
    
    cout << "No condition satisfied, composite" << endl;
    cout << "===============================" << endl;
}

// Hàm so sánh hiệu suất
void performanceComparison(vector<long long>& testCases) {
    cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
    cout << "Number\t\tMiller-Rabin\tResult" << endl;
    cout << "------\t\t------------\t------" << endl;
    
    for (long long n : testCases) {
        auto start = chrono::high_resolution_clock::now();
        bool result = isPrimeMillerRabin(n);
        auto end = chrono::high_resolution_clock::now();
        
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << n << "\t\t" << duration.count() << " μs\t\t" 
             << (result ? "PRIME" : "COMPOSITE") << endl;
    }
    cout << "===============================" << endl;
}

int main() {
    long long n;
    cin >> n;
    
    bool result = isPrimeMillerRabin(n);
    cout << (result ? "YES" : "NO") << endl;
    
    // Uncomment để xem debug info:
    // debugMillerRabin(n, 2);
    
    // Test cases cho performance comparison
    // vector<long long> testCases = {97, 1009, 10007, 100003, 1000003, 982451653, 9999999967LL};
    // performanceComparison(testCases);
    
    return 0;
}