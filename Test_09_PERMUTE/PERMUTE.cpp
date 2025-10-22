#include <iostream>
using namespace std;

long long permute(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * permute(n - 1);
}

int main() {
    int n;
    cin >> n;
    cout << permute(n) << endl;
    return 0;
}