#include <iostream>
using namespace std;

int sum_digits(int n) {
    if (n < 10) {
        return n;
    }
    return n % 10 + sum_digits(n / 10);
}

int main() {
    int n;
    cin >> n;
    cout << sum_digits(n) << endl;
    return 0;
}