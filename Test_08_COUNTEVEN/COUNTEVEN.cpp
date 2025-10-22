#include <iostream>
#include <vector>
using namespace std;

int countEven(vector<int>& arr) {
    int count = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << countEven(arr) << endl;
    return 0;
}