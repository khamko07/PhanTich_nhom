#include <iostream>
#include <vector>
#include <deque>
#include <string>
using namespace std;

// Complete Deque Problem - Bài toán tổng hợp với nhiều thao tác
class CompleteDeque {
private:
    vector<int> arr;
    
    // Tìm maximum trong k phần tử cuối
    int findMaxInLastK(int k) {
        if (k <= 0 || k > arr.size()) return -1;
        
        deque<int> dq;
        int start = arr.size() - k;
        
        for (int i = start; i < arr.size(); i++) {
            // Duy trì tính giảm dần
            while (!dq.empty() && arr[dq.back()] <= arr[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        
        return arr[dq.front()];
    }
    
    // Tìm minimum trong k phần tử cuối
    int findMinInLastK(int k) {
        if (k <= 0 || k > arr.size()) return -1;
        
        deque<int> dq;
        int start = arr.size() - k;
        
        for (int i = start; i < arr.size(); i++) {
            // Duy trì tính tăng dần
            while (!dq.empty() && arr[dq.back()] >= arr[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        
        return arr[dq.front()];
    }
    
public:
    CompleteDeque(vector<int>& initial) : arr(initial) {}
    
    void addElement(int x) {
        arr.push_back(x);
    }
    
    void popElement() {
        if (!arr.empty()) {
            arr.pop_back();
        }
    }
    
    int getMaxInLastK(int k) {
        return findMaxInLastK(k);
    }
    
    int getMinInLastK(int k) {
        return findMinInLastK(k);
    }
    
    void printArray() {
        cout << "Array: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
    }
    
    int size() {
        return arr.size();
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    
    vector<int> initial(n);
    for (int i = 0; i < n; i++) {
        cin >> initial[i];
    }
    
    CompleteDeque deque(initial);
    
    for (int i = 0; i < q; i++) {
        string operation;
        cin >> operation;
        
        if (operation == "ADD") {
            int x;
            cin >> x;
            deque.addElement(x);
        } else if (operation == "MAX") {
            int k;
            cin >> k;
            int result = deque.getMaxInLastK(k);
            if (result != -1) {
                cout << result << endl;
            } else {
                cout << "INVALID" << endl;
            }
        } else if (operation == "MIN") {
            int k;
            cin >> k;
            int result = deque.getMinInLastK(k);
            if (result != -1) {
                cout << result << endl;
            } else {
                cout << "INVALID" << endl;
            }
        } else if (operation == "POP") {
            deque.popElement();
        } else if (operation == "SIZE") {
            cout << deque.size() << endl;
        } else if (operation == "PRINT") {
            deque.printArray();
        }
    }
    
    return 0;
}