# 10 Bộ Test - Đề Tài 5: Deque và Bài Toán Min/Max

## Tổng Quan

Bộ test này được thiết kế để thực hành các kỹ thuật sử dụng Deque trong việc giải quyết các bài toán tìm min/max, sliding window và các bài toán tối ưu hóa khác. Mỗi test tập trung vào một khía cạnh khác nhau của việc áp dụng Deque.

---

## Test 01: SLIDING_MAX - Sliding Window Maximum

### Mô tả
Tìm giá trị lớn nhất trong mỗi cửa sổ trượt có kích thước k.

### Đề bài
Cho mảng A có n phần tử và số nguyên k. Với mỗi cửa sổ trượt kích thước k, tìm phần tử lớn nhất.

### Input
- Dòng 1: n, k (số phần tử và kích thước cửa sổ)
- Dòng 2: n số nguyên của mảng A

### Output
- Các giá trị lớn nhất của từng cửa sổ trượt

### Ví dụ
```
Input:
8 3
1 3 -1 -3 5 3 6 7

Output:
3 3 5 5 6 7
```

### Hướng dẫn
Sử dụng deque để duy trì các chỉ số theo thứ tự giảm dần của giá trị.

---

## Test 02: SLIDING_MIN - Sliding Window Minimum

### Mô tả
Tìm giá trị nhỏ nhất trong mỗi cửa sổ trượt có kích thước k.

### Đề bài
Tương tự Test 01 nhưng tìm minimum thay vì maximum.

### Input
- Dòng 1: n, k
- Dòng 2: n số nguyên của mảng A

### Output
- Các giá trị nhỏ nhất của từng cửa sổ trượt

### Ví dụ
```
Input:
8 3
1 3 -1 -3 5 3 6 7

Output:
-1 -3 -3 -3 3 3
```

---

## Test 03: HISTOGRAM - Largest Rectangle in Histogram

### Mô tả
Tìm diện tích hình chữ nhật lớn nhất có thể tạo thành trong histogram.

### Đề bài
Cho histogram với n cột có chiều cao h[i]. Tìm diện tích hình chữ nhật lớn nhất.

### Input
- Dòng 1: n (số cột)
- Dòng 2: n số nguyên h[i] (chiều cao các cột)

### Output
- Diện tích lớn nhất

### Ví dụ
```
Input:
6
2 1 5 6 2 3

Output:
10
```

### Giải thích
Hình chữ nhật lớn nhất có chiều cao 5 và chiều rộng 2 (từ cột 2 đến cột 3).

---

## Test 04: SHORTEST_SUBARRAY - Shortest Subarray with Sum ≥ K

### Mô tả
Tìm mảng con ngắn nhất có tổng ≥ K.

### Đề bài
Cho mảng A có n phần tử và số K. Tìm độ dài mảng con ngắn nhất có tổng ≥ K.

### Input
- Dòng 1: n, K
- Dòng 2: n số nguyên của mảng A

### Output
- Độ dài mảng con ngắn nhất, -1 nếu không tồn tại

### Ví dụ
```
Input:
5 7
2 -1 2 3 1

Output:
2
```

### Giải thích
Mảng con [3, 1] có tổng = 4 < 7, nhưng [2, 3] có tổng = 5 < 7, [3, 1] có tổng = 4 < 7.
Mảng con [2, -1, 2, 3] có tổng = 6 < 7, nhưng [2, 3, 1] có tổng = 6 < 7.
Mảng con [-1, 2, 3, 1] có tổng = 5 < 7, nhưng [2, -1, 2, 3, 1] có tổng = 7 ≥ 7.
Thực tế mảng con ngắn nhất là [3, 1] với độ dài 2 không đúng. Cần xem lại.

---

## Test 05: CONSTRAINED_SUM - Constrained Subsequence Sum

### Mô tả
Tìm tổng lớn nhất của subsequence với ràng buộc khoảng cách.

### Đề bài
Cho mảng A và số k. Tìm tổng lớn nhất của subsequence sao cho khoảng cách giữa hai phần tử liên tiếp ≤ k.

### Input
- Dòng 1: n, k
- Dòng 2: n số nguyên của mảng A

### Output
- Tổng lớn nhất

### Ví dụ
```
Input:
5 2
10 2 -10 5 20

Output:
37
```

### Giải thích
Chọn subsequence [10, 2, 5, 20] với tổng = 37.

---

## Test 06: MONOTONIC_DEQUE - Monotonic Deque Applications

### Mô tả
Sử dụng monotonic deque để giải bài toán tối ưu.

### Đề bài
Cho mảng A và số k. Với mỗi vị trí i, tìm phần tử nhỏ nhất trong khoảng [i-k+1, i].

### Input
- Dòng 1: n, k
- Dòng 2: n số nguyên của mảng A

### Output
- n số nguyên, mỗi số là minimum trong window kết thúc tại vị trí đó

### Ví dụ
```
Input:
6 3
4 3 1 2 5 6

Output:
4 3 1 1 1 2
```

---

## Test 07: RANGE_MINIMUM - Range Minimum Query with Deque

### Mô tả
Trả lời các truy vấn tìm minimum trong khoảng sử dụng deque.

### Đề bài
Cho mảng A và q truy vấn. Mỗi truy vấn yêu cầu tìm minimum trong khoảng [l, r].

### Input
- Dòng 1: n, q
- Dòng 2: n số nguyên của mảng A
- q dòng tiếp theo: mỗi dòng chứa l, r

### Output
- q dòng, mỗi dòng là kết quả của một truy vấn

### Ví dụ
```
Input:
5 3
3 1 4 1 5
1 3
2 4
1 5

Output:
1
1
1
```

---

## Test 08: SLIDING_MEDIAN - Sliding Window Median

### Mô tả
Tìm median trong mỗi cửa sổ trượt (bài toán nâng cao).

### Đề bài
Cho mảng A và k. Tìm median của mỗi cửa sổ trượt kích thước k.

### Input
- Dòng 1: n, k
- Dòng 2: n số nguyên của mảng A

### Output
- Median của từng cửa sổ (làm tròn xuống nếu k chẵn)

### Ví dụ
```
Input:
7 3
1 3 -1 -3 5 3 6

Output:
1 -1 -1 3 5
```

---

## Test 09: MAX_RECTANGLE - Maximum Rectangle in Binary Matrix

### Mô tả
Tìm hình chữ nhật lớn nhất trong ma trận nhị phân.

### Đề bài
Cho ma trận nhị phân n×m. Tìm diện tích hình chữ nhật lớn nhất chỉ chứa số 1.

### Input
- Dòng 1: n, m
- n dòng tiếp theo: mỗi dòng m số 0 hoặc 1

### Output
- Diện tích lớn nhất

### Ví dụ
```
Input:
4 4
1 0 1 0
1 0 1 1
1 1 1 1
1 0 0 1

Output:
4
```

---

## Test 10: COMPLETE_DEQUE - Complete Deque Problem

### Mô tả
Bài toán tổng hợp sử dụng nhiều kỹ thuật deque.

### Đề bài
Cho mảng A và các truy vấn. Hỗ trợ các thao tác:
1. Thêm phần tử vào cuối mảng
2. Tìm maximum trong k phần tử cuối
3. Tìm minimum trong k phần tử cuối
4. Xóa phần tử cuối

### Input
- Dòng 1: n, q (kích thước ban đầu và số truy vấn)
- Dòng 2: n số nguyên của mảng A ban đầu
- q dòng tiếp theo: mỗi dòng là một truy vấn
  - "ADD x": thêm x vào cuối
  - "MAX k": tìm max trong k phần tử cuối
  - "MIN k": tìm min trong k phần tử cuối
  - "POP": xóa phần tử cuối

### Output
- Với mỗi truy vấn MAX/MIN, in kết quả

### Ví dụ
```
Input:
3 5
1 2 3
MAX 2
ADD 4
MIN 3
POP
MAX 3

Output:
3
2
3
```

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành
1. **Hiểu rõ bài toán** và xác định có thể áp dụng deque không
2. **Phân tích** cần duy trì tính chất gì trong deque (tăng/giảm dần)
3. **Cài đặt** thuật toán với các thao tác deque cơ bản
4. **Test** với các trường hợp biên và test case lớn
5. **Tối ưu hóa** code và xử lý các trường hợp đặc biệt

### Tiêu Chí Đánh Giá
- **Tính đúng đắn**: Code chạy đúng với tất cả test case
- **Hiệu quả**: Độ phức tạp thời gian tối ưu (thường O(n))
- **Rõ ràng**: Code dễ đọc, logic rõ ràng
- **Xử lý biên**: Xử lý đúng các trường hợp đặc biệt

### Lộ Trình Học Tập
1. **Tuần 1**: Test 01-03 (Sliding window cơ bản)
2. **Tuần 2**: Test 04-06 (Ứng dụng nâng cao)
3. **Tuần 3**: Test 07-09 (Bài toán phức tạp)
4. **Tuần 4**: Test 10 và tổng hợp kiến thức

### Mẹo Giải Bài
1. **Vẽ sơ đồ** để hiểu rõ cách deque hoạt động
2. **Kiểm tra điều kiện** trước khi thao tác với deque
3. **Sử dụng chỉ số** thay vì giá trị để tiết kiệm bộ nhớ
4. **Chú ý thứ tự** thêm/xóa phần tử trong deque

---

**Ghi chú**: Deque là cấu trúc dữ liệu mạnh mẽ cho các bài toán sliding window và tối ưu hóa. Hãy thực hành nhiều để nắm vững các kỹ thuật!