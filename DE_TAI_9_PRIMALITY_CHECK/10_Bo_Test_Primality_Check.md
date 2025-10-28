# 10 Bộ Test - Đề Tài 9: Primality Check

## Tổng Quan

Bộ test này được thiết kế để thực hành các thuật toán kiểm tra số nguyên tố từ cơ bản đến nâng cao. Mỗi test tập trung vào một phương pháp khác nhau và các ứng dụng thực tế của việc kiểm tra số nguyên tố.

---

## Test 01: TRIAL_DIVISION - Kiểm Tra Nguyên Tố Cơ Bản

### Mô tả
Kiểm tra một số có phải là số nguyên tố hay không bằng phương pháp chia thử.

### Đề bài
Cho một số nguyên n, kiểm tra xem n có phải là số nguyên tố hay không.

### Input
- Một số nguyên n (1 ≤ n ≤ 10^12)

### Output
- "YES" nếu n là số nguyên tố, "NO" nếu không

### Ví dụ
```
Input:
97

Output:
YES
```

### Hướng dẫn
Sử dụng phương pháp chia thử, chỉ kiểm tra các số từ 2 đến √n.

---

## Test 02: SIEVE_ERATOSTHENES - Sàng Eratosthenes

### Mô tả
Tìm tất cả số nguyên tố không vượt quá n sử dụng sàng Eratosthenes.

### Đề bài
Cho số nguyên n, tìm tất cả số nguyên tố từ 2 đến n.

### Input
- Một số nguyên n (2 ≤ n ≤ 10^6)

### Output
- Dòng 1: số lượng số nguyên tố
- Dòng 2: tất cả số nguyên tố từ 2 đến n

### Ví dụ
```
Input:
20

Output:
8
2 3 5 7 11 13 17 19
```

---

## Test 03: MILLER_RABIN - Miller-Rabin Test

### Mô tả
Kiểm tra số nguyên tố bằng thuật toán Miller-Rabin cho số rất lớn.

### Đề bài
Cho một số nguyên lớn n, sử dụng Miller-Rabin test để kiểm tra tính nguyên tố.

### Input
- Một số nguyên n (1 ≤ n ≤ 10^18)

### Output
- "YES" nếu n là số nguyên tố, "NO" nếu không

### Ví dụ
```
Input:
1000000007

Output:
YES
```

### Hướng dẫn
Sử dụng deterministic Miller-Rabin với các witness cố định.

---

## Test 04: SEGMENTED_SIEVE - Sàng Phân Đoạn

### Mô tả
Tìm số nguyên tố trong khoảng [L, R] sử dụng segmented sieve.

### Đề bài
Cho hai số L và R, tìm tất cả số nguyên tố trong khoảng [L, R].

### Input
- Dòng 1: L, R (1 ≤ L ≤ R ≤ 10^12, R - L ≤ 10^6)

### Output
- Dòng 1: số lượng số nguyên tố trong [L, R]
- Dòng 2: tất cả số nguyên tố trong [L, R]

### Ví dụ
```
Input:
10 20

Output:
4
11 13 17 19
```

---

## Test 05: PRIME_FACTORIZATION - Phân Tích Thừa Số Nguyên Tố

### Mô tả
Phân tích một số thành các thừa số nguyên tố.

### Đề bài
Cho số nguyên n, phân tích n thành tích các thừa số nguyên tố.

### Input
- Một số nguyên n (2 ≤ n ≤ 10^12)

### Output
- Các thừa số nguyên tố của n theo thứ tự tăng dần (có thể lặp lại)

### Ví dụ
```
Input:
60

Output:
2 2 3 5
```

### Giải thích
60 = 2² × 3 × 5

---

## Test 06: PRIME_COUNTING - Đếm Số Nguyên Tố

### Mô tả
Đếm số lượng số nguyên tố không vượt quá n.

### Đề bài
Cho số nguyên n, đếm số lượng số nguyên tố ≤ n.

### Input
- Một số nguyên n (1 ≤ n ≤ 10^7)

### Output
- Số lượng số nguyên tố ≤ n

### Ví dụ
```
Input:
100

Output:
25
```

### Hướng dẫn
Sử dụng sàng Eratosthenes và đếm số lượng số nguyên tố.

---

## Test 07: NEXT_PRIME - Tìm Số Nguyên Tố Tiếp Theo

### Mô tả
Tìm số nguyên tố nhỏ nhất lớn hơn n.

### Đề bài
Cho số nguyên n, tìm số nguyên tố nhỏ nhất > n.

### Input
- Một số nguyên n (1 ≤ n ≤ 10^12)

### Output
- Số nguyên tố nhỏ nhất lớn hơn n

### Ví dụ
```
Input:
20

Output:
23
```

---

## Test 08: TWIN_PRIMES - Số Nguyên Tố Sinh Đôi

### Mô tả
Tìm tất cả cặp số nguyên tố sinh đôi trong khoảng [L, R].

### Đề bài
Hai số nguyên tố p và p+2 được gọi là twin primes. Tìm tất cả cặp twin primes trong [L, R].

### Input
- Dòng 1: L, R (1 ≤ L ≤ R ≤ 10^6)

### Output
- Dòng 1: số lượng cặp twin primes
- Các dòng tiếp theo: mỗi dòng chứa một cặp twin primes

### Ví dụ
```
Input:
1 30

Output:
5
3 5
5 7
11 13
17 19
29 31
```

---

## Test 09: CARMICHAEL_NUMBERS - Số Carmichael

### Mô tả
Kiểm tra xem một số có phải là Carmichael number hay không.

### Đề bài
Carmichael number là hợp số n sao cho a^(n-1) ≡ 1 (mod n) với mọi a nguyên tố cùng nhau với n.

### Input
- Một số nguyên n (3 ≤ n ≤ 10^9)

### Output
- "YES" nếu n là Carmichael number, "NO" nếu không

### Ví dụ
```
Input:
561

Output:
YES
```

### Giải thích
561 = 3 × 11 × 17 là Carmichael number đầu tiên.

---

## Test 10: COMPLETE_PRIMALITY - Bài Toán Tổng Hợp

### Mô tả
Bài toán tổng hợp yêu cầu thực hiện nhiều thao tác liên quan đến số nguyên tố.

### Đề bài
Cho một dãy số và các truy vấn. Hỗ trợ các thao tác:
1. Kiểm tra số nguyên tố
2. Tìm số nguyên tố tiếp theo
3. Phân tích thừa số nguyên tố
4. Đếm số nguyên tố trong khoảng

### Input
- Dòng 1: n, q (số phần tử và số truy vấn)
- Dòng 2: n số nguyên
- q dòng tiếp theo: mỗi dòng là một truy vấn
  - "CHECK x": kiểm tra x có phải số nguyên tố
  - "NEXT x": tìm số nguyên tố > x
  - "FACTOR x": phân tích x thành thừa số nguyên tố
  - "COUNT L R": đếm số nguyên tố trong [L, R]

### Output
- Với mỗi truy vấn, in kết quả tương ứng

### Ví dụ
```
Input:
5 4
2 15 17 25 29
CHECK 17
NEXT 25
FACTOR 15
COUNT 10 30

Output:
YES
29
3 5
7
```

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành
1. **Hiểu rõ lý thuyết** về các phương pháp kiểm tra số nguyên tố
2. **Chọn phương pháp phù hợp** dựa trên kích thước input
3. **Cài đặt cẩn thận** để tránh overflow và edge cases
4. **Tối ưu hóa** cho từng bài toán cụ thể
5. **Test với số lớn** để đảm bảo tính đúng đắn

### Tiêu Chí Đánh Giá
- **Tính đúng đắn**: Thuật toán cho kết quả chính xác
- **Hiệu quả**: Độ phức tạp thời gian phù hợp với input
- **Xử lý số lớn**: Không bị overflow với số 64-bit
- **Edge cases**: Xử lý đúng các trường hợp đặc biệt (n=1, n=2, etc.)

### Lộ Trình Học Tập
1. **Tuần 1**: Test 01-03 (Phương pháp cơ bản)
2. **Tuần 2**: Test 04-06 (Sàng và ứng dụng)
3. **Tuần 3**: Test 07-09 (Bài toán nâng cao)
4. **Tuần 4**: Test 10 và tổng hợp kiến thức

### Mẹo Giải Bài
1. **Chọn thuật toán phù hợp**: Trial division cho số nhỏ, Miller-Rabin cho số lớn
2. **Xử lý overflow**: Sử dụng __int128 hoặc modular arithmetic
3. **Tối ưu hóa**: Chỉ kiểm tra số lẻ, sử dụng wheel factorization
4. **Precompute**: Tính trước số nguyên tố nhỏ nếu cần

### Các Lỗi Thường Gặp
1. **Overflow**: Không xử lý đúng phép nhân với số lớn
2. **Edge cases**: Quên xử lý n=1, n=2
3. **Thuật toán sai**: Dùng Fermat test cho Carmichael numbers
4. **Tối ưu hóa sai**: Không kiểm tra đến √n

---

**Ghi chú**: Primality testing là nền tảng của nhiều ứng dụng mật mã. Hãy hiểu rõ lý thuyết và chọn thuật toán phù hợp!