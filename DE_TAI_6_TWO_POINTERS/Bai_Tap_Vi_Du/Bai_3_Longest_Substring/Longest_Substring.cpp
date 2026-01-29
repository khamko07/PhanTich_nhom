#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

// Longest Substring Without Repeating Characters sử dụng Sliding Window
int lengthOfLongestSubstring(string s) {
    unordered_set<char> charSet;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        // Thu hẹp window từ bên trái cho đến khi không có ký tự trùng lặp
        while (charSet.count(s[right])) {
            charSet.erase(s[left]);
            left++;
        }
        
        // Thêm ký tự hiện tại vào window
        charSet.insert(s[right]);
        
        // Cập nhật độ dài lớn nhất
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

// Phương pháp brute force để so sánh
int lengthOfLongestSubstringBruteForce(string s) {
    int maxLen = 0;
    int n = s.length();
    
    for (int i = 0; i < n; i++) {
        unordered_set<char> seen;
        for (int j = i; j < n; j++) {
            if (seen.count(s[j])) {
                break;
            }
            seen.insert(s[j]);
            maxLen = max(maxLen, j - i + 1);
        }
    }
    
    return maxLen;
}

// Hàm debug để hiển thị quá trình sliding window
void debugLongestSubstring(string s) {
    unordered_set<char> charSet;
    int left = 0, maxLen = 0;
    
    cout << "=== DEBUG LONGEST SUBSTRING ===" << endl;
    cout << "String: " << s << endl << endl;
    
    for (int right = 0; right < s.length(); right++) {
        cout << "Step " << right + 1 << ": Processing s[" << right << "] = '" << s[right] << "'" << endl;
        
        // Thu hẹp window nếu có ký tự trùng lặp
        while (charSet.count(s[right])) {
            cout << "  Remove s[" << left << "] = '" << s[left] << "' from window" << endl;
            charSet.erase(s[left]);
            left++;
        }
        
        // Thêm ký tự hiện tại
        charSet.insert(s[right]);
        cout << "  Add '" << s[right] << "' to window" << endl;
        
        // Hiển thị window hiện tại
        cout << "  Current window: [" << left << ", " << right << "] = \"";
        for (int i = left; i <= right; i++) {
            cout << s[i];
        }
        cout << "\"" << endl;
        
        // Cập nhật độ dài
        int currentLen = right - left + 1;
        maxLen = max(maxLen, currentLen);
        cout << "  Window length: " << currentLen << ", Max length: " << maxLen << endl << endl;
    }
    
    cout << "Final result: " << maxLen << endl;
    cout << "==============================" << endl;
}

int main() {
    string s;
    cin >> s;
    
    int result = lengthOfLongestSubstring(s);
    cout << result << endl;
    
    // Uncomment để xem debug info:
    // debugLongestSubstring(s);
    
    // Uncomment để so sánh với brute force:
    // int bruteResult = lengthOfLongestSubstringBruteForce(s);
    // cout << "Brute force result: " << bruteResult << endl;
    // cout << "Results match: " << (result == bruteResult ? "YES" : "NO") << endl;
    
    return 0;
}