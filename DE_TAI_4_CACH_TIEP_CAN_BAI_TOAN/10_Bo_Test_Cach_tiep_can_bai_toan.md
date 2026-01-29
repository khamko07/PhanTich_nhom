# 10 Bộ Test - Đề Tài 4: Những Cách Tiếp Cận Bài Toán

## Tổng Quan

Bộ test này được thiết kế để thực hành các kỹ năng tiếp cận và giải quyết bài toán một cách có hệ thống. Mỗi bài test tập trung vào một khía cạnh khác nhau của việc phân tích và giải quyết bài toán.

---

## Test 01: APPROACH - Phân Tích Cách Tiếp Cận

### Mô tả
Cho một bài toán, hãy phân tích và đưa ra ít nhất 2 cách tiếp cận khác nhau để giải quyết.

### Đề bài
Tìm hai số trong mảng có tổng bằng một giá trị target cho trước.

### Input
- Dòng 1: n (số phần tử), target (giá trị cần tìm)
- Dòng 2: n số nguyên của mảng

### Output
- Hai chỉ số của hai phần tử có tổng bằng target (nếu có)
- -1 -1 nếu không tìm thấy

### Ví dụ
```
Input:
4 9
2 7 11 15

Output:
0 1
```

### Cách tiếp cận
1. **Brute Force**: O(n²) - duyệt tất cả cặp
2. **Hash Table**: O(n) - sử dụng map để lưu trữ

---

## Test 02: DIVIDE - Chia Nhỏ Vấn Đề

### Mô tả
Sử dụng phương pháp chia nhỏ vấn đề để giải bài toán phức tạp.

### Đề bài
Tính lũy thừa a^n một cách hiệu quả.

### Input
- Dòng 1: a, n (cơ số và số mũ)

### Output
- Kết quả a^n

### Ví dụ
```
Input:
2 10

Output:
1024
```

### Hướng dẫn
Chia bài toán thành các hàm con:
- `power(a, n)` - hàm chính
- `fastPower(a, n)` - tính lũy thừa nhanh
- `isEven(n)` - kiểm tra số chẵn

---

## Test 03: KATA - Coding Kata Practice

### Mô tả
Thực hành coding kata với bài toán sắp xếp mảng.

### Đề bài
Cài đặt thuật toán sắp xếp nổi bọt (Bubble Sort) và đếm số lần hoán đổi.

### Input
- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên của mảng

### Output
- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần hoán đổi

### Ví dụ
```
Input:
5
64 34 25 12 22

Output:
12 22 25 34 64
10
```

### Yêu cầu
Thực hiện 3 lần:
1. Lần 1: Code từ đầu, ghi thời gian
2. Lần 2: Code lại, so sánh thời gian
3. Lần 3: Code lần cuối, tối ưu hóa

---

## Test 04: ATOMIC - Atomic Code Practice

### Mô tả
Viết các atomic code functions cơ bản.

### Đề bài
Cài đặt các hàm atomic sau:
1. Tìm phần tử lớn nhất trong mảng
2. Đảo ngược mảng
3. Kiểm tra mảng có sắp xếp hay không

### Input
- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên của mảng

### Output
- Dòng 1: phần tử lớn nhất
- Dòng 2: mảng đảo ngược
- Dòng 3: "YES" nếu mảng gốc đã sắp xếp, "NO" nếu chưa

### Ví dụ
```
Input:
5
1 3 2 5 4

Output:
5
4 5 2 3 1
NO
```

---

## Test 05: DEBUG - Debug Strategy

### Mô tả
Tìm và sửa lỗi trong đoạn code cho trước.

### Đề bài
Cho đoạn code tính tổng các số chẵn trong mảng (có lỗi). Hãy tìm và sửa lỗi.

### Code có lỗi
```cpp
int sumEven(vector<int>& arr) {
    int sum = 0;
    for (int i = 1; i <= arr.size(); i++) {
        if (arr[i] % 2 = 0) {
            sum += arr[i];
        }
    }
    return sum;
}
```

### Input
- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên của mảng

### Output
- Tổng các số chẵn trong mảng

### Ví dụ
```
Input:
5
1 2 3 4 5

Output:
6
```

---

## Test 06: PATTERN - Pattern Recognition

### Mô tả
Nhận dạng pattern trong dãy số và dự đoán phần tử tiếp theo.

### Đề bài
Cho một dãy số, tìm quy luật và in ra k phần tử tiếp theo.

### Input
- Dòng 1: n, k (số phần tử đã cho, số phần tử cần tìm)
- Dòng 2: n số nguyên của dãy

### Output
- k số tiếp theo trong dãy

### Ví dụ
```
Input:
5 3
1 4 7 10 13

Output:
16 19 22
```

### Gợi ý
Phân tích các pattern phổ biến:
- Cấp số cộng
- Cấp số nhân  
- Fibonacci
- Số chính phương

---

## Test 07: OPTIMIZE - Optimization Techniques

### Mô tả
Tối ưu hóa thuật toán từ độ phức tạp cao xuống thấp.

### Đề bài
Tìm tất cả các cặp số trong mảng có hiệu bằng k.

### Input
- Dòng 1: n, k (số phần tử, hiệu cần tìm)
- Dòng 2: n số nguyên của mảng

### Output
- Số lượng cặp có hiệu bằng k

### Ví dụ
```
Input:
4 2
1 3 5 7

Output:
3
```

### Yêu cầu
Cài đặt 2 phiên bản:
1. Brute Force: O(n²)
2. Optimized: O(n) hoặc O(n log n)

---

## Test 08: RECURSIVE - Recursive Thinking

### Mô tả
Sử dụng tư duy đệ quy để giải quyết bài toán.

### Đề bài
Tính tổng các chữ số của một số nguyên dương bằng đệ quy.

### Input
- Một số nguyên dương n

### Output
- Tổng các chữ số của n

### Ví dụ
```
Input:
12345

Output:
15
```

### Hướng dẫn
Chia nhỏ bài toán:
- Trường hợp cơ sở: n < 10
- Trường hợp đệ quy: n >= 10

---

## Test 09: GREEDY - Greedy Strategy

### Mô tả
Áp dụng chiến lược tham lam để giải bài toán tối ưu.

### Đề bài
Cho n công việc với thời gian hoàn thành và deadline. Chọn tối đa số công việc có thể hoàn thành đúng hạn.

### Input
- Dòng 1: n (số công việc)
- n dòng tiếp theo: thời gian hoàn thành và deadline của mỗi công việc

### Output
- Số lượng công việc tối đa có thể hoàn thành

### Ví dụ
```
Input:
4
4 6
1 4
2 5
3 6

Output:
3
```

---

## Test 10: COMPLETE - Complete Problem Solving

### Mô tả
Bài toán tổng hợp yêu cầu áp dụng nhiều kỹ thuật khác nhau.

### Đề bài
Cho một ma trận n×m, tìm đường đi từ góc trên trái đến góc dưới phải sao cho tổng các số trên đường đi là lớn nhất. Chỉ được di chuyển xuống dưới hoặc sang phải.

### Input
- Dòng 1: n, m (kích thước ma trận)
- n dòng tiếp theo: mỗi dòng m số nguyên

### Output
- Tổng lớn nhất có thể đạt được

### Ví dụ
```
Input:
3 3
1 3 1
1 5 1
4 2 1

Output:
12
```

### Phân tích
Bài toán này yêu cầu:
1. Phân tích bài toán (DP)
2. Chia nhỏ vấn đề
3. Tối ưu hóa không gian
4. Xử lý trường hợp biên

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành
1. **Đọc kỹ đề bài** và phân tích yêu cầu
2. **Brainstorm** các cách tiếp cận khác nhau
3. **Chọn cách tiếp cận** phù hợp nhất
4. **Chia nhỏ bài toán** thành các phần đơn giản
5. **Cài đặt từng phần** một cách cẩn thận
6. **Test và debug** kỹ lưỡng
7. **Tối ưu hóa** nếu cần thiết

### Tiêu Chí Đánh Giá
- **Tính đúng đắn**: Code chạy đúng với tất cả test case
- **Hiệu quả**: Độ phức tạp thời gian và không gian hợp lý
- **Rõ ràng**: Code dễ đọc, có comment phù hợp
- **Tổng quát**: Xử lý được các trường hợp biên

### Lộ Trình Học Tập
1. **Tuần 1-2**: Test 01-03 (Cơ bản)
2. **Tuần 3-4**: Test 04-06 (Trung bình)
3. **Tuần 5-6**: Test 07-09 (Nâng cao)
4. **Tuần 7-8**: Test 10 và ôn tập tổng hợp

---

**Ghi chú**: Mỗi test nên được thực hiện theo phương pháp coding kata - làm nhiều lần để nắm vững kỹ thuật và cải thiện tốc độ coding.