# Đề Tài 5: Deque và Bài Toán Min/Max

## 1. Trình Bày Lý Thuyết

### 1.1 Giới Thiệu Về Deque

**Deque (Double-ended queue)** là một cấu trúc dữ liệu cho phép thêm và xóa phần tử ở cả hai đầu (đầu và cuối) với thời gian O(1). Deque kết hợp ưu điểm của cả stack và queue, rất hữu ích trong việc giải quyết các bài toán tối ưu hóa.

### 1.2 Đặc Điểm Của Deque

**Các thao tác cơ bản:**

- `push_front(x)`: Thêm phần tử x vào đầu deque - O(1)
- `push_back(x)`: Thêm phần tử x vào cuối deque - O(1)
- `pop_front()`: Xóa phần tử ở đầu deque - O(1)
- `pop_back()`: Xóa phần tử ở cuối deque - O(1)
- `front()`: Truy cập phần tử đầu - O(1)
- `back()`: Truy cập phần tử cuối - O(1)

**Ưu điểm:**

- Thao tác nhanh ở cả hai đầu
- Tiết kiệm bộ nhớ hơn so với việc duy trì hai stack
- Hỗ trợ tốt cho sliding window problems

### 1.3 Bài Toán Sliding Window Maximum/Minimum

**Định nghĩa:** Cho mảng A có n phần tử và số nguyên k. Tìm giá trị lớn nhất (hoặc nhỏ nhất) trong mỗi cửa sổ trượt có kích thước k.

**Ví dụ:**

```
Mảng: [1, 3, -1, -3, 5, 3, 6, 7]
k = 3
Sliding windows: [1,3,-1], [3,-1,-3], [-1,-3,5], [-3,5,3], [5,3,6], [3,6,7]
Maximum values:     3,        3,         5,        5,       6,      7
```

### 1.4 Thuật Toán Deque cho Sliding Window

**Ý tưởng chính:**

1. Duy trì một deque chứa các chỉ số của mảng
2. Deque luôn được sắp xếp theo thứ tự giảm dần (cho max) hoặc tăng dần (cho min)
3. Phần tử ở đầu deque luôn là chỉ số của phần tử max/min trong window hiện tại

**Thuật toán cho Sliding Window Maximum:**

```cpp
vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
    deque<int> dq; // Lưu chỉ số
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        // Xóa các chỉ số nằm ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Xóa các phần tử nhỏ hơn phần tử hiện tại
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Nếu đã đủ k phần tử, thêm kết quả
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}
```

### 1.5 Các Ứng Dụng Khác Của Deque

**1. Monotonic Deque:**

- Duy trì tính đơn điệu trong deque
- Ứng dụng trong bài toán tìm min/max trong khoảng

**2. Largest Rectangle in Histogram:**

- Sử dụng deque để tìm diện tích hình chữ nhật lớn nhất

**3. Shortest Subarray with Sum at Least K:**

- Kết hợp prefix sum và deque

**4. Constrained Subsequence Sum:**

- Dynamic programming với deque optimization

### 1.6 So Sánh Với Các Cấu Trúc Khác

| Cấu trúc | Thêm đầu | Thêm cuối | Xóa đầu | Xóa cuối | Truy cập |
| -------- | -------- | --------- | ------- | -------- | -------- |
| Array    | O(n)     | O(1)      | O(n)    | O(1)     | O(1)     |
| Vector   | O(n)     | O(1)      | O(n)    | O(1)     | O(1)     |
| List     | O(1)     | O(1)      | O(1)    | O(1)     | O(n)     |
| Deque    | O(1)     | O(1)      | O(1)    | O(1)     | O(1)     |

## 2. Bài Tập Thực Hành

### Bài 1: Sliding Window Maximum

**Đề bài**: Tìm giá trị lớn nhất trong mỗi cửa sổ trượt kích thước k

**Lời giải**:

```cpp
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
    deque<int> dq; // Lưu chỉ số
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        // Xóa các chỉ số nằm ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Duy trì tính giảm dần trong deque
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Thêm kết quả khi window đã đủ k phần tử
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<int> result = slidingWindowMaximum(nums, k);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
```

### Bài 2: Sliding Window Minimum

**Đề bài**: Tìm giá trị nhỏ nhất trong mỗi cửa sổ trượt kích thước k

**Lời giải**:

```cpp
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

vector<int> slidingWindowMinimum(vector<int>& nums, int k) {
    deque<int> dq; // Lưu chỉ số
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        // Xóa các chỉ số nằm ngoài window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Duy trì tính tăng dần trong deque (cho minimum)
        while (!dq.empty() && nums[dq.back()] >= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Thêm kết quả khi window đã đủ k phần tử
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<int> result = slidingWindowMinimum(nums, k);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
```

### Bài 3: Largest Rectangle in Histogram

**Đề bài**: Tìm diện tích hình chữ nhật lớn nhất trong histogram

**Lời giải**:

```cpp
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int largestRectangleArea(vector<int>& heights) {
    deque<int> stack; // Lưu chỉ số
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; i++) {
        int currentHeight = (i == n) ? 0 : heights[i];

        while (!stack.empty() && heights[stack.back()] > currentHeight) {
            int height = heights[stack.back()];
            stack.pop_back();

            int width = stack.empty() ? i : i - stack.back() - 1;
            maxArea = max(maxArea, height * width);
        }

        stack.push_back(i);
    }

    return maxArea;
}

int main() {
    int n;
    cin >> n;

    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    cout << largestRectangleArea(heights) << endl;

    return 0;
}
```

### Bài 4: Shortest Subarray with Sum at Least K

**Đề bài**: Tìm mảng con ngắn nhất có tổng ≥ K

**Lời giải**:

```cpp
#include <iostream>
#include <vector>
#include <deque>
#include <climits>
using namespace std;

int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefixSum(n + 1, 0);

    // Tính prefix sum
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    deque<int> dq; // Lưu chỉ số của prefix sum
    int minLength = INT_MAX;

    for (int i = 0; i <= n; i++) {
        // Kiểm tra xem có thể tạo subarray với sum >= k không
        while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= k) {
            minLength = min(minLength, i - dq.front());
            dq.pop_front();
        }

        // Duy trì tính tăng dần của prefix sum trong deque
        while (!dq.empty() && prefixSum[dq.back()] >= prefixSum[i]) {
            dq.pop_back();
        }

        dq.push_back(i);
    }

    return minLength == INT_MAX ? -1 : minLength;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << shortestSubarray(nums, k) << endl;

    return 0;
}
```

### Bài 5: Constrained Subsequence Sum

**Đề bài**: Tìm tổng lớn nhất của subsequence với ràng buộc khoảng cách

**Lời giải**:

```cpp
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int constrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> dq; // Lưu chỉ số

    int maxSum = nums[0];

    for (int i = 0; i < n; i++) {
        // Xóa các chỉ số nằm ngoài khoảng k
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }

        // dp[i] = max(nums[i], nums[i] + max(dp[j])) với j trong [i-k, i-1]
        dp[i] = nums[i];
        if (!dq.empty()) {
            dp[i] = max(dp[i], nums[i] + dp[dq.front()]);
        }

        maxSum = max(maxSum, dp[i]);

        // Duy trì tính giảm dần trong deque
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }

        if (dp[i] > 0) {
            dq.push_back(i);
        }
    }

    return maxSum;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << constrainedSubsetSum(nums, k) << endl;

    return 0;
}
```

## 3. Phân Tích Độ Phức Tạp

### 3.1 Sliding Window Problems

**Thời gian:** O(n) - Mỗi phần tử được thêm và xóa khỏi deque tối đa một lần
**Không gian:** O(k) - Deque chứa tối đa k phần tử

### 3.2 So Sánh Với Các Phương Pháp Khác

| Phương pháp  | Thời gian  | Không gian | Ưu điểm         | Nhược điểm      |
| ------------ | ---------- | ---------- | --------------- | --------------- |
| Brute Force  | O(nk)      | O(1)       | Đơn giản        | Chậm            |
| Segment Tree | O(n log k) | O(k)       | Tổng quát       | Phức tạp        |
| Deque        | O(n)       | O(k)       | Nhanh, đơn giản | Chỉ cho min/max |

## 4. Lưu Ý Quan Trọng

### 4.1 Khi Nào Sử Dụng Deque?

1. **Sliding Window Problems**: Tìm min/max trong cửa sổ trượt
2. **Monotonic Stack/Queue**: Cần duy trì tính đơn điệu
3. **Range Queries**: Truy vấn trên khoảng với ràng buộc
4. **Dynamic Programming Optimization**: Tối ưu hóa DP với deque

### 4.2 Các Lỗi Thường Gặp

1. **Quên kiểm tra deque rỗng** trước khi truy cập
2. **Nhầm lẫn giữa chỉ số và giá trị** trong deque
3. **Không xử lý đúng điều kiện biên** của sliding window
4. **Sai logic duy trì tính đơn điệu** trong deque

### 4.3 Mẹo Tối Ưu

1. **Sử dụng chỉ số thay vì giá trị** để tiết kiệm bộ nhớ
2. **Kiểm tra điều kiện trước khi thao tác** với deque
3. **Tận dụng tính chất LIFO/FIFO** của deque
4. **Kết hợp với các kỹ thuật khác** như prefix sum

## 5. Bài Tập Mở Rộng

### 5.1 Bài Tập Cơ Bản

1. Sliding Window Average
2. First Negative Integer in Window
3. Maximum of All Subarrays of Size K

### 5.2 Bài Tập Nâng Cao

1. Sliding Window Median
2. Maximum Sum Rectangle in 2D Array
3. Longest Subarray with Absolute Diff ≤ Limit

### 5.3 Bài Tập Thách Thức

1. Minimum Window Substring
2. Sliding Window Maximum with Updates
3. Range Minimum Query with Deque

## 6. Tài Liệu Tham Khảo

### 6.1 Sách và Tài Liệu

- "Introduction to Algorithms" - CLRS
- "Competitive Programming" - Steven Halim
- "Algorithm Design Manual" - Steven Skiena

### 6.2 Website Hữu Ích

- [LeetCode Sliding Window Problems](https://leetcode.com/tag/sliding-window/)
- [GeeksforGeeks Deque](https://www.geeksforgeeks.org/deque-set-1-introduction-applications/)
- [CP-Algorithms](https://cp-algorithms.com/)

---

**Tác giả**: [Tên nhóm]  
**Ngày hoàn thành**: [Ngày tháng năm]  
**Tham khảo**: VNOI Wiki, LeetCode, GeeksforGeeks
