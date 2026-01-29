# Đề Tài 11: Sorting Algorithms - Thuật Toán Sắp Xếp

## 1. Giới Thiệu Về Thuật Toán Sắp Xếp

### 1.1 Khái Niệm Cơ Bản

**Sắp xếp** (Sorting) là một trong những bài toán cơ bản và quan trọng nhất trong khoa học máy tính. Mục tiêu là sắp xếp lại các phần tử trong một dãy theo một thứ tự nhất định (tăng dần hoặc giảm dần).

**Tại sao sắp xếp quan trọng?**
- **Tìm kiếm hiệu quả**: Dữ liệu đã sắp xếp cho phép tìm kiếm nhị phân O(log n)
- **Tiền xử lý**: Nhiều thuật toán yêu cầu dữ liệu đã được sắp xếp
- **Tối ưu hóa**: Giúp tối ưu hóa nhiều bài toán khác
- **Phân tích dữ liệu**: Dễ dàng tìm median, quartiles, outliers

### 1.2 Phân Loại Thuật Toán Sắp Xếp

**Theo độ phức tạp thời gian:**
- **O(n²)**: Bubble Sort, Selection Sort, Insertion Sort
- **O(n log n)**: Merge Sort, Heap Sort, Quick Sort (trung bình)
- **O(n)**: Counting Sort, Radix Sort, Bucket Sort (với điều kiện)

**Theo tính ổn định (Stability):**
- **Stable**: Giữ nguyên thứ tự tương đối của các phần tử bằng nhau
- **Unstable**: Có thể thay đổi thứ tự tương đối

**Theo sử dụng bộ nhớ:**
- **In-place**: Sử dụng O(1) bộ nhớ phụ
- **Out-of-place**: Cần O(n) bộ nhớ phụ

## 2. Các Thuật Toán Sắp Xếp Cơ Bản O(n²)

### 2.1 Bubble Sort

**Ý tưởng**: So sánh từng cặp phần tử liền kề và hoán đổi nếu chúng không đúng thứ tự.

```cpp
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Tối ưu: nếu không có hoán đổi nào, mảng đã sắp xếp
        if (!swapped) break;
    }
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n²) worst case, O(n) best case
- **Tính ổn định**: Stable
- **Bộ nhớ**: In-place O(1)
- **Ưu điểm**: Đơn giản, phát hiện mảng đã sắp xếp
- **Nhược điểm**: Chậm với dữ liệu lớn

### 2.2 Selection Sort

**Ý tưởng**: Tìm phần tử nhỏ nhất và đặt vào vị trí đầu, lặp lại với phần còn lại.

```cpp
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n²) trong mọi trường hợp
- **Tính ổn định**: Unstable
- **Bộ nhớ**: In-place O(1)
- **Ưu điểm**: Ít hoán đổi nhất (O(n))
- **Nhược điểm**: Luôn O(n²) dù mảng đã sắp xếp

### 2.3 Insertion Sort

**Ý tưởng**: Chèn từng phần tử vào vị trí đúng trong phần đã sắp xếp.

```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Di chuyển các phần tử lớn hơn key về phía sau
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n²) worst case, O(n) best case
- **Tính ổn định**: Stable
- **Bộ nhớ**: In-place O(1)
- **Ưu điểm**: Hiệu quả với mảng nhỏ hoặc gần như đã sắp xếp
- **Nhược điểm**: Chậm với dữ liệu lớn

## 3. Thuật Toán Sắp Xếp Nâng Cao O(n log n)

### 3.1 Merge Sort

**Ý tưởng**: Chia để trị - chia mảng thành hai nửa, sắp xếp từng nửa, rồi trộn lại.

```cpp
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    // Copy dữ liệu vào mảng tạm
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Trộn hai mảng con
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy phần tử còn lại
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n log n) trong mọi trường hợp
- **Tính ổn định**: Stable
- **Bộ nhớ**: O(n) cho mảng tạm
- **Ưu điểm**: Hiệu suất ổn định, stable
- **Nhược điểm**: Cần bộ nhớ phụ

### 3.2 Quick Sort

**Ý tưởng**: Chọn một pivot, phân hoạch mảng thành hai phần, sắp xếp đệ quy.

```cpp
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Chọn phần tử cuối làm pivot
    int i = low - 1; // Chỉ số của phần tử nhỏ hơn
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Phiên bản tối ưu với random pivot
int randomizedPartition(vector<int>& arr, int low, int high) {
    srand(time(nullptr));
    int random = low + rand() % (high - low + 1);
    swap(arr[random], arr[high]);
    return partition(arr, low, high);
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n log n) trung bình, O(n²) worst case
- **Tính ổn định**: Unstable
- **Bộ nhớ**: O(log n) cho stack đệ quy
- **Ưu điểm**: Nhanh trong thực tế, in-place
- **Nhược điểm**: Worst case O(n²)

### 3.3 Heap Sort

**Ý tưởng**: Xây dựng max heap, lần lượt lấy phần tử lớn nhất ra khỏi heap.

```cpp
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Root
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // Nếu con trái lớn hơn root
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    // Nếu con phải lớn hơn largest hiện tại
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // Nếu largest không phải root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Xây dựng heap (sắp xếp lại mảng)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Lần lượt lấy phần tử từ heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Di chuyển root hiện tại về cuối
        heapify(arr, i, 0); // Gọi heapify trên heap đã giảm
    }
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n log n) trong mọi trường hợp
- **Tính ổn định**: Unstable
- **Bộ nhớ**: In-place O(1)
- **Ưu điểm**: Hiệu suất ổn định, in-place
- **Nhược điểm**: Không stable, hằng số lớn

## 4. Thuật Toán Sắp Xếp Đặc Biệt

### 4.1 Counting Sort

**Ý tưởng**: Đếm số lần xuất hiện của mỗi giá trị, phù hợp khi phạm vi giá trị nhỏ.

```cpp
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    vector<int> count(range, 0);
    vector<int> output(arr.size());
    
    // Đếm số lần xuất hiện
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - minVal]++;
    
    // Tính tổng tích lũy
    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];
    
    // Xây dựng mảng kết quả
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    // Copy kết quả về mảng gốc
    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n + k) với k là phạm vi giá trị
- **Tính ổn định**: Stable
- **Bộ nhớ**: O(k) cho mảng đếm
- **Ưu điểm**: Rất nhanh khi k nhỏ
- **Nhược điểm**: Không hiệu quả khi k lớn

### 4.2 Radix Sort

**Ý tưởng**: Sắp xếp theo từng chữ số, từ chữ số ít quan trọng nhất.

```cpp
int getMax(vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);
    
    // Đếm số lần xuất hiện của mỗi chữ số
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    // Tính tổng tích lũy
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Xây dựng mảng kết quả
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copy kết quả về mảng gốc
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int maxVal = getMax(arr);
    
    // Sắp xếp theo từng chữ số
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortForRadix(arr, exp);
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(d × (n + k)) với d là số chữ số
- **Tính ổn định**: Stable
- **Bộ nhớ**: O(n + k)
- **Ưu điểm**: Hiệu quả với số nguyên
- **Nhược điểm**: Chỉ áp dụng được với một số kiểu dữ liệu

### 4.3 Bucket Sort

**Ý tưởng**: Phân phối các phần tử vào các bucket, sắp xếp từng bucket.

```cpp
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 0) return;
    
    // Tạo n bucket rỗng
    vector<vector<float>> buckets(n);
    
    // Phân phối các phần tử vào bucket
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i]; // Giả sử arr[i] trong [0, 1)
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // Sắp xếp từng bucket
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // Nối các bucket lại
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}
```

**Đặc điểm:**
- **Độ phức tạp**: O(n + k) trung bình, O(n²) worst case
- **Tính ổn định**: Stable (nếu thuật toán sắp xếp bucket stable)
- **Bộ nhớ**: O(n × k)
- **Ưu điểm**: Rất nhanh khi dữ liệu phân bố đều
- **Nhược điểm**: Hiệu suất phụ thuộc vào phân bố dữ liệu

## 5. So Sánh và Lựa Chọn Thuật Toán

### 5.1 Bảng So Sánh Tổng Quan

| Thuật toán | Best Case | Average Case | Worst Case | Space | Stable | In-place |
|------------|-----------|--------------|------------|-------|--------|----------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | ✓ | ✓ |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | ✗ | ✓ |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | ✓ | ✓ |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | ✓ | ✗ |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | ✗ | ✓ |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | ✗ | ✓ |
| Counting Sort | O(n + k) | O(n + k) | O(n + k) | O(k) | ✓ | ✗ |
| Radix Sort | O(d(n + k)) | O(d(n + k)) | O(d(n + k)) | O(n + k) | ✓ | ✗ |
| Bucket Sort | O(n + k) | O(n + k) | O(n²) | O(n) | ✓ | ✗ |

### 5.2 Hướng Dẫn Lựa Chọn

**Khi nào sử dụng thuật toán nào?**

**Bubble Sort:**
- Mảng rất nhỏ (< 10 phần tử)
- Mục đích giáo dục
- Cần phát hiện mảng đã sắp xếp

**Selection Sort:**
- Mảng nhỏ
- Muốn tối thiểu số lần hoán đổi
- Bộ nhớ hạn chế

**Insertion Sort:**
- Mảng nhỏ hoặc gần như đã sắp xếp
- Sắp xếp online (thêm phần tử vào mảng đã sắp xếp)
- Hybrid sort (kết hợp với Quick Sort)

**Merge Sort:**
- Cần stable sort
- Dữ liệu lớn
- Hiệu suất ổn định quan trọng
- Linked list

**Quick Sort:**
- Mảng lớn
- Bộ nhớ hạn chế
- Hiệu suất trung bình quan trọng hơn worst case

**Heap Sort:**
- Cần O(n log n) guaranteed
- Bộ nhớ hạn chế
- Không cần stable

**Counting Sort:**
- Phạm vi giá trị nhỏ
- Cần stable sort
- Số nguyên không âm

**Radix Sort:**
- Số nguyên hoặc chuỗi có độ dài cố định
- Cần stable sort
- Phạm vi chữ số nhỏ

**Bucket Sort:**
- Dữ liệu phân bố đều
- Số thực trong khoảng [0, 1)
- Có thể song song hóa

## 6. Tối Ưu Hóa và Kỹ Thuật Nâng Cao

### 6.1 Hybrid Sorting

**Introsort** (Introspective Sort):
```cpp
void introsort(vector<int>& arr, int low, int high, int depthLimit) {
    if (high - low < 16) {
        // Sử dụng Insertion Sort cho mảng nhỏ
        insertionSort(arr, low, high);
    } else if (depthLimit == 0) {
        // Chuyển sang Heap Sort khi đệ quy quá sâu
        heapSort(arr, low, high);
    } else {
        // Sử dụng Quick Sort
        int pivot = partition(arr, low, high);
        introsort(arr, low, pivot - 1, depthLimit - 1);
        introsort(arr, pivot + 1, high, depthLimit - 1);
    }
}
```

### 6.2 Parallel Sorting

**Merge Sort song song:**
```cpp
void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sử dụng thread cho các nửa
        thread leftThread([&]() { parallelMergeSort(arr, left, mid); });
        thread rightThread([&]() { parallelMergeSort(arr, mid + 1, right); });
        
        leftThread.join();
        rightThread.join();
        
        merge(arr, left, mid, right);
    }
}
```

### 6.3 External Sorting

**Sắp xếp file lớn:**
```cpp
void externalMergeSort(string inputFile, string outputFile, int memoryLimit) {
    // Phase 1: Chia file thành các chunk nhỏ và sắp xếp
    vector<string> tempFiles;
    ifstream input(inputFile);
    int chunkSize = memoryLimit / sizeof(int);
    
    vector<int> chunk(chunkSize);
    int fileCount = 0;
    
    while (input.read(reinterpret_cast<char*>(chunk.data()), 
                      chunkSize * sizeof(int))) {
        sort(chunk.begin(), chunk.end());
        
        string tempFile = "temp_" + to_string(fileCount++) + ".dat";
        ofstream temp(tempFile, ios::binary);
        temp.write(reinterpret_cast<char*>(chunk.data()), 
                   chunkSize * sizeof(int));
        temp.close();
        tempFiles.push_back(tempFile);
    }
    
    // Phase 2: Merge các file đã sắp xếp
    multiWayMerge(tempFiles, outputFile);
    
    // Cleanup
    for (const string& file : tempFiles) {
        remove(file.c_str());
    }
}
```

## 7. Ứng Dụng Thực Tế

### 7.1 Database Systems

**B+ Tree Index:**
```cpp
class BPlusTreeNode {
    vector<int> keys;
    vector<BPlusTreeNode*> children;
    bool isLeaf;
    
public:
    void insertKey(int key) {
        // Tìm vị trí chèn bằng binary search
        auto pos = lower_bound(keys.begin(), keys.end(), key);
        keys.insert(pos, key);
        
        // Maintain sorted order for efficient range queries
    }
};
```

### 7.2 Search Engines

**Inverted Index Sorting:**
```cpp
struct DocumentScore {
    int docId;
    double score;
    
    bool operator<(const DocumentScore& other) const {
        return score > other.score; // Sort by score descending
    }
};

vector<DocumentScore> rankDocuments(const vector<DocumentScore>& docs) {
    vector<DocumentScore> ranked = docs;
    
    // Sử dụng partial_sort nếu chỉ cần top-k
    partial_sort(ranked.begin(), ranked.begin() + 10, ranked.end());
    
    return ranked;
}
```

### 7.3 Graphics và Game Development

**Z-Buffer Sorting:**
```cpp
struct Triangle {
    Point3D vertices[3];
    double zDepth;
    
    bool operator<(const Triangle& other) const {
        return zDepth > other.zDepth; // Back to front
    }
};

void renderScene(vector<Triangle>& triangles) {
    // Sort triangles by depth for proper rendering
    sort(triangles.begin(), triangles.end());
    
    for (const auto& triangle : triangles) {
        renderTriangle(triangle);
    }
}
```

## 8. Kết Luận

### 8.1 Tầm Quan Trọng của Sorting

Thuật toán sắp xếp là nền tảng của nhiều thuật toán khác:
- **Tìm kiếm**: Binary search yêu cầu dữ liệu đã sắp xếp
- **Thuật toán tham lam**: Nhiều bài toán greedy cần sắp xếp trước
- **Xử lý dữ liệu**: Statistics, analytics, reporting
- **Tối ưu hóa**: Scheduling, resource allocation

### 8.2 Xu Hướng Phát Triển

**Parallel và Distributed Sorting:**
- GPU-based sorting
- MapReduce sorting
- Distributed merge sort

**Adaptive Sorting:**
- Thuật toán tự điều chỉnh theo đặc điểm dữ liệu
- Machine learning-guided sorting

**Specialized Sorting:**
- String sorting algorithms
- Multi-key sorting
- Approximate sorting

### 8.3 Lời Khuyên Thực Tế

1. **Hiểu rõ dữ liệu**: Kích thước, phân bố, đặc điểm
2. **Chọn thuật toán phù hợp**: Dựa trên yêu cầu cụ thể
3. **Tối ưu hóa**: Hybrid approaches, cache-friendly implementations
4. **Kiểm tra hiệu suất**: Benchmark với dữ liệu thực tế
5. **Sử dụng thư viện**: std::sort, std::stable_sort khi có thể

---

**"Sorting is the most fundamental algorithmic problem in computer science. Master it, and you master the art of algorithm design."**

## Tài Liệu Tham Khảo

1. **Sách giáo khoa:**
   - "Introduction to Algorithms" - CLRS
   - "The Art of Computer Programming, Volume 3" - Donald Knuth
   - "Algorithms" - Robert Sedgewick

2. **Tài nguyên trực tuyến:**
   - [VNOI Wiki - Sorting](https://wiki.vnoi.info/algo/basic/sorting)
   - [Sorting Algorithms Visualization](https://www.sortvisualizer.com/)
   - [Big-O Cheat Sheet](https://www.bigocheatsheet.com/)

3. **Research Papers:**
   - "Engineering a Sort Function" - Bentley & McIlroy
   - "Introspective Sorting and Selection Algorithms" - Musser

---

**Ngày hoàn thành**: [Ngày tháng năm]  
**Tác giả**: [Tên tác giả]  
**Phiên bản**: 1.0