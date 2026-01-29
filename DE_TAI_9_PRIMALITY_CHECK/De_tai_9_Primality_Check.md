# Đề Tài 9: Primality Check - Kiểm Tra Số Nguyên Tố

## 1. Trình Bày Lý Thuyết

### 1.1 Giới Thiệu Về Số Nguyên Tố

**Số nguyên tố** là số tự nhiên lớn hơn 1 chỉ có đúng hai ước số dương là 1 và chính nó. Việc kiểm tra một số có phải là số nguyên tố hay không (primality testing) là một bài toán cơ bản trong số học với nhiều ứng dụng quan trọng trong mật mã học, bảo mật thông tin và khoa học máy tính.

### 1.2 Các Phương Pháp Kiểm Tra Số Nguyên Tố

**1. Trial Division (Chia thử):**
- Kiểm tra tất cả các số từ 2 đến √n
- Độ phức tạp: O(√n)
- Đơn giản nhưng chậm với số lớn

**2. Sieve of Eratosthenes (Sàng Eratosthenes):**
- Tìm tất cả số nguyên tố ≤ n
- Độ phức tạp: O(n log log n)
- Hiệu quả cho việc tìm nhiều số nguyên tố

**3. Miller-Rabin Test:**
- Thuật toán xác suất
- Độ phức tạp: O(k log³ n) với k lần test
- Rất nhanh với số lớn

**4. Fermat's Little Theorem:**
- Dựa trên định lý Fermat nhỏ
- Có thể cho kết quả sai với Carmichael numbers

### 1.3 Trial Division - Phương Pháp Cơ Bản

**Ý tưởng:** Kiểm tra xem n có chia hết cho số nào từ 2 đến √n không.

```cpp
bool isPrimeTrial(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
```

**Tối ưu hóa:**
- Chỉ kiểm tra số lẻ (trừ 2)
- Chỉ kiểm tra đến √n
- Có thể sử dụng wheel factorization

### 1.4 Sieve of Eratosthenes

**Ý tưởng:** Loại bỏ tất cả bội số của các số nguyên tố đã tìm được.

```cpp
vector<bool> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}
```

**Tối ưu hóa:**
- Segmented Sieve cho số rất lớn
- Wheel Sieve để giảm số phép toán
- Bitwise operations để tiết kiệm bộ nhớ###
 1.5 Miller-Rabin Primality Test

**Ý tưởng:** Dựa trên định lý Fermat nhỏ và tính chất của căn bậc hai của 1 modulo n.

**Thuật toán:**
1. Viết n-1 = d × 2^r với d lẻ
2. Chọn ngẫu nhiên a trong [2, n-2]
3. Tính x = a^d mod n
4. Nếu x = 1 hoặc x = n-1, n có thể là nguyên tố
5. Lặp r-1 lần: x = x² mod n, nếu x = n-1, n có thể là nguyên tố
6. Nếu không thỏa mãn điều kiện nào, n là hợp số

```cpp
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
    
    // Viết n-1 = d * 2^r
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

bool isPrimeMillerRabin(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    
    // Các witness deterministic cho n < 3,317,044,064,679,887,385,961,981
    vector<long long> witnesses = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    for (long long a : witnesses) {
        if (a >= n) break;
        if (!millerRabinTest(n, a)) {
            return false;
        }
    }
    
    return true;
}
```

### 1.6 Pollard's Rho Algorithm

**Mục đích:** Tìm ước số của hợp số n (không phải để kiểm tra nguyên tố).

```cpp
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
```

## 2. Các Thuật Toán Nâng Cao

### 2.1 Segmented Sieve

**Mục đích:** Tìm số nguyên tố trong khoảng [L, R] với R - L nhỏ nhưng R có thể rất lớn.

```cpp
vector<bool> segmentedSieve(long long L, long long R) {
    long long limit = sqrt(R) + 1;
    vector<bool> isPrime = sieveOfEratosthenes(limit);
    vector<long long> primes;
    
    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    vector<bool> segmentPrime(R - L + 1, true);
    
    for (long long prime : primes) {
        long long start = max(prime * prime, (L + prime - 1) / prime * prime);
        
        for (long long j = start; j <= R; j += prime) {
            segmentPrime[j - L] = false;
        }
    }
    
    if (L == 1) segmentPrime[0] = false;
    
    return segmentPrime;
}
```

### 2.2 Wheel Factorization

**Ý tưởng:** Bỏ qua các số chia hết cho các số nguyên tố nhỏ (2, 3, 5, ...).

```cpp
class Wheel235 {
private:
    vector<int> wheel = {4, 6, 10, 12, 16, 18, 22, 24};
    int pos = 0;
    
public:
    int next(int current) {
        if (current < 2) return 2;
        if (current < 3) return 3;
        if (current < 5) return 5;
        
        current += wheel[pos];
        pos = (pos + 1) % wheel.size();
        return current;
    }
};

bool isPrimeWheel(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3 || n == 5) return true;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) return false;
    
    Wheel235 wheel;
    for (long long i = 7; i * i <= n; i = wheel.next(i)) {
        if (n % i == 0) {
            return false;
        }
    }
    
    return true;
}
```

### 2.3 Deterministic Miller-Rabin

**Ý tưởng:** Sử dụng tập witness cố định thay vì ngẫu nhiên.

```cpp
bool isDeterministicPrime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    // Witnesses cho các khoảng khác nhau
    vector<vector<long long>> witnessRanges = {
        {2, 3},                                    // n < 1,373,653
        {2, 3, 5},                                // n < 25,326,001
        {2, 3, 5, 7},                             // n < 3,215,031,751
        {2, 3, 5, 7, 11},                         // n < 4,759,123,141
        {2, 3, 5, 7, 11, 13},                     // n < 1,122,004,669,633
        {2, 3, 5, 7, 11, 13, 17},                 // n < 2,152,302,898,747
        {2, 3, 5, 7, 11, 13, 17, 19, 23}         // n < 3,474,749,660,383
    };
    
    vector<long long> witnesses;
    if (n < 1373653LL) witnesses = witnessRanges[0];
    else if (n < 25326001LL) witnesses = witnessRanges[1];
    else if (n < 3215031751LL) witnesses = witnessRanges[2];
    else if (n < 4759123141LL) witnesses = witnessRanges[3];
    else if (n < 1122004669633LL) witnesses = witnessRanges[4];
    else if (n < 2152302898747LL) witnesses = witnessRanges[5];
    else witnesses = witnessRanges[6];
    
    for (long long a : witnesses) {
        if (a >= n) break;
        if (!millerRabinTest(n, a)) {
            return false;
        }
    }
    
    return true;
}
```## 3. B
ài Tập Thực Hành

### Bài 1: Trial Division - Kiểm Tra Nguyên Tố Cơ Bản
**Đề bài**: Kiểm tra một số có phải là số nguyên tố hay không bằng phương pháp chia thử.

```cpp
#include <iostream>
#include <cmath>
using namespace std;

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

// Hàm debug để hiển thị quá trình kiểm tra
void debugTrialDivision(long long n) {
    cout << "=== DEBUG TRIAL DIVISION ===" << endl;
    cout << "Checking if " << n << " is prime" << endl;
    
    if (n < 2) {
        cout << n << " < 2, not prime" << endl;
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
    
    cout << "Checking odd divisors from 3 to " << (long long)sqrt(n) << endl;
    
    for (long long i = 3; i * i <= n; i += 2) {
        cout << "Checking " << n << " % " << i << " = " << (n % i);
        if (n % i == 0) {
            cout << " -> Found divisor! Not prime" << endl;
            return;
        }
        cout << " -> Continue" << endl;
    }
    
    cout << "No divisors found, " << n << " is prime" << endl;
    cout << "===========================" << endl;
}

int main() {
    long long n;
    cin >> n;
    
    bool result = isPrimeTrial(n);
    cout << (result ? "YES" : "NO") << endl;
    
    // Uncomment để xem debug info:
    // debugTrialDivision(n);
    
    return 0;
}
```

### Bài 2: Sieve of Eratosthenes
**Đề bài**: Tìm tất cả số nguyên tố không vượt quá n.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<bool> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            // Đánh dấu tất cả bội số của i
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

// Hàm debug để hiển thị quá trình sàng
void debugSieve(int n) {
    cout << "=== DEBUG SIEVE OF ERATOSTHENES ===" << endl;
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    cout << "Initial: All numbers from 2 to " << n << " marked as prime" << endl;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            cout << "\nSieving with prime " << i << ":" << endl;
            cout << "Marking multiples: ";
            
            for (int j = i * i; j <= n; j += i) {
                if (isPrime[j]) {
                    cout << j << " ";
                    isPrime[j] = false;
                }
            }
            cout << endl;
        }
    }
    
    cout << "\nFinal primes: ";
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "==================================" << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<bool> isPrime = sieveOfEratosthenes(n);
    
    // Đếm và in số nguyên tố
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            count++;
        }
    }
    
    cout << count << endl;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // debugSieve(n);
    
    return 0;
}
```

### Bài 3: Miller-Rabin Test
**Đề bài**: Kiểm tra số nguyên tố bằng thuật toán Miller-Rabin.

```cpp
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

int main() {
    long long n;
    cin >> n;
    
    bool result = isPrimeMillerRabin(n);
    cout << (result ? "YES" : "NO") << endl;
    
    // Uncomment để xem debug info:
    // debugMillerRabin(n, 2);
    
    return 0;
}
```### Bài 4: S
egmented Sieve
**Đề bài**: Tìm số nguyên tố trong khoảng [L, R] với R có thể rất lớn.

```cpp
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
    
    return 0;
}
```

### Bài 5: Prime Factorization
**Đề bài**: Phân tích một số thành thừa số nguyên tố.

```cpp
#include <iostream>
#include <vector>
#include <map>
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
        if (n % i == 0) return yaphed Cryptogr of Appli Handbook),thms (CLRSAlgorin to ductio, Introheckity C Primalki - VNOI Wi*:m khảo*Tham]  
** nă thángnh**: [Ngàyhoàn thàgày *Nm]  
*: [Tên nhóác giả**
**T``

---

}
`sult;return re
    ;
    }>>= 1 exp   mod);
     e, base, basmulmod(  base = 
          }od);
    se, m(result, baodsult = mulmre      ) {
       if (exp & 1
       > 0) { while (exp  1;
   sult = reong long    lod) {
g long monxp, lg long eg base, lond(long lon powmo
long long}

 * b) % mod;28)an ((int1tur   re
 d) { long moongb, lng a, long loong long od(llmong long mu

lint128;= __128  intingusr
latoán moduho phép __int128 cSử dụng 
```cpp
// Rất Lớn Số 6.3 Xử Lý## ```

#
};
 }
   t;urren c   return     % 8;
= (pos + 1)   pos s];
      ments[po increrent +=
        cur     }
      7;
         return        turn 5;
  < 5) re if (current        rn 3;
   eturrent < 3) r if (cu          rn 2;
 tunt < 2) re if (curre
            7) {ent < if (curr      urrent) {
 t next(int clic:
    inpub    
os = 0;
    int p24};
, 22, , 16, 18, 6, 10, 12ts = {4cremen in vector<int>{
    Wheel235 2,3,5
classorization / Wheel factcpp
/``ốc Độ
`a Ti Ưu Hó6.2 Tố
### ``
}
}
`    }
        }
          [j] = 0;
      isPrime          ) {
  = i; j + * i; j <= n= ij (int         for ]) {
    e[i (isPrim     if
   n; i++) { i * i <= int i = 2; (   for   
 
 [1] = 0; = isPrimerime[0] isP 1
   t cả bit =/ Đặt tất(); / isPrime.se {
   n)int mizedSieve(

void optie; + 1> isPrim<MAXN0;
bitsetAXN = 100000 Mconst intitset>

#include <bol>or<bo vectvì thay  dụng bitset// Sửpp
ộ Nhớ
```cóa B.1 Tối Ưu H
### 6
aoâng Cật Nvà Kỹ Thuối Ưu Hóa  T

## 6.oán số họchuật tatics**: TMathemal tationn
- **Compuiorizata trên factoPhá mã dựalysis**: ptantố
- **Crysố nguyên phân bố iên cứu ghy**: Number TheorDụng
- **Noán Học Ứng ## 5.3 T
#n tố
nguyêới số ing vsistent hashonSystems**: Ced ibutistr**D PRNG
- trong nguyên tố ation**: Sốumber Generdom N*Ranllision
- * giảm co tố để số nguyêndụng Sử ons**:tiuncHash F**áy Tính
- c Mhoa Họ2 Kệt

### 5.biên tố đặc ần số nguygraphy**: Ctourve Crypiptic C
- **Elllớnuyên tố số ng: Sử dụng lman**e-Hel
- **Diffiớn l tích sốủa việc phân khăn cên khó trSA**: Dựa Học
- **Rt MãMậ.1  Tế

### 5g Dụng Thực Ứn
## 5.g
g khoảnn tố tron nguyê tất cả sốn
- Cầng R lớhỏ nhưnới R - L n[L, R] v Khoảng 
-:**nted Sieve

**Segmehỏất sai rất n suận xáchấp nhao
- C tốc độ c Cần
-8) 10^1 >ố rất lớn (n Sbin:**
-*Miller-Ra

*hớó đủ bộ n C)
- < 10^8 lớn (n quáôngn kh ≤ n
- ên tốả số nguyất cm t:**
- Tìnesosthef Erat

**Sieve o xác 100%nh chíuảkết q
- Cần a một vài số Kiểm trn < 10^6)
-hỏ (*
- Số non:*al Divisi

**Trig Pháp Nào?Phương ụnhi Nào Sử D### 4.2 K

p cài đặt |ức tạPhhoảng |  cho kiệu quảR-L) | H + O(√ng R) | -L) log lo(Rve | O(√n + nted Sieme) |
| Seghể sai(có tác suất t nhanh | X(1) | Rấ) | O³ nlogRabin | O(k 
| Miller-n bộ nhớ | số | Tốo nhiều chhanhO(n) | N log n) |  O(n loghenes |ratostf ESieve o
|  | số lớnhậm vớixác | Cnh hí, cảnn giĐơn) | O(1) | | O(√l Division 
| Tria------|-----|-----------|-----------------|---|---------------iểm |
| đ| Nhược| Ưu điểm Không gian gian | p | Thời ng phá

| Phươạphức To Sánh Độ P S4.1 Bảng# 
##Pháp
ơng ác Phư Sánh C

## 4. So0;
}
```  return 
    
  zation(n);debugFactori
    // info:g  debuxement để  Uncomm
    //endl;
     cout <<     }
       }
";
    st << "  << p.firout      c      {
 ++)nd; i< p.seco = 0; i int ir (  fo) {
      factors& p : (auto   for ả
  qu In kết    
    // factors);
n,e(ctoriz
    fators; facg long, int>
    map<lonn;
    in >>     cg n;
on  long lmain() {
  
int }
" << endl;
=============================== << "== cout   t << endl;
ou  c}
      = false;
      firstecond;
   << p.sut << "^" ond > 1) co   if (p.sec     t;
 p.firs cout <<
        ";out << " ×!first) c      if (
  : factors) {uto& p    for (a
  true;st =ool fir
    b";nal << ": << origion of " actorizati"\nFt <<   cou    
     }
       }
 
 n]++; factors[        
   ebug for dplified Sim  //          
n << endl;or " <<  flard's Rhosing Pol<< "U      cout {
         } else n]++;
     s[     factor    endl;
    prime" << < " iscout << n <  
          ial(n)) {f (isPrimeTr  i    << endl;
  n  <<  number "ing Remain 2:Step"  cout << 1) {
      f (n >  
    i   }
       }
     }
            
dl;<< eng"  remainin"<< n <<   "  " <<    cout        = i;
          n /
          ors[i]++;  fact               i == 0) {
(n %    while        endl;
 " << i << und factor cout << "Fo          
  % i == 0) { (n      if   {
 +)100; i+<=  n && i  * i <=i = 2; i(long long 
    for ndl;imes" << ell prth smavision wi: Trial dip 1 "Ste  cout <<;
    
  ginal = ng long oris;
    lonnt> factor i<long long,map    
    endl;
< n <<  <ng "iziactorcout << "F   << endl;
 ON ===" ACTORIZATIUG PRIME F"=== DEB cout << {
   ng long n) loctorization(bugFavoid de tích
á trình phânển thị qug để hiHàm debu}

//    }
tích thêm
 ể phân Không thrs[n]++; // to      fac{
  else rs);
    } actoze(n / d, f   factoris);
     tororize(d, fac       fact1) {
 if (d != -  dRho(n);
  arllg d = polong lonớn
    số ld's Rho cho g Pollar dụn  // Sử
    }
  n;
    turre       s[n]++;
  factor     al(n)) {
  rimeTri  if (isP  ;
    
== 1) return (n 
    if    }
   }
   = i;
       /     n      s[i]++;
 ctor  fa         0) {
 == hile (n % i     w++) {
    = 1000; i&& i <<= n 2; i * i ng long i =  (lofor
    yên tố nhỏguố n các s chochia// Thử        

     }eturn;
    rn]++;
        factors[(n)) {
    imeTrialPr  if (is
    
  return; 1)  ==if (n {
    t>& factors)ng long, inn, map<log long torize(lonac
void f}
rue;
    return t    }
false;
