# 10 Bộ Test - Đề Tài 11: Sorting Algorithms

## Tổng Quan

Bộ test này được thiết kế để thực hành và so sánh các thuật toán sắp xếp khác nhau. Mỗi test tập trung vào một khía cạnh khác nhau của việc sắp xếp, từ cơ bản đến nâng cao, bao gồm cả phân tích hiệu suất và ứng dụng thực tế.

---

## Test 01: BUBBLE_SORT - Bubble Sort Algorithm

### Mô tả

Triển khai thuật toán Bubble Sort với các tối ưu hóa cơ bản.

### Đề bài

Sắp xếp mảng số nguyên theo thứ tự tăng dần sử dụng Bubble Sort.

### Input

- Dòng 1: n (số phần tử của mảng)
- Dòng 2: n số nguyên cách nhau bởi dấu cách

### Output

- Dòng 1: mảng đã sắp xếp theo thứ tự tăng dần
- Dòng 2: số lần so sánh thực hiện
- Dòng 3: số lần hoán đổi thực hiện

### Ví dụ

```
Input:
5
64 34 25 12 22

Output:
12 22 25 34 64
10
8
```

### Hướng dẫn

Implement early termination optimization khi không có hoán đổi nào xảy ra.

---

## Test 02: SELECTION_SORT - Selection Sort Algorithm

### Mô tả

Triển khai Selection Sort và phân tích số lần so sánh.

### Đề bài

Sắp xếp mảng sử dụng Selection Sort và đếm số operations.

### Input

- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần tìm minimum
- Dòng 3: số lần hoán đổi

### Ví dụ

```
Input:
6
29 10 14 37 13 25

Output:
10 13 14 25 29 37
6
5
```

### Giải thích

Selection Sort luôn thực hiện n-1 lần tìm minimum và tối đa n-1 lần hoán đổi.

---

## Test 03: INSERTION_SORT - Insertion Sort Algorithm

### Mô tả

Triển khai Insertion Sort với binary search optimization.

### Đề bài

Sắp xếp mảng sử dụng Insertion Sort, có thể tối ưu với binary search.

### Input

- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên
- Dòng 3: mode (0: normal, 1: binary search optimization)

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần so sánh
- Dòng 3: số lần dịch chuyển

### Ví dụ

```
Input:
5
5 2 4 6 1
0

Output:
1 2 4 5 6
8
8
```

### Hướng dẫn

Binary search có thể giảm số lần so sánh từ O(n²) xuống O(n log n).

---

## Test 04: MERGE_SORT - Merge Sort Algorithm

### Mô tả

Triển khai Merge Sort và phân tích độ sâu đệ quy.

### Đề bài

Sắp xếp mảng sử dụng Merge Sort và theo dõi quá trình chia nhỏ.

### Input

- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần gọi đệ quy
- Dòng 3: số lần merge
- Dòng 4: độ sâu đệ quy tối đa

### Ví dụ

```
Input:
8
38 27 43 3 9 82 10 1

Output:
1 3 9 10 27 38 43 82
15
7
3
```

### Giải thích

Merge Sort có độ phức tạp O(n log n) ổn định với mọi input.

---

## Test 05: QUICK_SORT - Quick Sort Algorithm

### Mô tả

Triển khai Quick Sort với các chiến lược chọn pivot khác nhau.

### Đề bài

Sắp xếp mảng sử dụng Quick Sort với pivot strategy được chỉ định.

### Input

- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên
- Dòng 3: pivot_strategy (0: first, 1: last, 2: middle, 3: random, 4: median-of-three)

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần gọi đệ quy
- Dòng 3: số lần partition
- Dòng 4: độ sâu đệ quy tối đa

### Ví dụ

```
Input:
7
10 7 8 9 1 5 6
2

Output:
1 5 6 7 8 9 10
13
6
4
```

### Hướng dẫn

Median-of-three thường cho performance tốt nhất trên thực tế.

---

## Test 06: HEAP_SORT - Heap Sort Algorithm

### Mô tả

Triển khai Heap Sort và visualize heap structure.

### Đề bài

Sắp xếp mảng sử dụng Heap Sort và theo dõi quá trình build heap.

### Input

- Dòng 1: n (số phần tử)
- Dòng 2: n số nguyên

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần heapify trong build phase
- Dòng 3: số lần heapify trong sort phase
- Dòng 4: tổng số lần so sánh

### Ví dụ

```
Input:
6
12 11 13 5 6 7

Output:
5 6 7 11 12 13
3
5
18
```

### Giải thích

Heap Sort có độ phức tạp O(n log n) và sắp xếp in-place.

---

## Test 07: COUNTING_SORT - Counting Sort Algorithm

### Mô tả

Triển khai Counting Sort cho các số nguyên trong phạm vi cho trước.

### Đề bài

Sắp xếp mảng các số nguyên không âm sử dụng Counting Sort.

### Input

- Dòng 1: n, k (số phần tử và giá trị lớn nhất)
- Dòng 2: n số nguyên trong khoảng [0, k]

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: kích thước mảng đếm sử dụng
- Dòng 3: tổng số phép gán

### Ví dụ

```
Input:
8 5
4 2 2 8 3 3 1 1

Output:
1 1 2 2 3 3 4 8
9
16
```

### Hướng dẫn

Counting Sort có độ phức tạp O(n + k) và là stable sort.

---

## Test 08: RADIX_SORT - Radix Sort Algorithm

### Mô tả

Triển khai Radix Sort với base khác nhau.

### Đề bài

Sắp xếp mảng số nguyên sử dụng Radix Sort với base được chỉ định.

### Input

- Dòng 1: n, base (số phần tử và cơ số)
- Dòng 2: n số nguyên dương

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần gọi counting sort
- Dòng 3: số digit tối đa

### Ví dụ

```
Input:
5 10
170 45 75 90 2

Output:
2 45 75 90 170
3
3
```

### Giải thích

Radix Sort có độ phức tạp O(d × (n + k)) với d là số digits.

---

## Test 09: BUCKET_SORT - Bucket Sort Algorithm

### Mô tả

Triển khai Bucket Sort cho số thực trong khoảng [0, 1).

### Đề bài

Sắp xếp mảng số thực sử dụng Bucket Sort.

### Input

- Dòng 1: n, num_buckets (số phần tử và số buckets)
- Dòng 2: n số thực trong khoảng [0, 1)

### Output

- Dòng 1: mảng đã sắp xếp (làm tròn 3 chữ số thập phân)
- Dòng 2: số buckets được sử dụng
- Dòng 3: kích thước bucket lớn nhất

### Ví dụ

```
Input:
6 3
0.897 0.565 0.656 0.1234 0.665 0.3434

Output:
0.123 0.343 0.565 0.656 0.665 0.897
3
3
```

### Hướng dẫn

Bucket Sort hiệu quả khi input được phân bố đều.

---

## Test 10: HYBRID_SORT - Hybrid Sorting Algorithm

### Mô tả

Triển khai thuật toán sắp xếp hybrid kết hợp nhiều phương pháp.

### Đề bài

Sắp xếp mảng sử dụng hybrid approach: Quick Sort + Insertion Sort + Heap Sort.

### Input

- Dòng 1: n, threshold (số phần tử và ngưỡng chuyển đổi)
- Dòng 2: n số nguyên

### Output

- Dòng 1: mảng đã sắp xếp
- Dòng 2: số lần sử dụng Quick Sort
- Dòng 3: số lần sử dụng Insertion Sort
- Dòng 4: số lần sử dụng Heap Sort

### Ví dụ

```
Input:
20 10
64 34 25 12 22 11 90 88 76 50 42 30 5 77 55 23 78 33 44 99

Output:
5 11 12 22 23 25 30 33 34 42 44 50 55 64 76 77 78 88 90 99
2
3
0
```

### Giải thích

- Quick Sort cho mảng lớn
- Insertion Sort cho mảng nhỏ (< threshold)
- Heap Sort khi Quick Sort có worst case

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành

1. **Hiểu thuật toán**: Đọc kỹ lý thuyết và complexity analysis
2. **Implement từng bước**: Bắt đầu với version cơ bản
3. **Tối ưu hóa**: Thêm các optimization techniques
4. **So sánh performance**: Test với different input sizes
5. **Phân tích trade-offs**: Memory vs Time, Stable vs Unstable

### Tiêu Chí Đánh Giá

- **Correctness**: Thuật toán sắp xếp đúng
- **Efficiency**: Độ phức tạp thời gian và không gian
- **Stability**: Giữ nguyên thứ tự các phần tử bằng nhau
- **Adaptability**: Hiệu suất với different input patterns
- **Implementation**: Code clean và optimize

### Lộ Trình Học Tập

1. **Tuần 1**: Test 01-03 (Simple sorts: Bubble, Selection, Insertion)
2. **Tuần 2**: Test 04-05 (Divide & Conquer: Merge, Quick)
3. **Tuần 3**: Test 06-08 (Advanced sorts: Heap, Counting, Radix)
4. **Tuần 4**: Test 09-10 (Specialized sorts: Bucket, Hybrid)

### Mẹo Giải Bài

1. **Chọn thuật toán phù hợp**:

   - Small arrays (n < 50): Insertion Sort
   - General purpose: Quick Sort hoặc Merge Sort
   - Integers in range: Counting Sort hoặc Radix Sort
   - Nearly sorted: Insertion Sort hoặc Bubble Sort

2. **Optimization techniques**:

   - Early termination trong Bubble Sort
   - Median-of-three pivot trong Quick Sort
   - Binary search trong Insertion Sort
   - Hybrid approach cho arrays lớn

3. **Memory considerations**:

   - In-place: Bubble, Selection, Insertion, Quick, Heap
   - Extra space: Merge, Counting, Radix, Bucket

4. **Stability requirements**:
   - Stable: Bubble, Insertion, Merge, Counting, Radix
   - Unstable: Selection, Quick, Heap

### So Sánh Thuật Toán

| Algorithm | Time (Best) | Time (Average) | Time (Worst) | Space    | Stable |
| --------- | ----------- | -------------- | ------------ | -------- | ------ |
| Bubble    | O(n)        | O(n²)          | O(n²)        | O(1)     | Yes    |
| Selection | O(n²)       | O(n²)          | O(n²)        | O(1)     | No     |
| Insertion | O(n)        | O(n²)          | O(n²)        | O(1)     | Yes    |
| Merge     | O(n log n)  | O(n log n)     | O(n log n)   | O(n)     | Yes    |
| Quick     | O(n log n)  | O(n log n)     | O(n²)        | O(log n) | No     |
| Heap      | O(n log n)  | O(n log n)     | O(n log n)   | O(1)     | No     |
| Counting  | O(n + k)    | O(n + k)       | O(n + k)     | O(k)     | Yes    |
| Radix     | O(d(n + k)) | O(d(n + k))    | O(d(n + k))  | O(n + k) | Yes    |

---

**Ghi chú**: Việc hiểu rõ các thuật toán sắp xếp là nền tảng quan trọng trong khoa học máy tính. Mỗi thuật toán có ưu nhược điểm riêng và phù hợp với các tình huống khác nhau!
