# Đề Tài 1: Đệ Quy và Thuật Toán Quay Lui

## 1. Trình Bày Lý Thuyết

### 1.1 Khái Niệm Đệ Quy

**Đệ quy** (Recursion) là một phương pháp giải quyết vấn đề bằng cách chia nhỏ vấn đề thành các vấn đề con tương tự nhưng đơn giản hơn.

Một hàm đệ quy bao gồm hai phần chính:

- **Trường hợp cơ sở (Base case)**: Điều kiện dừng của đệ quy
- **Trường hợp đệ quy (Recursive case)**: Hàm gọi chính nó với tham số khác

### 1.2 Thuật Toán Quay Lui

**Thuật toán quay lui** (Backtracking) là một kỹ thuật tìm kiếm có hệ thống để giải quyết các bài toán tổ hợp. Nó xây dựng lời giải từng bước và loại bỏ những lời giải không khả thi.

Cấu trúc chung:

```
void backtrack(trạng_thái_hiện_tại) {
    if (đạt_được_lời_giải) {
        xử_lý_lời_giải();
        return;
    }

    for (mỗi_lựa_chọn_có_thể) {
        thực_hiện_lựa_chọn();
        backtrack(trạng_thái_mới);
        hoàn_tác_lựa_chọn(); // Quay lui
    }
}
```

### 1.3 Ứng Dụng

- Tính toán các hàm số học (giai thừa, Fibonacci)
- Sinh các tổ hợp, hoán vị
- Giải các bài toán tối ưu (N-Queens, Sudoku)
- Duyệt cây và đồ thị

## 2. Bài Tập Thực Hành

### Bài 1: Tính Giai Thừa

**Đề bài**: Tính n! với n ≥ 0

**Lời giải**:

```cpp
#include <iostream>
using namespace std;

long long factorial(int n) {
    // Trường hợp cơ sở
    if (n == 0 || n == 1) {
        return 1;
    }
    // Trường hợp đệ quy
    return n * factorial(n - 1);
}

int main() {
    int n;
    cin >> n;
    cout << factorial(n) << endl;
    return 0;
}
```

**Giải thích**:

- Base case: 0! = 1, 1! = 1
- Recursive case: n! = n × (n-1)!

### Bài 2: Dãy Fibonacci

**Đề bài**: Tính số Fibonacci thứ n

**Lời giải**:

```cpp
#include <iostream>
using namespace std;

long long fibonacci(int n) {
    // Trường hợp cơ sở
    if (n <= 1) {
        return n;
    }
    // Trường hợp đệ quy
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    cin >> n;
    cout << fibonacci(n) << endl;
    return 0;
}
```

**Giải thích**:

- Base case: F(0) = 0, F(1) = 1
- Recursive case: F(n) = F(n-1) + F(n-2)

### Bài 3: Tổng Các Chữ Số

**Đề bài**: Tính tổng các chữ số của số nguyên dương n

**Lời giải**:

```cpp
#include <iostream>
using namespace std;

int sum_digits(int n) {
    // Trường hợp cơ sở
    if (n < 10) {
        return n;
    }
    // Trường hợp đệ quy
    return n % 10 + sum_digits(n / 10);
}

int main() {
    int n;
    cin >> n;
    cout << sum_digits(n) << endl;
    return 0;
}
```

**Giải thích**:

- Base case: Nếu n < 10, tổng chính là n
- Recursive case: Tổng = chữ số cuối + tổng các chữ số còn lại

### Bài 4: Sinh Dãy Nhị Phân

**Đề bài**: In tất cả dãy nhị phân độ dài n

**Lời giải**:

```cpp
#include <iostream>
#include <string>
using namespace std;

void generate_binary(int n, string current = "") {
    // Trường hợp cơ sở
    if (current.length() == n) {
        cout << current << endl;
        return;
    }

    // Thử thêm '0'
    generate_binary(n, current + "0");
    // Thử thêm '1'
    generate_binary(n, current + "1");
}

int main() {
    int n;
    cin >> n;
    generate_binary(n);
    return 0;
}
```

**Giải thích**:

- Base case: Khi độ dài dãy = n, in kết quả
- Recursive case: Thử thêm '0' và '1' vào dãy hiện tại

### Bài 5: Bài Toán N-Queens (Đơn Giản)

**Đề bài**: Đếm số cách xếp n quân hậu trên bàn cờ n×n sao cho không ăn nhau

**Lời giải**:

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool is_safe(vector<int>& board, int row, int col, int n) {
    // Kiểm tra cột
    for (int i = 0; i < row; i++) {
        if (board[i] == col) {
            return false;
        }
    }

    // Kiểm tra đường chéo
    for (int i = 0; i < row; i++) {
        if (abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }

    return true;
}

int solve_nqueens(vector<int>& board, int row, int n) {
    // Trường hợp cơ sở
    if (row == n) {
        return 1;
    }

    int count = 0;
    for (int col = 0; col < n; col++) {
        if (is_safe(board, row, col, n)) {
            board[row] = col;
            count += solve_nqueens(board, row + 1, n);
        }
    }

    return count;
}

int main() {
    int n;
    cin >> n;
    vector<int> board(n, -1);
    cout << solve_nqueens(board, 0, n) << endl;
    return 0;
}
```

**Giải thích**:

- Base case: Khi đã xếp đủ n quân hậu
- Recursive case: Thử xếp quân hậu ở mỗi cột của hàng hiện tại

## 3. Bộ Test

### Bài 1: Tính Giai Thừa

- **Test 01**: Input: 5, Output: 120
- **Test 02**: Input: 0, Output: 1

### Bài 2: Dãy Fibonacci

- **Test 01**: Input: 7, Output: 13
- **Test 02**: Input: 10, Output: 55

### Bài 3: Tổng Các Chữ Số

- **Test 01**: Input: 123, Output: 6
- **Test 02**: Input: 9876, Output: 30

### Bài 4: Sinh Dãy Nhị Phân

- **Test 01**: Input: 2, Output: 00, 01, 10, 11
- **Test 02**: Input: 3, Output: 000, 001, 010, 011, 100, 101, 110, 111

### Bài 5: Bài Toán N-Queens

- **Test 01**: Input: 4, Output: 2
- **Test 02**: Input: 8, Output: 92

## 4. Cấu Trúc Thư Mục

```
De_tai_1_De_quy_va_Thuat_toan_quay_lui/
├── De_tai_1_De_quy_va_Thuat_toan_quay_lui.md
├── Bai_1_Giai_thua/
│   ├── Giai_thua.cpp
│   ├── Test01/
│   │   ├── Giai_thua.inp
│   │   └── Giai_thua.out
│   └── Test02/
│       ├── Giai_thua.inp
│       └── Giai_thua.out
├── Bai_2_Fibonacci/
│   ├── Fibonacci.cpp
│   ├── Test01/
│   │   ├── Fibonacci.inp
│   │   └── Fibonacci.out
│   └── Test02/
│       ├── Fibonacci.inp
│       └── Fibonacci.out
├── Bai_3_Tong_chu_so/
│   ├── Tong_chu_so.cpp
│   ├── Test01/
│   │   ├── Tong_chu_so.inp
│   │   └── Tong_chu_so.out
│   └── Test02/
│       ├── Tong_chu_so.inp
│       └── Tong_chu_so.out
├── Bai_4_Sinh_day_nhi_phan/
│   ├── Sinh_day_nhi_phan.cpp
│   ├── Test01/
│   │   ├── Sinh_day_nhi_phan.inp
│   │   └── Sinh_day_nhi_phan.out
│   └── Test02/
│       ├── Sinh_day_nhi_phan.inp
│       └── Sinh_day_nhi_phan.out
└── Bai_5_N_Queens/
    ├── N_Queens.cpp
    ├── Test01/
    │   ├── N_Queens.inp
    │   └── N_Queens.out
    └── Test02/
        ├── N_Queens.inp
        └── N_Queens.out
```

## 5. Hướng Dẫn Sử Dụng

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
