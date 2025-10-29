# 10 Bộ Test - Đề Tài 12: Computational Complexity

## Tổng Quan

Bộ test này được thiết kế để thực hành và hiểu sâu về độ phức tạp tính toán, từ phân tích Big O cơ bản đến các khái niệm nâng cao như P vs NP, thuật toán xấp xỉ và amortized analysis. Mỗi test tập trung vào một khía cạnh quan trọng của lý thuyết độ phức tạp.

---

## Test 01: BIG_O_ANALYSIS - Big O Notation Analysis

### Mô tả

Phân tích độ phức tạp thời gian và không gian của các thuật toán khác nhau.

### Đề bài

Cho một đoạn code, xác định độ phức tạp thời gian và không gian của nó.

### Input

- Dòng 1: algorithm_type (1: nested loops, 2: recursive, 3: divide & conquer)
- Dòng 2: n (kích thước input)
- Các dòng tiếp theo: parameters tùy thuộc vào algorithm_type

### Output

- Dòng 1: time_complexity (dạng string như "O(n^2)")
- Dòng 2: space_complexity (dạng string như "O(1)")
- Dòng 3: actual_operations (số phép toán thực tế thực hiện)

### Ví dụ

```
Input:
1
100

Output:
O(n^2)
O(1)
4950
```

### Hướng dẫn

Phân tích từng vòng lặp và recursive call để xác định complexity.

---

## Test 02: AMORTIZED_ANALYSIS - Amortized Analysis

### Mô tả

Phân tích amortized cost của dynamic array operations.

### Đề bài

Mô phỏng dynamic array với doubling strategy và tính amortized cost.

### Input

- Dòng 1: n (số operations)
- n dòng tiếp theo: mỗi dòng chứa operation_type value
  - 1 value: insert value
  - 2: pop last element
  - 3: get size

### Output

- Dòng 1: total_operations_performed
- Dòng 2: total_resize_operations
- Dòng 3: amortized_cost_per_operation (làm tròn 2 chữ số)

### Ví dụ

```
Input:
5
1 10
1 20
1 30
2
3

Output:
5
2
2.40
```

### Giải thích

Dynamic array resize khi đầy, amortized analysis cho thấy cost trung bình là O(1).

---

## Test 03: SPACE_COMPLEXITY - Space Complexity Analysis

### Mô tả

Phân tích space complexity của các thuật toán đệ quy và iterative.

### Đề bài

So sánh space usage giữa recursive và iterative implementations.

### Input

- Dòng 1: algorithm_type (1: factorial, 2: fibonacci, 3: tree traversal)
- Dòng 2: n (input size)

### Output

- Dòng 1: recursive_space_complexity
- Dòng 2: iterative_space_complexity
- Dòng 3: recursive_max_stack_depth
- Dòng 4: iterative_extra_space

### Ví dụ

```
Input:
2
10

Output:
O(n)
O(1)
10
1
```

### Hướng dẫn

Đếm số recursive calls và auxiliary space sử dụng.

---

## Test 04: P_VS_NP - P vs NP Problems

### Mô tả

Phân biệt và giải quyết các bài toán P và NP-Complete.

### Đề bài

Cho một bài toán, xác định class complexity và giải quyết nếu có thể.

### Input

- Dòng 1: problem_type (1: sorting, 2: subset_sum, 3: graph_coloring, 4: shortest_path)
- Các dòng tiếp theo: input data cho problem tương ứng

### Output

- Dòng 1: complexity_class (P, NP, NP-Complete, NP-Hard)
- Dòng 2: best_known_algorithm_complexity
- Dòng 3: solution (nếu có thể giải trong thời gian hợp lý)

### Ví dụ

```
Input:
2
5 9
3 34 4 12 5

Output:
NP-Complete
O(2^n)
YES
```

### Giải thích

Subset Sum là NP-Complete, có thể giải bằng DP hoặc brute force.

---

## Test 05: NP_COMPLETENESS - NP-Completeness Proofs

### Mô tả

Demonstration của NP-Completeness reductions.

### Đề bài

Thực hiện reduction giữa các NP-Complete problems.

### Input

- Dòng 1: source_problem target_problem
- Các dòng tiếp theo: instance của source problem

### Output

- Dòng 1: reduction_possible (YES/NO)
- Dòng 2: reduction_complexity
- Các dòng tiếp theo: transformed instance (nếu có)

### Ví dụ

```
Input:
3SAT VERTEX_COVER
3
(x1 OR x2 OR x3) AND (NOT x1 OR x2 OR NOT x3) AND (x1 OR NOT x2 OR x3)

Output:
YES
O(n)
6 9
0 1
1 2
2 3
3 4
4 5
0 5
1 4
2 5
0 3
```

### Hướng dẫn

Sử dụng standard reductions giữa các NP-Complete problems.

---

## Test 06: APPROXIMATION_ALGORITHMS - Approximation Algorithms

### Mô tả

Triển khai và phân tích approximation algorithms.

### Đề bài

Giải quyết NP-Hard problems bằng approximation algorithms.

### Input

- Dòng 1: problem_type (1: vertex_cover, 2: tsp, 3: set_cover, 4: knapsack)
- Các dòng tiếp theo: problem instance

### Output

- Dòng 1: approximation_ratio
- Dòng 2: approximate_solution_value
- Dòng 3: solution_details

### Ví dụ

```
Input:
1
4 4
0 1
1 2
2 3
0 3

Output:
2.0
2
0 2
```

### Giải thích

Vertex Cover 2-approximation algorithm chọn cả hai endpoints của mỗi edge.

---

## Test 07: LOWER_BOUNDS - Lower Bounds Analysis

### Mô tả

Chứng minh lower bounds cho các bài toán cơ bản.

### Đề bài

Phân tích information-theoretic và adversarial lower bounds.

### Input

- Dòng 1: problem_type (1: sorting, 2: searching, 3: matrix_multiplication)
- Dòng 2: n (problem size)
- Dòng 3: model_type (1: comparison, 2: algebraic, 3: boolean)

### Output

- Dòng 1: lower_bound_complexity
- Dòng 2: matching_upper_bound (YES/NO)
- Dòng 3: gap_between_bounds

### Ví dụ

```
Input:
1
1000
1

Output:
Omega(n log n)
YES
0
```

### Giải thích

Comparison-based sorting có lower bound Ω(n log n), matching với merge sort.

---

## Test 08: PARALLEL_COMPLEXITY - Parallel Complexity Classes

### Mô tả

Phân tích complexity trong parallel computing models.

### Đề bài

Tính toán parallel time và work complexity.

### Input

- Dòng 1: algorithm_type (1: parallel_sum, 2: parallel_sort, 3: parallel_search)
- Dòng 2: n (input size)
- Dòng 3: p (number of processors)

### Output

- Dòng 1: parallel_time_complexity
- Dòng 2: work_complexity
- Dòng 3: efficiency (work/p\*time)
- Dòng 4: speedup_factor

### Ví dụ

```
Input:
1
1000000
1000

Output:
O(log n)
O(n)
0.91
909.09
```

### Hướng dẫn

Sử dụng PRAM model để phân tích parallel algorithms.

---

## Test 09: RANDOMIZED_COMPLEXITY - Randomized Algorithms

### Mô tả

Phân tích expected complexity của randomized algorithms.

### Đề bài

Triển khai và phân tích randomized algorithms.

### Input

- Dòng 1: algorithm_type (1: quicksort, 2: primality_test, 3: skip_list)
- Dòng 2: n (input size)
- Dòng 3: confidence_level (for Monte Carlo algorithms)

### Output

- Dòng 1: expected_time_complexity
- Dòng 2: worst_case_time_complexity
- Dòng 3: success_probability
- Dòng 4: number_of_trials_needed

### Ví dụ

```
Input:
2
1000000
0.99

Output:
O(k log log log n)
O(k log log log n)
0.99
7
```

### Giải thích

Miller-Rabin primality test có expected polynomial time.

---

## Test 10: COMPLEXITY_HIERARCHY - Complexity Hierarchy

### Mô tả

Demonstration của time và space hierarchy theorems.

### Đề bài

So sánh các complexity classes khác nhau.

### Input

- Dòng 1: hierarchy_type (1: time, 2: space, 3: nondeterministic)
- Dòng 2: lower_bound_function
- Dòng 3: upper_bound_function
- Dòng 4: n (input size for demonstration)

### Output

- Dòng 1: separation_exists (YES/NO/UNKNOWN)
- Dòng 2: hierarchy_theorem_applies (YES/NO)
- Dòng 3: example_problem_in_higher_class
- Dòng 4: resources_needed_ratio

### Ví dụ

```
Input:
1
n
n^2
1000

Output:
YES
YES
PALINDROME_RECOGNITION
1000.0
```

### Giải thích

Time Hierarchy Theorem: DTIME(n) ⊊ DTIME(n²).

---

## Hướng Dẫn Sử Dụng

### Cách Thực Hành

1. **Hiểu lý thuyết**: Đọc kỹ về complexity theory và các định lý cơ bản
2. **Phân tích từng bước**: Đếm operations và memory usage cẩn thận
3. **Chứng minh bounds**: Sử dụng mathematical techniques
4. **So sánh algorithms**: Hiểu trade-offs giữa time và space
5. **Áp dụng vào thực tế**: Kết nối với real-world problems

### Tiêu Chí Đánh Giá

- **Theoretical Understanding**: Hiểu các khái niệm complexity
- **Mathematical Rigor**: Chứng minh chính xác
- **Practical Application**: Áp dụng vào algorithms thực tế
- **Comparative Analysis**: So sánh các approaches khác nhau

### Lộ Trình Học Tập

1. **Tuần 1**: Test 01-03 (Basic complexity analysis)
2. **Tuần 2**: Test 04-06 (P vs NP và approximation)
3. **Tuần 3**: Test 07-09 (Advanced topics)
4. **Tuần 4**: Test 10 và tổng hợp kiến thức

### Mẹo Giải Bài

1. **Big O Analysis**:

   - Đếm nested loops
   - Phân tích recursive relations
   - Xác định dominant terms

2. **P vs NP**:

   - Biết các NP-Complete problems cơ bản
   - Hiểu reduction techniques
   - Phân biệt decision vs optimization problems

3. **Approximation Algorithms**:

   - Tính approximation ratio
   - Hiểu greedy approaches
   - Biết khi nào có FPTAS

4. **Lower Bounds**:
   - Sử dụng adversarial arguments
   - Information-theoretic bounds
   - Reduction-based proofs

### Complexity Classes Hierarchy

```
P ⊆ NP ⊆ PSPACE ⊆ EXPTIME ⊆ EXPSPACE ⊆ ...

Known Separations:
- P ⊊ EXPTIME (Time Hierarchy)
- PSPACE ⊊ EXPSPACE (Space Hierarchy)

Open Questions:
- P ?= NP
- NP ?= PSPACE
- PSPACE ?= EXPTIME
```

### Important Complexity Classes

| Class       | Definition                  | Example Problems        |
| ----------- | --------------------------- | ----------------------- |
| P           | Polynomial time             | Sorting, Shortest Path  |
| NP          | Nondeterministic polynomial | SAT, Vertex Cover       |
| NP-Complete | Hardest problems in NP      | 3-SAT, Hamiltonian Path |
| NP-Hard     | At least as hard as NP      | TSP, Knapsack           |
| PSPACE      | Polynomial space            | QBF, Game positions     |
| EXPTIME     | Exponential time            | Chess (generalized)     |

---

**Ghi chú**: Computational Complexity là nền tảng lý thuyết của khoa học máy tính, giúp hiểu giới hạn và khả năng của computation. Việc nắm vững các khái niệm này rất quan trọng cho việc thiết kế algorithms hiệu quả!
