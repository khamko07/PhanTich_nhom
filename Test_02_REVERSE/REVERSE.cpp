#include <iostream>
#include <vector>
using namespace std;

void reverseArray(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n/2; i++) {
        swap(arr[i], arr[n-1-i]);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    reverseArray(arr);
    
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n-1) cout << " ";
    }
    cout << endl;
    return 0;
}