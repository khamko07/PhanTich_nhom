# 10 Bộ Test - Đề Tài 6: Kỹ Thuật Two Pointers

## Tổng Quan

Bộ test này được thiết kế để thực hành các kỹ thuật Two Pointers từ cơ bản đến nâng cao. Mỗi test tập trung vào một khía cạnh khác nhau của kỹ thuật này, giúp học viên nắm vững các pattern và ứng dụng phổ biến.

---

## Test 01: TWO_SUM - Two Sum trên Mảng Đã Sắp Xếp

### Mô tả
Tìm hai số trong mảng đã sắp xếp có tổng bằng target sử dụng two pointers.

### Đề bài
Cho mảng đã sắp xếp tăng dần và một số target. Tìm chỉ số của hai phần tử có tổng bằng target.

### Input
- Dòng 1: n, target (số phần tử và giá trị target)
- Dòng 2: n số nguyên đã sắp xếp tăng dần

### Output
- Hai chỉ số của hai phần tử có tổng bằng target (0-indexed)
- -1 -1 nếu không tìm thấy

### Ví dụ
```
Input:
4 9
2 7 11 15

Output:
0 1
```

### Hướng dẫn
Sử dụng hai pointer: một từ đầu, một từ cuối. Di chuyển dựa trên so sánh tổng với target.

---

## Test 02: CONTAINER_WATER - Container With Most Water

### Mô tả
Tìm hai đường thẳng tạo thành container chứa nhiều nước nhất.

### Đề bài
Cho mảng height[i] biểu diễn chiều cao các đường thẳng. Tìm diện tích lớn nhất có thể tạo thành.

### Input
- Dòng 1: n (số đường thẳng)
- Dòng 2: n số nguyên biểu diễn chiều cao

### Output
- Diện tích lớn nhất

### Ví dụ
```
Input:
9
1 8 6 2 5 4 8 3 7

Output:
49
```

### Giải thích
Container được tạo bởi đường thẳng tại vị trí 1 (height=8) và vị trí 8 (height=7), diện tích = min(8,7) * (8-1) = 49.

---

## Test 03: LONGEST_SUBSTRING - Longest Substring Without Repeating

### Mô tả
Tìm độ dài chuỗi con dài nhất không có ký tự lặp lại sử dụng sliding window.

### Đề bài
Cho một chuỗi s, tìm độ dài của chuỗi con dài nhất không có ký tự nào lặp lại.

### Input
- Một chuỗi s (chỉ chứa chữ cái thường)

### Output
- Độ dài chuỗi con dài nhất

### Ví dụ
```
Input:
abcabcbb

Output:
3
```

### Giải thích
Chuỗi con "abc" có độ dài 3 và không có ký tự lặp lại.

---

## Test 04: REMOVE_DUPLICATES - Remove Duplicates from Sorted Array

### Mô tả
Xóa các phần tử trùng lặp trong mảng đã sắp xếp sử dụng two pointers.

### Đề bài
Cho mảng đã sắp xếp, xóa các phần tử trùng lặp in-place và trả về độ dài mảng mới.

### Input
- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên đã sắp xếp

### Output
- Dòng 1: mảng sau khi xóa trùng lặp
- Dòng 2: độ dài mảng mới

### Ví dụ
```
Input:
10
0 0 1 1 1 2 2 3 3 4

Output:
0 1 2 3 4
5
```

---

## Test 05: SUBARRAY_SUM - Subarray Sum Equals K

### Mô tả
Đếm số lượng subarray có tổng bằng k sử dụng prefix sum và hash map.

### Đề bài
Cho mảng nums và số nguyên k, đếm số lượng subarray liên tục có tổng bằng k.

### Input
- Dòng 1: n, k
- Dòng 2: n số nguyên

### Output
- Số lượng subarray có tổng bằng k

### Ví dụ
```
Input:
3 2
1 1 1

Output:
2
```

### Giải thích
Có 2 subarray: [1,1] từ vị trí 0-1 và [1,1] từ vị trí 1-2.

---

## Test 06: THREE_SUM - 3Sum Problem

### Mô tả
Tìm tất cả bộ ba số có tổng bằng 0 sử dụng three pointers.

### Đề bài
Cho mảng nums, tìm tất cả bộ ba (i,j,k) sao cho nums[i] + nums[j] + nums[k] = 0.

### Input
- Dòng 1: n
- Dòng 2: n số nguyên

### Output
- Số lượng bộ ba khác nhau có tổng bằng 0

### Ví dụ
```
Input:
6
-1 0 1 2 -1 -4

Output:
2
```

### Giải thích
Có 2 bộ ba: [-1,-1,2] và [-1,0,1].

---

## Test 07: PALINDROME_CHECK - Valid Palindrome

### Mô tả
Kiểm tra chuỗi có phải palindrome không sử dụng two pointers.

### Đề bài
Cho một chuỗi, kiểm tra xem nó có phải palindrome không (chỉ xét chữ cái và số, bỏ qua case).

### Input
- Một chuỗi s

### Output
- "YES" nếu là palindrome, "NO" nếu không

### Ví dụ
```
Input:
A man a plan a canal Panama

Output:
YES
```

---

## Test 08: TRAPPING_WATER - Trapping Rain Water

### Mô tả
Tính lượng nước mưa có thể chứa được sử dụng two pointers.

### Đề bài
Cho mảng height biểu diễn độ cao các cột, tính lượng nước mưa có thể chứa được.

### Input
- Dòng 1: n
- Dòng 2: n số nguyên biểu diễn độ cao

### Output
- Tổng lượng nước có thể chứa được

### Ví dụ
```
Input:
12
0 1 0 2 1 0 1 3 2 1 2 1

Output:
6
```

---

## Test 09: MINIMUM_WINDOW - Minimum Window Substring

### Mô tả
Tìm chuỗi con nhỏ nhất chứa tất cả ký tự của pattern sử dụng sliding window.

### Đề bài
Cho chuỗi s và pattern t, tìm chuỗi con nhỏ nhất của s chứa tất cả ký tự của t.

### Input
- Dòng 1: chuỗi s
- Dòng 2: chuỗi t (pattern)

### Output
- Độ dài chuỗi con nhỏ nhất, -1 nếu không tồn tại

### Ví dụ
```
Input:
ADOBECODEBANC
ABC

Output:
4
```

### Giải thích
Chuỗi con nhỏ nhất là "BANC" có độ dài 4.

---

## Test 10: COMPLETE_TWO_POINTERS - Complete Two Pointers Problem

### Mô tả
Bài toán tổng hợp sử dụng nhiều kỹ thuật two pointers khác nhau.

### Đề bài
Cho mảng nums và các truy vấn. Hỗ trợ các thao tác:
1. Tìm cặp có tổng gần nhất với target
2. Tìm longest subarray có tổng ≤ k
3. Đếm số palindromic substrings
4. Tìm container with most water

### Input
- Dòng 1: n, q (kích thước mảng và số truy vấn)
- Dòng 2: n số nguyên
- q dòng tiếp theo: mỗi dòng là một truy vấn
  - "CLOSEST target": tìm cặp có tổng gần target nhất
  - "SUBARRAY k": tìm longest subarray có tổng ≤ k
  - "PALINDROME": đếm palindromic substrings
  - "WATER": tìm container with most water

### Output
- Với mỗi truy vấn, in kết quả tương ứng

### Ví dụ
```
Input:
5 3
1 8 6 2 5
CLOSEST 10
SUBARRAY 15
WATER

Output:
8
4
20
```

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành
1. **Hiểu rõ bài toán** và xác định loại two pointers phù hợp
2. **Vẽ sơ đồ** để hiểu cách di chuyển các pointers
3. **Cài đặt** từng bước một cách cẩn thận
4. **Test** với các trường hợp biên
5. **Tối ưu hóa** và xử lý edge cases

### Tiêu Chí Đánh Giá
- **Tính đúng đắn**: Code chạy đúng với tất cả test case
- **Hiệu quả**: Độ phức tạp thời gian tối ưu (thường O(n))
- **Rõ ràng**: Logic dễ hiểu, code sạch
- **Xử lý biên**: Xử lý đúng các trường hợp đặc biệt

### Lộ Trình Học Tập
1. **Tuần 1**: Test 01-03 (Two pointers cơ bản)
2. **Tuần 2**: Test 04-06 (Sliding window và three pointers)
3. **Tuần 3**: Test 07-09 (Bài toán nâng cao)
4. **Tuần 4**: Test 10 và tổng hợp kiến thức

### Mẹo Giải Bài
1. **Xác định pattern**: Same direction, opposite direction, hay fast & slow
2. **Kiểm tra điều kiện**: Khi nào di chuyển pointer nào
3. **Xử lý duplicate**: Cẩn thận với các phần tử trùng lặp
4. **Debug hiệu quả**: In ra trạng thái các pointers

---

**Ghi chú**: Two Pointers là kỹ thuật quan trọng giúp tối ưu hóa nhiều bài toán từ O(n²) xuống O(n). Hãy thực hành nhiều để nắm vững các pattern!