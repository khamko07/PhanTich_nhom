#include <iostream>
#include <vector>
using namespace std;

int countFrequency(vector<int>& arr, int x) {
    int count = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == x) {
            count++;
        }
    }
    return count;
}

int main() {
    int n, x;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> x;
    cout << countFrequency(arr, x) << endl;
    return 0;
}