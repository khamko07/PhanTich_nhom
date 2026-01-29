# 10 Bộ Test - Đề Tài 8: Greedy is Good

## Tổng Quan

Bộ test này được thiết kế để thực hành các thuật toán tham lam nâng cao và kỹ thuật chứng minh tính đúng đắn. Mỗi test tập trung vào một khía cạnh khác nhau của việc thiết kế và phân tích thuật toán greedy.

---

## Test 01: ACTIVITY_SELECTION - Activity Selection Problem

### Mô tả

Chọn tối đa số hoạt động không trùng thời gian sử dụng thuật toán greedy.

### Đề bài

Cho n hoạt động với thời gian bắt đầu và kết thúc. Chọn tối đa số hoạt động sao cho không có hai hoạt động nào trùng thời gian.

### Input

- Dòng 1: n (số hoạt động)
- n dòng tiếp theo: mỗi dòng chứa start_i, finish_i

### Output

- Dòng 1: số lượng hoạt động tối đa có thể chọn
- Dòng 2: chỉ số các hoạt động được chọn (0-indexed)

### Ví dụ

```
Input:
6
1 4
3 5
0 6
5 7
3 9
5 9

Output:
4
0 1 3 4
```

### Hướng dẫn

Sắp xếp các hoạt động theo thời gian kết thúc tăng dần, sau đó chọn greedy.

---

## Test 02: FRACTIONAL_KNAPSACK - Fractional Knapsack Problem

### Mô tả

Tối đa hóa giá trị trong cái túi khi có thể chia nhỏ vật phẩm.

### Đề bài

Cho n vật phẩm với giá trị và trọng lượng, và cái túi có sức chứa W. Tối đa hóa tổng giá trị.

### Input

- Dòng 1: n, W (số vật phẩm và sức chứa)
- n dòng tiếp theo: mỗi dòng chứa value_i, weight_i

### Output

- Tổng giá trị lớn nhất (làm tròn xuống)

### Ví dụ

```
Input:
3 50
60 10
100 20
120 30

Output:
240
```

### Giải thích

Chọn toàn bộ vật 1 (ratio=6), toàn bộ vật 2 (ratio=5), và 2/3 vật 3 (ratio=4).

---

## Test 03: JOB_SCHEDULING - Job Scheduling Problem

### Mô tả

Sắp xếp công việc để tối thiểu hóa tổng thời gian chờ.

### Đề bài

Cho n công việc với thời gian thực hiện. Sắp xếp để tối thiểu hóa tổng thời gian chờ.

### Input

- Dòng 1: n (số công việc)
- Dòng 2: n số nguyên biểu diễn thời gian thực hiện

### Output

- Tổng thời gian chờ tối thiểu

### Ví dụ

```
Input:
4
3 1 4 2

Output:
10
```

### Giải thích

Thứ tự tối ưu: 1, 2, 3, 4 với thời gian chờ: 0 + 1 + 3 + 6 = 10.

---

## Test 04: HUFFMAN_CODING - Huffman Coding

### Mô tả

Tạo mã Huffman tối ưu cho tập ký tự với tần suất cho trước.

### Đề bài

Cho n ký tự với tần suất xuất hiện. Tạo mã Huffman và tính độ dài trung bình.

### Input

- Dòng 1: n (số ký tự)
- n dòng tiếp theo: mỗi dòng chứa ký tự và tần suất

### Output

- n dòng: mỗi dòng chứa ký tự và mã Huffman tương ứng
- Dòng cuối: độ dài trung bình (làm tròn 2 chữ số thập phân)

### Ví dụ

```
Input:
4
a 5
b 9
c 12
d 13

Output:
a: 100
b: 101
c: 11
d: 0
2.05
```

---

## Test 05: MINIMUM_SPANNING_TREE - Kruskal's Algorithm

### Mô tả

Tìm cây khung nhỏ nhất của đồ thị có trọng số sử dụng thuật toán Kruskal.

### Đề bài

Cho đồ thị vô hướng có trọng số. Tìm cây khung có tổng trọng số nhỏ nhất.

### Input

- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v, w (cạnh từ u đến v với trọng số w)

### Output

- Dòng 1: tổng trọng số của MST
- n-1 dòng tiếp theo: các cạnh trong MST

### Ví dụ

```
Input:
4 5
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Output:
19
2 3 4
0 3 5
0 1 10
```

---

## Test 06: DIJKSTRA_SHORTEST_PATH - Dijkstra's Algorithm

### Mô tả

Tìm đường đi ngắn nhất từ một đỉnh đến tất cả các đỉnh khác.

### Đề bài

Cho đồ thị có hướng với trọng số không âm. Tìm đường đi ngắn nhất từ đỉnh nguồn.

### Input

- Dòng 1: n, m, start (số đỉnh, số cạnh, đỉnh nguồn)
- m dòng tiếp theo: mỗi dòng chứa u, v, w

### Output

- n số nguyên: khoảng cách ngắn nhất từ start đến mỗi đỉnh

### Ví dụ

```
Input:
5 8 0
0 1 4
0 2 2
1 2 1
1 3 5
2 3 8
2 4 10
3 4 2
4 3 3

Output:
0 3 2 7 9
```

---

## Test 07: INTERVAL_PARTITIONING - Interval Partitioning

### Mô tả

Phân chia các khoảng thời gian vào số lượng tài nguyên tối thiểu.

### Đề bài

Cho n khoảng thời gian. Tìm số lượng tài nguyên tối thiểu để tất cả khoảng đều được phục vụ.

### Input

- Dòng 1: n (số khoảng thời gian)
- n dòng tiếp theo: mỗi dòng chứa start_i, finish_i

### Output

- Số lượng tài nguyên tối thiểu cần thiết

### Ví dụ

```
Input:
4
1 3
2 4
3 5
1 2

Output:
2
```

### Giải thích

Cần 2 tài nguyên: một cho [1,3] và [3,5], một cho [2,4] và [1,2].

---

## Test 08: MINIMIZING_LATENESS - Minimizing Maximum Lateness

### Mô tả

Sắp xếp công việc để tối thiểu hóa độ trễ tối đa.

### Đề bài

Cho n công việc với thời gian thực hiện và deadline. Sắp xếp để tối thiểu hóa độ trễ tối đa.

### Input

- Dòng 1: n (số công việc)
- n dòng tiếp theo: mỗi dòng chứa duration_i, deadline_i

### Output

- Độ trễ tối đa nhỏ nhất có thể đạt được

### Ví dụ

```
Input:
3
3 6
2 8
1 9

Output:
1
```

### Giải thích

Thứ tự tối ưu theo deadline: job1(3,6), job2(2,8), job3(1,9) với lateness = max(0,0,1) = 1.

---

## Test 09: SET_COVER - Greedy Set Cover

### Mô tả

Tìm số lượng tập con tối thiểu để phủ tất cả các phần tử.

### Đề bài

Cho universe U và collection S của các tập con. Tìm số lượng tập con tối thiểu để phủ U.

### Input

- Dòng 1: n, m (kích thước universe và số tập con)
- Dòng 2: n phần tử của universe
- m dòng tiếp theo: mỗi dòng mô tả một tập con

### Output

- Số lượng tập con tối thiểu cần chọn

### Ví dụ

```
Input:
5 3
1 2 3 4 5
3 1 2 3
2 3 4
2 4 5

Output:
2
```

### Giải thích

Chọn tập {1,2,3} và {4,5} để phủ tất cả phần tử.

---

## Test 10: COMPLETE_GREEDY - Bài Toán Tổng Hợp Greedy

### Mô tả

Bài toán tổng hợp yêu cầu áp dụng nhiều kỹ thuật greedy khác nhau.

### Đề bài

Cho một công ty với n nhân viên và m dự án. Mỗi nhân viên có kỹ năng và mức lương, mỗi dự án có yêu cầu kỹ năng và ngân sách. Tối đa hóa lợi nhuận.

### Input

- Dòng 1: n, m (số nhân viên và số dự án)
- n dòng tiếp theo: skill_i, salary_i của nhân viên i
- m dòng tiếp theo: required_skill_j, budget_j của dự án j

### Output

- Lợi nhuận tối đa có thể đạt được

### Ví dụ

```
Input:
3 3
5 100
3 80
7 150
4 120
6 200
2 90

Output:
130
```

### Giải thích

Gán nhân viên 2 (skill=3, salary=80) cho dự án 3 (required=2, budget=90), lợi nhuận = 90-80 = 10.
Gán nhân viên 1 (skill=5, salary=100) cho dự án 1 (required=4, budget=120), lợi nhuận = 120-100 = 20.
Gán nhân viên 3 (skill=7, salary=150) cho dự án 2 (required=6, budget=200), lợi nhuận = 200-150 = 50.
Tổng lợi nhuận = 10 + 20 + 50 = 80.

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành

1. **Hiểu rõ bài toán** và xác định có thể áp dụng greedy không
2. **Thiết kế greedy choice** phù hợp
3. **Chứng minh tính đúng đắn** bằng exchange argument hoặc staying ahead
4. **Cài đặt thuật toán** hiệu quả
5. **Test với các trường hợp biên**

### Tiêu Chí Đánh Giá

- **Tính đúng đắn**: Thuật toán cho kết quả tối ưu
- **Hiệu quả**: Độ phức tạp thời gian hợp lý
- **Chứng minh**: Có thể giải thích tại sao greedy hoạt động
- **Cài đặt**: Code rõ ràng, xử lý đúng edge cases

### Lộ Trình Học Tập

1. **Tuần 1**: Test 01-03 (Greedy cơ bản)
2. **Tuần 2**: Test 04-06 (Thuật toán kinh điển)
3. **Tuần 3**: Test 07-09 (Bài toán nâng cao)
4. **Tuần 4**: Test 10 và tổng hợp kiến thức

### Mẹo Giải Bài

1. **Xác định greedy choice**: Tìm tiêu chí sắp xếp hoặc lựa chọn
2. **Chứng minh bằng phản chứng**: Giả sử có lời giải tốt hơn
3. **Kiểm tra optimal substructure**: Bài toán con có cấu trúc tương tự
4. **Cài đặt cẩn thận**: Chú ý thứ tự và điều kiện

---

**Ghi chú**: Greedy algorithms rất mạnh mẽ nhưng cần chứng minh cẩn thận. Không phải bài toán nào cũng có thể giải bằng greedy!
