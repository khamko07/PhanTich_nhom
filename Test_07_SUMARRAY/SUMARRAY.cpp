#include <iostream>
#include <vector>
using namespace std;

long long sumArray(vector<int>& arr) {
    long long sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << sumArray(arr) << endl;
    return 0;
}