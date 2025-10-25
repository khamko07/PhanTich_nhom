#include <iostream>
#include <vector>
using namespace std;

// Pattern Recognition: Nhận dạng quy luật trong dãy số

// Kiểm tra cấp số cộng
bool isArithmeticSequence(const vector<int>& seq, int& commonDiff) {
    if (seq.size() < 2) return false;
    
    commonDiff = seq[1] - seq[0];
    
    for (int i = 2; i < seq.size(); i++) {
        if (seq[i] - seq[i-1] != commonDiff) {
            return false;
        }
    }
    
    return true;
}

// Kiểm tra cấp số nhân
bool isGeometricSequence(const vector<int>& seq, int& commonRatio) {
    if (seq.size() < 2 || seq[0] == 0) return false;
    
    if (seq[1] % seq[0] != 0) return false;
    commonRatio = seq[1] / seq[0];
    
    for (int i = 2; i < seq.size(); i++) {
        if (seq[i-1] == 0 || seq[i] % seq[i-1] != 0 || seq[i] / seq[i-1] != commonRatio) {
            return false;
        }
    }
    
    return true;
}

// Kiểm tra dãy Fibonacci
bool isFibonacciSequence(const vector<int>& seq) {
    if (seq.size() < 3) return false;
    
    for (int i = 2; i < seq.size(); i++) {
        if (seq[i] != seq[i-1] + seq[i-2]) {
            return false;
        }
    }
    
    return true;
}

// Kiểm tra dãy số chính phương
bool isSquareSequence(const vector<int>& seq) {
    for (int i = 0; i < seq.size(); i++) {
        int root = (int)sqrt(seq[i]);
        if (root * root != seq[i]) {
            return false;
        }
        
        // Kiểm tra xem có phải là dãy 1², 2², 3², ... không
        if (i > 0) {
            int prevRoot = (int)sqrt(seq[i-1]);
            if (root != prevRoot + 1) {
                return false;
            }
        }
    }
    
    return true;
}

// Sinh k phần tử tiếp theo
vector<int> generateNext(const vector<int>& seq, int k) {
    vector<int> result;
    
    int commonDiff, commonRatio;
    
    // Kiểm tra cấp số cộng
    if (isArithmeticSequence(seq, commonDiff)) {
        int lastElement = seq.back();
        for (int i = 0; i < k; i++) {
            lastElement += commonDiff;
            result.push_back(lastElement);
        }
        return result;
    }
    
    // Kiểm tra cấp số nhân
    if (isGeometricSequence(seq, commonRatio)) {
        int lastElement = seq.back();
        for (int i = 0; i < k; i++) {
            lastElement *= commonRatio;
            result.push_back(lastElement);
        }
        return result;
    }
    
    // Kiểm tra Fibonacci
    if (isFibonacciSequence(seq)) {
        vector<int> fib = seq;
        for (int i = 0; i < k; i++) {
            int nextFib = fib[fib.size()-1] + fib[fib.size()-2];
            fib.push_back(nextFib);
            result.push_back(nextFib);
        }
        return result;
    }
    
    // Kiểm tra số chính phương
    if (isSquareSequence(seq)) {
        int lastRoot = (int)sqrt(seq.back());
        for (int i = 0; i < k; i++) {
            lastRoot++;
            result.push_back(lastRoot * lastRoot);
        }
        return result;
    }
    
    // Nếu không nhận dạng được pattern, trả về mảng rỗng
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> sequence(n);
    for (int i = 0; i < n; i++) {
        cin >> sequence[i];
    }
    
    vector<int> nextElements = generateNext(sequence, k);
    
    if (nextElements.empty()) {
        cout << "Pattern not recognized" << endl;
    } else {
        for (int i = 0; i < k; i++) {
            cout << nextElements[i];
            if (i < k - 1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}