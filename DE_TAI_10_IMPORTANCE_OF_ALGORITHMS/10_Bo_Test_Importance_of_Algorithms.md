# 10 Bộ Test - Đề Tài 10: The Importance of Algorithms

## Tổng Quan

Bộ test này được thiết kế để thực hành và hiểu sâu về tầm quan trọng của thuật toán trong các lĩnh vực khác nhau. Mỗi test tập trung vào một ứng dụng thực tế của thuật toán trong cuộc sống và công nghệ.

---

## Test 01: SEARCH_ENGINE - PageRank Algorithm

### Mô tả

Triển khai thuật toán PageRank đơn giản để xếp hạng trang web dựa trên liên kết.

### Đề bài

Cho một đồ thị có hướng đại diện cho các trang web và liên kết giữa chúng. Tính PageRank cho mỗi trang.

### Input

- Dòng 1: n, m (số trang web và số liên kết)
- m dòng tiếp theo: mỗi dòng chứa u, v (trang u liên kết đến trang v)
- Dòng cuối: số lần lặp

### Output

- n dòng: PageRank của mỗi trang (làm tròn 4 chữ số thập phân)

### Ví dụ

```
Input:
4 5
0 1
0 2
1 2
2 0
2 3
10

Output:
0.3725
0.1958
0.3942
0.0375
```

### Hướng dẫn

Sử dụng công thức PageRank với damping factor = 0.85.

---

## Test 02: RECOMMENDATION_SYSTEM - Collaborative Filtering

### Mô tả

Xây dựng hệ thống gợi ý phim dựa trên collaborative filtering.

### Đề bài

Cho ma trận đánh giá của người dùng cho các bộ phim. Gợi ý phim cho người dùng mục tiêu.

### Input

- Dòng 1: n, m, target (số người dùng, số phim, người dùng mục tiêu)
- n dòng tiếp theo: mỗi dòng chứa m số (đánh giá từ 1-5, 0 nếu chưa xem)
- Dòng cuối: số lượng gợi ý cần thiết

### Output

- Danh sách ID phim được gợi ý (sắp xếp theo độ ưu tiên)

### Ví dụ

```
Input:
4 5 0
5 3 0 1 4
3 1 2 3 3
4 3 4 3 5
2 1 0 5 4
2

Output:
2 4
```

### Giải thích

Tìm người dùng tương tự và gợi ý phim họ thích mà người dùng mục tiêu chưa xem.

---

## Test 03: GPS_NAVIGATION - Shortest Path

### Mô tả

Tìm đường đi ngắn nhất trong hệ thống GPS với các ràng buộc thực tế.

### Đề bài

Cho bản đồ đường bộ với thời gian di chuyển. Tìm đường đi nhanh nhất từ điểm A đến B.

### Input

- Dòng 1: n, m (số nút giao thông và số đường)
- m dòng tiếp theo: u, v, time (đường từ u đến v mất time phút)
- Dòng cuối: start, end (điểm bắt đầu và kết thúc)

### Output

- Dòng 1: thời gian ngắn nhất (phút)
- Dòng 2: đường đi (các nút trung gian)

### Ví dụ

```
Input:
5 7
0 1 10
0 2 5
1 3 1
2 1 3
2 3 9
3 4 2
1 4 4
0 4

Output:
10
0 2 1 4
```

### Hướng dẫn

Sử dụng thuật toán Dijkstra với các tối ưu hóa cho GPS thực tế.

---

## Test 04: SOCIAL_NETWORK - Community Detection

### Mô tả

Phát hiện cộng đồng trong mạng xã hội sử dụng thuật toán clustering.

### Đề bài

Cho đồ thị mạng xã hội, tìm các nhóm người có mối quan hệ chặt chẽ.

### Input

- Dòng 1: n, m (số người và số mối quan hệ)
- m dòng tiếp theo: u, v (người u và v là bạn bè)

### Output

- Số lượng cộng đồng
- Mỗi dòng tiếp theo: thành viên của một cộng đồng

### Ví dụ

```
Input:
6 7
0 1
1 2
0 2
3 4
4 5
3 5
2 3

Output:
2
0 1 2 3
4 5
```

### Giải thích

Sử dụng thuật toán như Louvain hoặc modularity optimization.

---

## Test 05: MACHINE_LEARNING - K-Means Clustering

### Mô tả

Triển khai thuật toán K-Means để phân cụm dữ liệu.

### Đề bài

Cho tập điểm trong không gian 2D, phân thành k cụm sử dụng K-Means.

### Input

- Dòng 1: n, k (số điểm và số cụm)
- n dòng tiếp theo: x, y (tọa độ điểm)

### Output

- k dòng: tọa độ centroid của mỗi cụm (làm tròn 2 chữ số)
- n dòng: nhãn cụm của mỗi điểm (0 đến k-1)

### Ví dụ

```
Input:
6 2
1.0 1.0
1.5 2.0
3.0 4.0
5.0 7.0
3.5 5.0
4.5 5.0

Output:
1.25 1.50
4.00 5.50
0
0
1
1
1
1
```

### Hướng dẫn

Khởi tạo centroid ngẫu nhiên, lặp cho đến khi hội tụ.

---

## Test 06: CRYPTOGRAPHY - RSA Encryption

### Mô tả

Triển khai thuật toán mã hóa RSA cơ bản.

### Đề bài

Tạo khóa RSA và mã hóa/giải mã thông điệp.

### Input

- Dòng 1: p, q (hai số nguyên tố)
- Dòng 2: message (số cần mã hóa)

### Output

- Dòng 1: n, e (khóa công khai)
- Dòng 2: d (khóa riêng tư)
- Dòng 3: encrypted (thông điệp đã mã hóa)
- Dòng 4: decrypted (thông điệp đã giải mã)

### Ví dụ

```
Input:
7 11
42

Output:
77 7
43
63
42
```

### Giải thích

n = p*q, e = 7 (thường dùng), d là nghịch đảo modular của e.

---

## Test 07: BIOINFORMATICS - DNA Sequence Alignment

### Mô tả

Căn chỉnh hai chuỗi DNA sử dụng thuật toán Smith-Waterman.

### Đề bài

Tìm căn chỉnh tối ưu giữa hai chuỗi DNA.

### Input

- Dòng 1: chuỗi DNA thứ nhất
- Dòng 2: chuỗi DNA thứ hai
- Dòng 3: match_score, mismatch_score, gap_penalty

### Output

- Dòng 1: điểm số căn chỉnh tối ưu
- Dòng 2: chuỗi 1 đã căn chỉnh
- Dòng 3: chuỗi 2 đã căn chỉnh

### Ví dụ

```
Input:
ACGTACGT
ACGTGCGT
2 -1 -1

Output:
12
ACGTACGT
ACGT-CGT
```

### Hướng dẫn

Sử dụng dynamic programming với ma trận điểm số.

---

## Test 08: LOGISTICS - Vehicle Routing Problem

### Mô tả

Tối ưu hóa tuyến đường giao hàng cho nhiều xe tải.

### Đề bài

Cho vị trí khách hàng và xe tải, tìm tuyến đường tối ưu để giao hàng.

### Input

- Dòng 1: n, k (số khách hàng và số xe)
- Dòng 2: depot_x, depot_y (tọa độ kho)
- n dòng tiếp theo: x, y, demand (tọa độ và nhu cầu khách hàng)
- Dòng cuối: vehicle_capacity

### Output

- k dòng: mỗi dòng là tuyến đường của một xe (danh sách khách hàng)
- Dòng cuối: tổng khoảng cách

### Ví dụ

```
Input:
4 2
0 0
2 3 10
5 1 15
1 4 20
3 2 25
50

Output:
0 2 0
1 3 0
18.45
```

### Giải thích

Mỗi xe bắt đầu và kết thúc tại kho (0), không vượt quá sức chứa.

---

## Test 09: FINANCE - Portfolio Optimization

### Mô tả

Tối ưu hóa danh mục đầu tư sử dụng Modern Portfolio Theory.

### Đề bài

Cho lợi nhuận kỳ vọng và ma trận hiệp phương sai, tìm danh mục tối ưu.

### Input

- Dòng 1: n (số cổ phiếu)
- Dòng 2: n số (lợi nhuận kỳ vọng của mỗi cổ phiếu)
- n dòng tiếp theo: ma trận hiệp phương sai n×n
- Dòng cuối: target_return (lợi nhuận mục tiêu)

### Output

- n số: tỷ trọng của mỗi cổ phiếu trong danh mục (tổng = 1)
- Dòng cuối: rủi ro của danh mục (độ lệch chuẩn)

### Ví dụ

```
Input:
3
0.12 0.10 0.08
0.04 0.02 0.01
0.02 0.03 0.015
0.01 0.015 0.02
0.10

Output:
0.40 0.35 0.25
0.145
```

### Hướng dẫn

Sử dụng Quadratic Programming để tối thiểu hóa rủi ro với ràng buộc lợi nhuận.

---

## Test 10: AI_GAME - Minimax Algorithm

### Mô tả

Triển khai AI chơi game Tic-Tac-Toe sử dụng thuật toán Minimax.

### Đề bài

Cho trạng thái bàn cờ Tic-Tac-Toe, tìm nước đi tối ưu cho AI.

### Input

- 3 dòng: mỗi dòng chứa 3 ký tự đại diện cho bàn cờ
  - 'X': người chơi
  - 'O': AI
  - '.': ô trống
- Dòng cuối: lượt của ai ('X' hoặc 'O')

### Output

- Dòng 1: tọa độ nước đi tối ưu (row, col)
- Dòng 2: điểm số của nước đi này

### Ví dụ

```
Input:
X.O
.X.
O..
O

Output:
2 2
10
```

### Giải thích

AI chọn góc dưới phải để thắng game. Điểm số: thắng = 10, hòa = 0, thua = -10.

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành

1. **Hiểu bối cảnh**: Đọc kỹ mô tả ứng dụng thực tế
2. **Phân tích thuật toán**: Xác định thuật toán phù hợp
3. **Cài đặt từng bước**: Chia nhỏ bài toán
4. **Tối ưu hóa**: Cải thiện hiệu suất và độ chính xác
5. **Kiểm tra kết quả**: Verify với test cases

### Tiêu Chí Đánh Giá

- **Tính đúng đắn**: Kết quả chính xác theo yêu cầu
- **Hiệu quả**: Độ phức tạp thời gian và không gian hợp lý
- **Thực tế**: Có thể áp dụng trong môi trường thực
- **Mở rộng**: Dễ dàng scale và customize

### Lộ Trình Học Tập

1. **Tuần 1**: Test 01-03 (Web và Navigation)
2. **Tuần 2**: Test 04-06 (Social Network và ML)
3. **Tuần 3**: Test 07-09 (Bioinformatics và Optimization)
4. **Tuần 4**: Test 10 và tích hợp kiến thức

### Mẹo Giải Bài

1. **Nghiên cứu domain**: Hiểu rõ lĩnh vực ứng dụng
2. **Chọn thuật toán phù hợp**: Cân nhắc trade-offs
3. **Xử lý edge cases**: Dữ liệu thực tế thường phức tạp
4. **Optimize cho thực tế**: Không chỉ lý thuyết mà còn thực tiễn

### Ứng Dụng Thực Tế

Mỗi test trong bộ này đều có ứng dụng trực tiếp trong:

- **Công nghệ**: Search engines, recommendation systems
- **Giao thông**: GPS navigation, traffic optimization
- **Tài chính**: Portfolio management, risk analysis
- **Y tế**: Bioinformatics, drug discovery
- **Giải trí**: Game AI, content recommendation
- **Logistics**: Supply chain, delivery optimization

---

**Ghi chú**: Đây là những thuật toán đang được sử dụng hàng ngày bởi hàng tỷ người trên thế giới. Hiểu và thành thạo chúng sẽ mở ra nhiều cơ hội nghề nghiệp trong tương lai!