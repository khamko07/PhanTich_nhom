#include <iostream>
#include <vector>
using namespace std;

void insertAtPosition(vector<int>& arr, int pos, int val) {
    arr.insert(arr.begin() + pos, val);
}

int main() {
    int n, pos, val;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> pos >> val;
    
    insertAtPosition(arr, pos, val);
    
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size()-1) cout << " ";
    }
    cout << endl;
    return 0;
}