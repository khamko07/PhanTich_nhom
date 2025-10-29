# Đề Tài 6: Kỹ Thuật Two Pointers

## 1. Trình Bày Lý Thuyết

### 1.1 Giới Thiệu Về Two Pointers

**Two Pointers** là một kỹ thuật thuật toán sử dụng hai con trỏ để duyệt qua cấu trúc dữ liệu (thường là mảng hoặc chuỗi) một cách hiệu quả. Kỹ thuật này giúp giảm độ phức tạp thời gian từ O(n²) xuống O(n) trong nhiều bài toán.

### 1.2 Các Dạng Two Pointers Cơ Bản

**1. Two Pointers cùng chiều (Same Direction):**
- Hai con trỏ di chuyển cùng chiều từ trái sang phải
- Thường dùng cho sliding window, subarray problems

**2. Two Pointers ngược chiều (Opposite Direction):**
- Một con trỏ từ đầu, một con trỏ từ cuối
- Thường dùng cho bài toán tìm cặp, palindrome

**3. Fast & Slow Pointers:**
- Một con trỏ di chuyển nhanh, một con trỏ di chuyển chậm
- Thường dùng cho linked list, cycle detection

### 1.3 Ứng Dụng Phổ Biến

- Tìm cặp số có tổng bằng target
- Sliding window maximum/minimum
- Longest substring without repeating characters
- Container with most water
- Remove duplicates from sorted array

### 1.4 Ví Dụ Cơ Bản - Two Sum

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {-1, -1};
}
```
## 
2. Các Kỹ Thuật Two Pointers Chi Tiết

### 2.1 Sliding Window Technique

**Định nghĩa:** Sử dụng hai con trỏ để duy trì một "cửa sổ" có kích thước thay đổi hoặc cố định.

**Template cơ bản:**
```cpp
int left = 0, right = 0;
while (right < n) {
    // Mở rộng window bằng cách thêm nums[right]
    // Cập nhật trạng thái window
    
    while (/* điều kiện thu hẹp window */) {
        // Thu hẹp window bằng cách loại bỏ nums[left]
        left++;
    }
    
    // Cập nhật kết quả
    right++;
}
```

### 2.2 Two Pointers trên Mảng Đã Sắp Xếp

**Ứng dụng:** Tìm cặp phần tử thỏa mãn điều kiện nào đó.

```cpp
// Tìm cặp có tổng = target
pair<int,int> findPair(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return {left, right};
        else if (sum < target) left++;
        else right--;
    }
    
    return {-1, -1};
}
```

### 2.3 Fast & Slow Pointers (Floyd's Algorithm)

**Ứng dụng:** Phát hiện cycle trong linked list.

```cpp
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) return true;
    }
    
    return false;
}
```

## 3. Bài Tập Thực Hành

### Bài 1: Two Sum trên Mảng Đã Sắp Xếp
**Đề bài**: Tìm hai số trong mảng đã sắp xếp có tổng bằng target.

```cpp
#include <iostream>
#include <vector>
using namespace std;

pair<int, int> twoSum(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {-1, -1};
}

int main() {
    int n, target;
    cin >> n >> target;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    auto result = twoSum(nums, target);
    cout << result.first << " " << result.second << endl;
    
    return 0;
}
```### Bài
 2: Container With Most Water
**Đề bài**: Tìm hai đường thẳng tạo thành container chứa nhiều nước nhất.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        int width = right - left;
        int currentArea = min(height[left], height[right]) * width;
        maxWater = max(maxWater, currentArea);
        
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxWater;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> height(n);
    for (int i = 0; i < n; i++) {
        cin >> height[i];
    }
    
    cout << maxArea(height) << endl;
    
    return 0;
}
```

### Bài 3: Longest Substring Without Repeating Characters
**Đề bài**: Tìm độ dài chuỗi con dài nhất không có ký tự lặp lại.

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_set<char> charSet;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        while (charSet.count(s[right])) {
            charSet.erase(s[left]);
            left++;
        }
        
        charSet.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

int main() {
    string s;
    cin >> s;
    
    cout << lengthOfLongestSubstring(s) << endl;
    
    return 0;
}
```##
# Bài 4: Remove Duplicates from Sorted Array
**Đề bài**: Xóa các phần tử trùng lặp trong mảng đã sắp xếp.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 0;
    
    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    
    return slow + 1;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int newLength = removeDuplicates(nums);
    
    for (int i = 0; i < newLength; i++) {
        cout << nums[i];
        if (i < newLength - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Bài 5: Subarray Sum Equals K
**Đề bài**: Đếm số lượng subarray có tổng bằng k.

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;
    
    int prefixSum = 0, count = 0;
    
    for (int num : nums) {
        prefixSum += num;
        
        if (prefixSumCount.count(prefixSum - k)) {
            count += prefixSumCount[prefixSum - k];
        }
        
        prefixSumCount[prefixSum]++;
    }
    
    return count;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    cout << subarraySum(nums, k) << endl;
    
    return 0;
}
```## 4
. Phân Tích Độ Phức Tạp

### 4.1 So Sánh Độ Phức Tạp

| Bài toán | Brute Force | Two Pointers | Cải thiện |
|----------|-------------|--------------|-----------|
| Two Sum | O(n²) | O(n) | n lần |
| Container Water | O(n²) | O(n) | n lần |
| Longest Substring | O(n³) | O(n) | n² lần |
| Remove Duplicates | O(n²) | O(n) | n lần |

### 4.2 Điều Kiện Áp Dụng Two Pointers

1. **Mảng/chuỗi đã sắp xếp** hoặc có thể sắp xếp
2. **Tính chất monotonic**: khi di chuyển một pointer, điều kiện thay đổi theo một hướng
3. **Sliding window**: cần duy trì một khoảng liên tục
4. **Linked list**: cần duyệt với tốc độ khác nhau

## 5. Các Lỗi Thường Gặp

### 5.1 Lỗi Về Chỉ Số
- Không kiểm tra điều kiện biên `left < right`
- Quên cập nhật pointer sau khi xử lý
- Truy cập ngoài phạm vi mảng

### 5.2 Lỗi Logic
- Không hiểu rõ khi nào di chuyển pointer nào
- Không xử lý đúng trường hợp đặc biệt
- Nhầm lẫn giữa các dạng two pointers

### 5.3 Cách Debug
```cpp
// Thêm debug info
cout << "left=" << left << ", right=" << right 
     << ", sum=" << (nums[left] + nums[right]) << endl;
```

## 6. Mẹo và Kỹ Thuật Nâng Cao

### 6.1 Template Sliding Window
```cpp
int slidingWindow(vector<int>& nums, int condition) {
    int left = 0, result = 0;
    // Khởi tạo trạng thái window
    
    for (int right = 0; right < nums.size(); right++) {
        // Thêm nums[right] vào window
        
        while (/* window không hợp lệ */) {
            // Loại bỏ nums[left] khỏi window
            left++;
        }
        
        // Cập nhật kết quả
        result = max(result, right - left + 1);
    }
    
    return result;
}
```

### 6.2 Three Pointers
Mở rộng cho bài toán 3Sum:
```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    
    for (int i = 0; i < nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left+1]) left++;
                while (left < right && nums[right] == nums[right-1]) right--;
                left++; right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}
```## 7. 
Bài Tập Nâng Cao

### 7.1 Minimum Window Substring
Tìm chuỗi con nhỏ nhất chứa tất cả ký tự của pattern.

### 7.2 Trapping Rain Water
Tính lượng nước mưa có thể chứa được.

### 7.3 Palindromic Substrings
Đếm số lượng chuỗi con palindrome.

### 7.4 Sliding Window Maximum
Tìm maximum trong mỗi sliding window (kết hợp với deque).

## 8. Tài Liệu Tham Khảo

### 8.1 Sách và Tài Liệu
- "Cracking the Coding Interview" - Gayle McDowell
- "Elements of Programming Interviews" - Aziz, Lee, Prakash
- "Algorithm Design Manual" - Steven Skiena

### 8.2 Website Hữu Ích
- [VNOI Wiki - Two Pointers](https://wiki.vnoi.info/algo/basic/two-pointers)
- [LeetCode Two Pointers Problems](https://leetcode.com/tag/two-pointers/)
- [GeeksforGeeks Two Pointer Technique](https://www.geeksforgeeks.org/two-pointers-technique/)

### 8.3 Bài Tập Luyện Tập
- LeetCode: 1, 11, 15, 16, 18, 26, 27, 42, 75, 76, 125, 167, 209, 283, 344, 345, 349, 350, 392, 524, 532, 567, 713, 719, 763, 844, 845, 904, 925, 977, 986

## 9. Lưu Ý Quan Trọng

### 9.1 Khi Nào Sử Dụng Two Pointers?
1. **Bài toán trên mảng đã sắp xếp** cần tìm cặp/bộ ba
2. **Sliding window problems** với điều kiện động
3. **Linked list problems** cần phát hiện cycle
4. **String problems** cần kiểm tra palindrome

### 9.2 Các Biến Thể Phổ Biến
- **Same direction**: Cả hai pointer di chuyển cùng chiều
- **Opposite direction**: Hai pointer di chuyển ngược chiều
- **Fast & Slow**: Một nhanh một chậm
- **Multiple pointers**: Sử dụng 3+ pointers

### 9.3 Tối Ưu Hóa
- Sử dụng early termination khi có thể
- Kết hợp với hash table để tăng hiệu quả
- Xử lý duplicate elements cẩn thận
- Chú ý đến overflow khi tính tổng

---

**Tác giả**: [Tên nhóm]  
**Ngày hoàn thành**: [Ngày tháng năm]  
**Tham khảo**: VNOI Wiki - Two Pointers, LeetCode, GeeksforGeeks