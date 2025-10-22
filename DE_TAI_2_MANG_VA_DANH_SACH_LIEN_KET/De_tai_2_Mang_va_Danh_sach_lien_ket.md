# Đề Tài 2: Mảng và Danh Sách Liên Kết

## 1. Trình Bày Lý Thuyết

### 1.1 Biến và Con Trỏ

**Biến (Variable)** là cấu trúc dữ liệu đơn giản nhất, chỉ lưu trữ một giá trị duy nhất với phạm vi sử dụng có giới hạn.

**Con trỏ (Pointer)** là một biến đặc biệt lưu trữ địa chỉ vùng nhớ thay vì giá trị trực tiếp.

Ví dụ:
```cpp
int var = 50;        // Biến thông thường
int* ptr = &var;     // Con trỏ trỏ đến địa chỉ của var
```

### 1.2 Mảng (Arrays)

**Mảng** là cấu trúc dữ liệu lưu trữ nhiều phần tử cùng kiểu trong vùng nhớ liên tiếp.

**Đặc điểm:**
- Kích thước cố định, cần biết trước số phần tử
- Truy cập ngẫu nhiên với độ phức tạp O(1)
- Thêm/xóa phần tử có độ phức tạp O(N)

**Ví dụ:**
```cpp
int arr[100];           // Mảng tĩnh
vector<int> vec;        // Mảng động (STL)
```

### 1.3 Vector (Mảng Động)

**Vector** sử dụng kỹ thuật "nhân đôi mảng" để tối ưu hiệu suất:
- Truy cập phần tử: O(1)
- Thêm/xóa cuối mảng: O(1) trung bình
- Thêm/xóa vị trí bất kỳ: O(N)

### 1.4 Danh Sách Liên Kết (Linked Lists)

**Danh sách liên kết** là cấu trúc dữ liệu động, mỗi nút chứa dữ liệu và con trỏ đến nút tiếp theo.

**Cấu trúc:**
```cpp
struct ListNode {
    int data;
    ListNode* next;
};
```

**Đặc điểm:**
- Kích thước linh hoạt
- Thêm/xóa đầu/cuối: O(1)
- Truy cập phần tử: O(N)

## 2. Bài Tập Thực Hành

### Bài 1: Tìm Phần Tử Lớn Nhất Trong Mảng
**Đề bài**: Tìm giá trị lớn nhất trong mảng n số nguyên

**Lời giải**:
```cpp
#include <iostream>
#include <vector>
using namespace std;

int findMax(vector<int>& arr) {
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << findMax(arr) << endl;
    return 0;
}
```

**Giải thích**: Duyệt qua mảng và cập nhật giá trị lớn nhất

### Bài 2: Đảo Ngược Mảng
**Đề bài**: Đảo ngược thứ tự các phần tử trong mảng

**Lời giải**:
```cpp
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
```

**Giải thích**: Hoán đổi phần tử đầu với cuối, tiến dần vào giữa

### Bài 3: Tính Tổng Mảng Con
**Đề bài**: Tính tổng các phần tử từ vị trí l đến r trong mảng

**Lời giải**:
```cpp
#include <iostream>
#include <vector>
using namespace std;

long long rangeSum(vector<int>& arr, int l, int r) {
    long long sum = 0;
    for (int i = l; i <= r; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int n, l, r;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> l >> r;
    cout << rangeSum(arr, l, r) << endl;
    return 0;
}
```

**Giải thích**: Duyệt từ chỉ số l đến r và tính tổng

### Bài 4: Thêm Phần Tử Vào Danh Sách Liên Kết
**Đề bài**: Thêm phần tử vào đầu danh sách liên kết và in ra

**Lời giải**:
```cpp
#include <iostream>
using namespace std;

struct ListNode {
    int data;
    ListNode* next;
    ListNode(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    void addFirst(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
    }
    
    void printList() {
        ListNode* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;
    LinkedList list;
    
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        list.addFirst(val);
    }
    
    list.printList();
    return 0;
}
```

**Giải thích**: Tạo nút mới và liên kết với đầu danh sách

### Bài 5: Tìm Kiếm Trong Mảng
**Đề bài**: Tìm vị trí đầu tiên của phần tử x trong mảng

**Lời giải**:
```cpp
#include <iostream>
#include <vector>
using namespace std;

int linearSearch(vector<int>& arr, int x) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n, x;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> x;
    cout << linearSearch(arr, x) << endl;
    return 0;
}
```

**Giải thích**: Duyệt tuần tự mảng để tìm phần tử x## 3. B
ộ Test

### Bài 1: Tìm Phần Tử Lớn Nhất
- **Test 01**: Input: 5, [3,7,2,9,1], Output: 9

### Bài 2: Đảo Ngược Mảng  
- **Test 01**: Input: 4, [1,2,3,4], Output: 4 3 2 1

### Bài 3: Tổng Mảng Con
- **Test 01**: Input: 5, [1,2,3,4,5], l=1, r=3, Output: 9

### Bài 4: Thêm Vào Danh Sách Liên Kết
- **Test 01**: Input: 3, [1,2,3], Output: 3 2 1

### Bài 5: Tìm Kiếm Tuyến Tính
- **Test 01**: Input: 5, [10,20,30,20,40], x=20, Output: 1

## 4. 10 Bộ Test Bổ Sung

### Test 01: MAXARRAY - Tìm phần tử lớn nhất
### Test 02: REVERSE - Đảo ngược mảng
### Test 03: RANGESUM - Tổng mảng con
### Test 04: ADDLIST - Thêm vào danh sách liên kết
### Test 05: SEARCH - Tìm kiếm tuyến tính
### Test 06: MINARRAY - Tìm phần tử nhỏ nhất
### Test 07: SUMARRAY - Tổng mảng
### Test 08: COUNTEVEN - Đếm số chẵn
### Test 09: INSERTPOS - Chèn phần tử
### Test 10: FREQUENCY - Đếm tần suất

## 5. Cấu Trúc Thư Mục

```
De_tai_2_Mang_va_Danh_sach_lien_ket/
├── De_tai_2_Mang_va_Danh_sach_lien_ket.md
├── 10_Bo_Test_Mang_va_Danh_sach_lien_ket.md
├── Test_01_MAXARRAY/
│   ├── MAXARRAY.cpp
│   └── Test01/
│       ├── MAXARRAY.inp
│       └── MAXARRAY.out
├── Test_02_REVERSE/
│   ├── REVERSE.cpp
│   └── Test01/
│       ├── REVERSE.inp
│       └── REVERSE.out
├── ... (tương tự cho 8 test còn lại)
└── Test_10_FREQUENCY/
    ├── FREQUENCY.cpp
    └── Test01/
        ├── FREQUENCY.inp
        └── FREQUENCY.out
```

## 6. Hướng Dẫn Sử Dụng

### Biên Dịch và Chạy
```bash
# Biên dịch
g++ -o program_name source_file.cpp

# Chạy với input file
./program_name < input_file.inp

# Hoặc chạy trực tiếp
./program_name
```

### Kiểm Tra Kết Quả
So sánh output của chương trình với file `.out` tương ứng để kiểm tra tính đúng đắn.

---

**Tác giả**: [Tên nhóm]  
**Ngày hoàn thành**: [Ngày tháng năm]  
**Tham khảo**: VNOI Wiki - https://wiki.vnoi.info/