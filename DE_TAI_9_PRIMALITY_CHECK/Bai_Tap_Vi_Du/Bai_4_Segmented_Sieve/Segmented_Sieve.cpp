#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<bool> simpleSieve(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

vector<bool> segmentedSieve(long long L, long long R) {
    long long limit = sqrt(R) + 1;
    vector<bool> isPrime = simpleSieve(limit);
    
    // Lấy tất cả số nguyên tố <= √R
    vector<long long> primes;
    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    // Tạo mảng cho segment [L, R]
    vector<bool> segmentPrime(R - L + 1, true);
    
    // Sàng với từng số nguyên tố
    for (long long prime : primes) {
        // Tìm bội số đầu tiên của prime trong [L, R]
        long long start = max(prime * prime, (L + prime - 1) / prime * prime);
        
        // Đánh dấu tất cả bội số
        for (long long j = start; j <= R; j += prime) {
            segmentPrime[j - L] = false;
        }
    }
    
    // Xử lý trường hợp đặc biệt
    if (L == 1) segmentPrime[0] = false;
    
    return segmentPrime;
}

// Hàm debug để hiển thị quá trình segmented sieve
void debugSegmentedSieve(long long L, long long R) {
    cout << "=== DEBUG SEGMENTED SIEVE ===" << endl;
    cout << "Finding primes in range [" << L << ", " << R << "]" << endl;
    
    long long limit = sqrt(R) + 1;
    cout << "Step 1: Find all primes up to √" << R << " = " << limit << endl;
    
    vector<bool> isPrime = simpleSieve(limit);
    vector<long long> primes;
    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    cout << "Found " << primes.size() << " primes: ";
    for (long long p : primes) cout << p << " ";
    cout << endl;
    
    cout << "\nStep 2: Sieve segment [" << L << ", " << R << "]" << endl;
    vector<bool> segmentPrime(R - L + 1, true);
    
    for (long long prime : primes) {
        long long start = max(prime * prime, (L + prime - 1) / prime * prime);
        cout << "Sieving with prime " << prime << ", starting from " << start << endl;
        
        for (long long j = start; j <= R; j += prime) {
            segmentPrime[j - L] = false;
        }
    }
    
    if (L == 1) segmentPrime[0] = false;
    
    cout << "\nPrimes in [" << L << ", " << R << "]: ";
    for (long long i = L; i <= R; i++) {
        if (segmentPrime[i - L]) {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "============================" << endl;
}

// Hàm so sánh với sieve thông thường
void compareWithNormalSieve(long long L, long long R) {
    cout << "\n=== MEMORY USAGE COMPARISON ===" << endl;
    
    // Segmented Sieve
    long long segmentSize = R - L + 1;
    long long limit = sqrt(R) + 1;
    
    cout << "Segmented Sieve:" << endl;
    cout << "- Segment size: " << segmentSize << " elements" << endl;
    cout << "- Base sieve size: " << limit << " elements" << endl;
    cout << "- Total memory: ~" << (segmentSize + limit) << " elements" << endl;
    
    // Normal Sieve (if we were to use it)
    cout << "\nNormal Sieve (hypothetical):" << endl;
    cout << "- Would need: " << R << " elements" << endl;
    cout << "- Memory saved: " << (R - segmentSize - limit) << " elements" << endl;
    cout << "- Reduction factor: " << (double)R / (segmentSize + limit) << "x" << endl;
    cout << "===============================" << endl;
}

int main() {
    long long L, R;
    cin >> L >> R;
    
    vector<bool> segmentPrime = segmentedSieve(L, R);
    
    // Đếm và in số nguyên tố
    int count = 0;
    for (long long i = L; i <= R; i++) {
        if (segmentPrime[i - L]) {
            count++;
        }
    }
    
    cout << count << endl;
    for (long long i = L; i <= R; i++) {
        if (segmentPrime[i - L]) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // debugSegmentedSieve(L, R);
    // compareWithNormalSieve(L, R);
    
    return 0;
}