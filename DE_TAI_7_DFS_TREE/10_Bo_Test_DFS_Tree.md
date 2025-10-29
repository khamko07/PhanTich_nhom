# 10 Bộ Test - Đề Tài 7: Depth-First Search Tree

## Tổng Quan

Bộ test này được thiết kế để thực hành các kỹ thuật liên quan đến DFS Tree từ cơ bản đến nâng cao. Mỗi test tập trung vào một ứng dụng cụ thể của DFS Tree trong việc giải quyết các bài toán đồ thị.

---

## Test 01: DFS_TREE - Xây Dựng DFS Tree

### Mô tả
Xây dựng DFS tree từ đồ thị và phân loại các cạnh thành tree edge và back edge.

### Đề bài
Cho đồ thị vô hướng, thực hiện DFS từ đỉnh 0 và phân loại các cạnh.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh nối u và v)

### Output
- Dòng 1: số lượng tree edges
- Các dòng tiếp theo: các tree edges
- Dòng tiếp theo: số lượng back edges  
- Các dòng cuối: các back edges

### Ví dụ
```
Input:
5 6
0 1
0 2
1 3
2 3
3 4
1 4

Output:
4
0 1
1 3
3 4
0 2
2
2 3
1 4
```

### Hướng dẫn
Sử dụng DFS để duyệt đồ thị, phân biệt tree edge (dẫn đến đỉnh chưa thăm) và back edge (dẫn đến đỉnh đã thăm, không phải cha).

---

## Test 02: CYCLE_DETECTION - Phát Hiện Chu Trình

### Mô tả
Sử dụng DFS để phát hiện chu trình trong đồ thị vô hướng.

### Đề bài
Kiểm tra xem đồ thị vô hướng có chứa chu trình hay không.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh nối u và v)

### Output
- "YES" nếu có chu trình, "NO" nếu không có

### Ví dụ
```
Input:
4 4
0 1
1 2
2 3
3 0

Output:
YES
```

### Giải thích
Đồ thị tạo thành chu trình 0-1-2-3-0.

---

## Test 03: TOPOLOGICAL_SORT - Sắp Xếp Topo

### Mô tả
Sử dụng DFS để thực hiện sắp xếp topo trên đồ thị có hướng không chu trình (DAG).

### Đề bài
Cho DAG, tìm một thứ tự topo của các đỉnh.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh có hướng từ u đến v)

### Output
- Một thứ tự topo của các đỉnh

### Ví dụ
```
Input:
6 6
5 2
5 0
4 0
4 1
2 3
3 1

Output:
5 4 2 3 1 0
```

### Hướng dẫn
Sử dụng DFS và thêm đỉnh vào kết quả khi finish, sau đó đảo ngược thứ tự.

---

## Test 04: STRONGLY_CONNECTED - Thành Phần Liên Thông Mạnh

### Mô tả
Tìm tất cả các thành phần liên thông mạnh (SCC) trong đồ thị có hướng sử dụng thuật toán Kosaraju.

### Đề bài
Cho đồ thị có hướng, tìm tất cả các SCC.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh có hướng từ u đến v)

### Output
- Dòng 1: số lượng SCC
- Các dòng tiếp theo: mỗi dòng chứa các đỉnh trong một SCC

### Ví dụ
```
Input:
5 5
1 0
0 2
2 1
0 3
3 4

Output:
3
0 1 2
3
4
```

---

## Test 05: BRIDGES - Tìm Cầu

### Mô tả
Tìm tất cả các cầu (bridge) trong đồ thị vô hướng sử dụng thuật toán Tarjan.

### Đề bài
Cho đồ thị vô hướng liên thông, tìm tất cả các cầu.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh nối u và v)

### Output
- Dòng 1: số lượng cầu
- Các dòng tiếp theo: mỗi dòng chứa một cầu (u, v) với u < v

### Ví dụ
```
Input:
7 7
0 1
1 2
2 0
1 3
3 4
4 5
5 3

Output:
1
1 3
```

### Giải thích
Cạnh (1,3) là cầu vì việc loại bỏ nó sẽ tách đồ thị thành hai thành phần liên thông.

---

## Test 06: ARTICULATION_POINTS - Tìm Khớp

### Mô tả
Tìm tất cả các điểm khớp (articulation point) trong đồ thị vô hướng.

### Đề bài
Cho đồ thị vô hướng liên thông, tìm tất cả các điểm khớp.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh nối u và v)

### Output
- Các điểm khớp theo thứ tự tăng dần

### Ví dụ
```
Input:
7 7
0 1
1 2
2 0
1 3
3 4
4 5
5 3

Output:
1
```

### Giải thích
Đỉnh 1 là điểm khớp vì việc loại bỏ nó sẽ tách đồ thị thành hai thành phần liên thông.

---

## Test 07: BICONNECTED_COMPONENTS - Thành Phần Song Liên Thông

### Mô tả
Tìm tất cả các thành phần song liên thông trong đồ thị vô hướng.

### Đề bài
Cho đồ thị vô hướng, tìm tất cả các thành phần song liên thông.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh nối u và v)

### Output
- Dòng 1: số lượng thành phần song liên thông
- Các dòng tiếp theo: mỗi dòng chứa các cạnh trong một thành phần

### Ví dụ
```
Input:
6 7
0 1
1 2
2 0
1 3
3 4
4 5
5 3

Output:
3
0 1
1 2
2 0
1 3
3 4
4 5
5 3
```

---

## Test 08: DIRECTED_CYCLE - Chu Trình Trong Đồ Thị Có Hướng

### Mô tả
Phát hiện chu trình trong đồ thị có hướng sử dụng DFS với 3 màu.

### Đề bài
Kiểm tra xem đồ thị có hướng có chứa chu trình hay không.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh có hướng từ u đến v)

### Output
- "YES" nếu có chu trình, "NO" nếu không có

### Ví dụ
```
Input:
3 3
0 1
1 2
2 0

Output:
YES
```

---

## Test 09: EDGE_CLASSIFICATION - Phân Loại Cạnh

### Mô tả
Phân loại tất cả các cạnh trong đồ thị có hướng thành tree, back, forward, và cross edges.

### Đề bài
Cho đồ thị có hướng, phân loại tất cả các cạnh.

### Input
- Dòng 1: n, m (số đỉnh và số cạnh)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh có hướng từ u đến v)

### Output
- Số lượng mỗi loại cạnh: tree, back, forward, cross

### Ví dụ
```
Input:
4 6
0 1
0 2
1 2
1 3
2 3
3 1

Output:
Tree edges: 3
Back edges: 1
Forward edges: 1
Cross edges: 1
```

---

## Test 10: COMPLETE_DFS - Bài Toán Tổng Hợp DFS

### Mô tả
Bài toán tổng hợp yêu cầu thực hiện nhiều thao tác khác nhau trên đồ thị.

### Đề bài
Cho đồ thị và các truy vấn. Hỗ trợ các thao tác:
1. Kiểm tra có chu trình
2. Đếm số thành phần liên thông
3. Tìm đường đi DFS từ u đến v
4. Kiểm tra u có phải tổ tiên của v trong DFS tree không

### Input
- Dòng 1: n, m, q (số đỉnh, số cạnh, số truy vấn)
- m dòng tiếp theo: mỗi dòng chứa u, v (cạnh)
- q dòng tiếp theo: mỗi dòng là một truy vấn
  - "CYCLE": kiểm tra chu trình
  - "COMPONENTS": đếm thành phần liên thông
  - "PATH u v": tìm đường đi DFS từ u đến v
  - "ANCESTOR u v": kiểm tra u có phải tổ tiên của v không

### Output
- Với mỗi truy vấn, in kết quả tương ứng

### Ví dụ
```
Input:
5 4 4
0 1
1 2
3 4
2 3
CYCLE
COMPONENTS
PATH 0 4
ANCESTOR 0 2

Output:
NO
1
0 1 2 3 4
YES
```

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành
1. **Hiểu rõ lý thuyết** về DFS tree và các ứng dụng
2. **Vẽ sơ đồ** để hiểu cách DFS hoạt động trên đồ thị
3. **Cài đặt từng bước** một cách cẩn thận
4. **Test với ví dụ nhỏ** trước khi chạy test lớn
5. **Debug bằng cách in** trạng thái DFS tree

### Tiêu Chí Đánh Giá
- **Tính đúng đắn**: Thuật toán cho kết quả chính xác
- **Hiệu quả**: Độ phức tạp O(V + E) cho hầu hết bài toán
- **Rõ ràng**: Code dễ đọc, logic rõ ràng
- **Xử lý biên**: Xử lý đúng đồ thị rỗng, không liên thông

### Lộ Trình Học Tập
1. **Tuần 1**: Test 01-03 (DFS cơ bản, chu trình, topo sort)
2. **Tuần 2**: Test 04-06 (SCC, cầu, khớp)
3. **Tuần 3**: Test 07-09 (Biconnected, directed cycle, edge classification)
4. **Tuần 4**: Test 10 và tổng hợp kiến thức

### Mẹo Giải Bài
1. **Khởi tạo đúng** các mảng visited, parent, disc, low
2. **Xử lý đồ thị không liên thông** bằng cách duyệt tất cả đỉnh
3. **Chú ý thứ tự** khi phân loại cạnh
4. **Sử dụng stack** thay đệ quy cho đồ thị lớn

---

**Ghi chú**: DFS Tree là nền tảng cho nhiều thuật toán đồ thị quan trọng. Hãy nắm vững lý thuyết trước khi thực hành!