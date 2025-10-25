#include <iostream>
using namespace std;

// Hàm con: kiểm tra số chẵn
bool isEven(int n) {
    return n % 2 == 0;
}

// Hàm con: tính lũy thừa nhanh (chia nhỏ vấn đề)
long long fastPower(long long base, int exp) {
    if (exp == 0) {
        return 1;
    }
    
    if (exp == 1) {
        return base;
    }
    
    // Chia nhỏ: a^n = (a^(n/2))^2 nếu n chẵn
    //           a^n = a * (a^(n/2))^2 nếu n lẻ
    long long half = fastPower(base, exp / 2);
    
    if (isEven(exp)) {
        return half * half;
    } else {
        return base * half * half;
    }
}

// Hàm chính: tính lũy thừa
long long power(long long a, int n) {
    if (n < 0) {
        return 0; // Không xử lý số mũ âm trong bài này
    }
    
    return fastPower(a, n);
}

int main() {
    long long a;
    int n;
    cin >> a >> n;
    
    long long result = power(a, n);
    cout << result << endl;
    
    return 0;
}