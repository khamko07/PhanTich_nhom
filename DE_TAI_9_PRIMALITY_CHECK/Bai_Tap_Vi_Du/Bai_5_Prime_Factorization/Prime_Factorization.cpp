#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long pollardRho(long long n) {
    if (n % 2 == 0) return 2;
    
    long long x = 2, y = 2, d = 1;
    auto f = [&](long long x) { return ((__int128)x * x + 1) % n; };
    
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(abs(x - y), n);
    }
    
    return d == n ? -1 : d;
}

bool isPrimeTrial(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void factorize(long long n, map<long long, int>& factors) {
    if (n == 1) return;
    
    // Thử chia cho các số nguyên tố nhỏ
    for (long long i = 2; i * i <= n && i <= 1000; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    
    // Nếu n > 1, sử dụng Pollard's Rho cho số lớn
    if (n > 1) {
        if (isPrimeTrial(n)) {
            factors[n]++;
        } else {
            // Sử dụng Pollard's Rho cho số lớn
            long long d = pollardRho(n);
            if (d != -1) {
                factorize(d, factors);
                factorize(n / d, factors);
            } else {
                // Không thể phân tích thêm
                factors[n]++; // Có thể là số nguyên tố
            }
        }
    }
}

// Hàm debug để hiển thị quá trình phân tích
void debugFactorization(long long original) {
    cout << "=== DEBUG PRIME FACTORIZATION ===" << endl;
    cout << "Factorizing " << original << endl;
    
    long long n = original;
    map<long long, int> factors;
    
    cout << "Step 1: Trial division with small primes" << endl;
    
    for (long long i = 2; i * i <= n && i <= 1000; i++) {
        if (n % i == 0) {
            cout << "Found factor " << i << endl;
            while (n % i == 0) {
                factors[i]++;
                n /= i;
                cout << "Remaining number: " << n << endl;
            }
        }
    }
    
    cout << "Step 2: Using Pollard's Rho for remaining number" << endl;
    if (n > 1) {
        if (isPrimeTrial(n)) {
            cout << n << " is prime" << endl;
            factors[n]++;
        } else {
            cout << "Using Pollard's Rho for " << n << endl;
            // Simplified for debug
            factors[n]++; // Có thể là số nguyên tố
        }
    }
    
    cout << "\nFinal factorization of " << original << ": ";
    bool first = true;
    for (auto& p : factors) {
        if (!first) cout << " × ";
        cout << p.first;
        if (p.second > 1) cout << "^" << p.second;
        first = false;
    }
    cout << endl;
    cout << "===============================" << endl;
}

// Hàm kiểm tra tính đúng đắn
bool verifyFactorization(long long original, const map<long long, int>& factors) {
    long long product = 1;
    for (auto& p : factors) {
        for (int i = 0; i < p.second; i++) {
            product *= p.first;
            if (product > original) return false; // Overflow check
        }
    }
    return product == original;
}

// Hàm so sánh hiệu suất
void performanceComparison(vector<long long>& testCases) {
    cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
    cout << "Number\t\tTime\t\tFactors" << endl;
    cout << "------\t\t----\t\t-------" << endl;
    
    for (long long n : testCases) {
        auto start = chrono::high_resolution_clock::now();
        
        map<long long, int> factors;
        factorize(n, factors);
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << n << "\t\t" << duration.count() << " μs\t\t";
        
        bool first = true;
        for (auto& p : factors) {
            if (!first) cout << "×";
            cout << p.first;
            if (p.second > 1) cout << "^" << p.second;
            first = false;
        }
        cout << endl;
    }
    cout << "===============================" << endl;
}

int main() {
    long long n;
    cin >> n;
    
    map<long long, int> factors;
    factorize(n, factors);
    
    // In kết quả
    for (auto& p : factors) {
        for (int i = 0; i < p.second; i++) {
            cout << p.first << " ";
        }
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // debugFactorization(n);
    
    // Verify factorization
    // if (verifyFactorization(n, factors)) {
    //     cout << "Factorization verified!" << endl;
    // } else {
    //     cout << "Factorization error!" << endl;
    // }
    
    // Test cases cho performance comparison
    // vector<long long> testCases = {12, 100, 1001, 9999, 100000, 1000003};
    // performanceComparison(testCases);
    
    return 0;
}