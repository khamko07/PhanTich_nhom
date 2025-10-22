#include <iostream>
using namespace std;

int count_subsets(int n, int k, int pos = 1, int selected = 0) {
    if (selected == k) {
        return 1;
    }
    if (pos > n) {
        return 0;
    }
    
    // Chọn phần tử pos
    int count1 = count_subsets(n, k, pos + 1, selected + 1);
    // Không chọn phần tử pos
    int count2 = count_subsets(n, k, pos + 1, selected);
    
    return count1 + count2;
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << count_subsets(n, k) << endl;
    return 0;
}