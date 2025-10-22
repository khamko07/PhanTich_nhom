#include <iostream>
using namespace std;

long long hanoi(int n) {
    if (n == 1) {
        return 1;
    }
    return 2 * hanoi(n - 1) + 1;
}

int main() {
    int n;
    cin >> n;
    cout << hanoi(n) << endl;
    return 0;
}