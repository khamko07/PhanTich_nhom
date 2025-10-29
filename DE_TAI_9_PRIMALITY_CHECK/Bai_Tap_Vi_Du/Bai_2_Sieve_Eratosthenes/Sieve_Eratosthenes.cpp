#include <iostream>
#include <vector>
using namespace std;

// Sieve of Eratosthenes - Tìm tất cả số nguyên tố ≤ n
vector<bool> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            // Đánh dấu tất cả bội số của i bắt đầu từ i²
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

// Phiên bản tối ưu chỉ xét số lẻ
vector<bool> sieveOptimized(int n) {
    if (n < 2) return vector<bool>(n + 1, false);
    
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    // Xử lý số 2 riêng
    for (int i = 4; i <= n; i += 2) {
        isPrime[i] = false;
    }
    
    // Chỉ xét số lẻ
    for (int i = 3; i * i <= n; i += 2) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

// Hàm debug để hiển thị quá trình sàng
void debugSieve(int n) {
    cout << "=== DEBUG SIEVE OF ERATOSTHENES ===" << endl;
    cout << "Finding all primes up to " << n << endl;
    
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    cout << "Initial: Mark 0 and 1 as not prime" << endl;
    cout << "Assume all numbers from 2 to " << n << " are prime" << endl << endl;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            cout << "Sieving with prime " << i << ":" << endl;
            cout << "  Marking multiples starting from " << (i * i) << ": ";
            
            vector<int> marked;
            for (int j = i * i; j <= n; j += i) {
                if (isPrime[j]) {
                    marked.push_back(j);
                    isPrime[j] = false;
                }
            }
            
            for (int x : marked) cout << x << " ";
            cout << endl;
            
            // Hiển thị số nguyên tố còn lại
            cout << "  Remaining primes: ";
            for (int k = 2; k <= min(n, 50); k++) {
                if (isPrime[k]) cout << k << " ";
            }
            if (n > 50) cout << "...";
            cout << endl << endl;
        }
    }
    
    // Đếm kết quả cuối cùng
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) count++;
    }
    
    cout << "Final result: " << count << " primes found" << endl;
    cout << "Primes: ";
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) cout << i << " ";
    }
    cout << endl;
    cout << "==================================" << endl;
}

// Tính số lượng operations
int countOperations(int n) {
    int operations = 0;
    
    for (int i = 2; i * i <= n; i++) {
        // Giả sử i là nguyên tố (worst case)
        for (int j = i * i; j <= n; j += i) {
            operations++;
        }
    }
    
    return operations;
}

int main() {
    int n;
    cin >> n;
    
    vector<bool> isPrime = sieveOfEratosthenes(n);
    
    // Đếm số nguyên tố
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            count++;
        }
    }
    
    cout << count << endl;
    
    // In tất cả số nguyên tố
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    // Uncomment để xem debug info (chỉ với n nhỏ):
    // if (n <= 50) {
    //     debugSieve(n);
    // }
    
    // Uncomment để so sánh hiệu suất:
    // vector<bool> optimized = sieveOptimized(n);
    // cout << "Optimized sieve gives same result: " << (isPrime == optimized ? "YES" : "NO") << endl;
    // cout << "Estimated operations: " << countOperations(n) << endl;
    
    return 0;
}