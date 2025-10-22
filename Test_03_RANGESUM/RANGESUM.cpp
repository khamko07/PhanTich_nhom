#include <iostream>
#include <vector>
using namespace std;

long long rangeSum(vector<int>& arr, int l, int r) {
    long long sum = 0;
    for (int i = l; i <= r; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int n, l, r;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> l >> r;
    cout << rangeSum(arr, l, r) << endl;
    return 0;
}