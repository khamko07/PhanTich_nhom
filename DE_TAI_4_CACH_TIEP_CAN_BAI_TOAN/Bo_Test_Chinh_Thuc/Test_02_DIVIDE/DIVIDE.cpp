#include <iostream>
using namespace std;

// Chia nhỏ vấn đề: Tính lũy thừa a^n hiệu quả

// Hàm con: kiểm tra số chẵn
bool isEven(int n) {
    return n % 2 == 0;
}

// Hàm con: tính lũy thừa nhanh bằng chia đôi
long long fastPower(long long base, int exponent) {
    // Trường hợp cơ sở
    if (exponent == 0) {
        return 1;
    }
    
    if (exponent == 1) {
        return base;
    }
    
    // Chia nhỏ vấn đề: tính a^(n/2)
    long long halfPower = fastPower(base, exponent / 2);
    
    // Kết hợp kết quả
    if (isEven(exponent)) {
        // Nếu n chẵn: a^n = (a^(n/2))^2
        return halfPower * halfPower;
    } else {
        // Nếu n lẻ: a^n = a * (a^(n/2))^2
        return base * halfPower * halfPower;
    }
}

// Hàm chính: xử lý input và gọi hàm con
long long power(long long a, int n) {
    if (n < 0) {
        return 0; // Không xử lý số mũ âm
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