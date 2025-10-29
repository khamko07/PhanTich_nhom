# Đề Tài 12: Computational Complexity - Độ Phức Tạp Tính Toán

## 1. Giới Thiệu Về Độ Phức Tạp Tính Toán

### 1.1 Khái Niệm Cơ Bản

**Độ phức tạp tính toán** (Computational Complexity) là một lĩnh vực quan trọng trong khoa học máy tính, nghiên cứu về lượng tài nguyên cần thiết để giải quyết các bài toán tính toán. Hai loại tài nguyên chính được quan tâm là:

- **Thời gian** (Time Complexity): Số bước tính toán cần thiết
- **Không gian** (Space Complexity): Lượng bộ nhớ cần thiết

### 1.2 Tại Sao Cần Nghiên Cứu Độ Phức Tạp?

```cpp
// Ví dụ: Tìm kiếm trong mảng
// Approach 1: Linear Search - O(n)
bool linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return true;
    }
    return false;
}

// Approach 2: Binary Search - O(log n) - Yêu cầu mảng đã sắp xếp
bool binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return true;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}
```

**Sự khác biệt**: Với mảng 1 triệu phần tử, linear search cần tối đa 1 triệu phép so sánh, trong khi binary search chỉ cần tối đa 20 phép so sánh!

## 2. Ký Hiệu Big O và Các Khái Niệm Liên Quan

### 2.1 Big O Notation (Ký Hiệu O Lớn)

**Định nghĩa**: f(n) = O(g(n)) nếu tồn tại các hằng số dương c và n₀ sao cho:
f(n) ≤ c × g(n) với mọi n ≥ n₀

```cpp
// Ví dụ phân tích Big O
void example1(int n) {
    for (int i = 0; i < n; i++) {        // O(n)
        cout << i << " ";
    }
}
// Time Complexity: O(n)

void example2(int n) {
    for (int i = 0; i < n; i++) {        // O(n)
        for (int j = 0; j < n; j++) {    // O(n)
            cout << i << "," << j << " ";
        }
    }
}
// Time Complexity: O(n²)

void example3(int n) {
    for (int i = 1; i < n; i *= 2) {     // O(log n)
        cout << i << " ";
    }
}
// Time Complexity: O(log n)
```

### 2.2 Các Ký Hiệu Khác

**Big Omega (Ω)**: Cận dưới
- f(n) = Ω(g(n)) nếu g(n) = O(f(n))

**Big Theta (Θ)**: Cận chặt
- f(n) = Θ(g(n)) nếu f(n) = O(g(n)) và f(n) = Ω(g(n))

**Little o**: Cận trên không chặt
- f(n) = o(g(n)) nếu lim(n→∞) f(n)/g(n) = 0

```cpp
// Ví dụ về các ký hiệu
void analyzeComplexity() {
    // f(n) = 3n² + 2n + 1
    // f(n) = O(n²)     - Cận trên
    // f(n) = Ω(n²)     - Cận dưới  
    // f(n) = Θ(n²)     - Cận chặt
    // f(n) = o(n³)     - Cận trên không chặt
}
```

## 3. Phân Tích Độ Phức Tạp Thời Gian

### 3.1 Các Trường Hợp Phân Tích

```cpp
class ComplexityAnalysis {
public:
    // Best Case: O(1) - Tìm thấy ngay phần tử đầu
    // Average Case: O(n/2) = O(n) - Tìm thấy ở giữa
    // Worst Case: O(n) - Tìm thấy ở cuối hoặc không tìm thấy
    int linearSearch(vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }
    
    // Phân tích Quick Sort
    void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);    // T(k)
            quickSort(arr, pi + 1, high);   // T(n-k-1)
        }
    }
    // Best/Average Case: O(n log n) - Pivot chia đều
    // Worst Case: O(n²) - Pivot luôn là min/max
    
private:
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};
```

### 3.2 Phương Pháp Phân Tích

**1. Đếm Phép Toán Cơ Bản**
```cpp
void countOperations(int n) {
    int count = 0;
    
    // Loop 1: n iterations
    for (int i = 0; i < n; i++) {
        count++;  // 1 operation per iteration
    }
    // Total: n operations
    
    // Loop 2: n² iterations  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count++;  // 1 operation per iteration
        }
    }
    // Total: n² operations
    
    // Overall: O(n + n²) = O(n²)
}
```

**2. Phương Pháp Đệ Quy (Master Theorem)**
```cpp
// T(n) = aT(n/b) + f(n)
// Ví dụ: Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);      // T(n/2)
        mergeSort(arr, mid + 1, right); // T(n/2)
        merge(arr, left, mid, right);   // O(n)
    }
}
// T(n) = 2T(n/2) + O(n) = O(n log n)
```

## 4. Phân Tích Độ Phức Tạp Không Gian

### 4.1 Các Loại Không Gian

```cpp
class SpaceComplexity {
public:
    // O(1) - Constant Space
    int findMax(vector<int>& arr) {
        int maxVal = arr[0];  // 1 variable
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }
        return maxVal;
    }
    
    // O(n) - Linear Space
    vector<int> createCopy(vector<int>& arr) {
        vector<int> copy = arr;  // n space
        return copy;
    }
    
    // O(log n) - Logarithmic Space (Recursive call stack)
    int binarySearchRecursive(vector<int>& arr, int target, int left, int right) {
        if (left > right) return -1;
        
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        
        if (arr[mid] > target) {
            return binarySearchRecursive(arr, target, left, mid - 1);
        } else {
            return binarySearchRecursive(arr, target, mid + 1, right);
        }
    }
    // Call stack depth: O(log n)
    
    // O(n²) - Quadratic Space
    vector<vector<int>> create2DArray(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        return matrix;  // n × n space
    }
};
```

### 4.2 Auxiliary Space vs Total Space

```cpp
void spaceAnalysisExample() {
    vector<int> input(1000);  // Input space: O(n)
    
    // Auxiliary space analysis:
    
    // Method 1: In-place sorting
    sort(input.begin(), input.end());  // Auxiliary: O(log n)
    // Total space: O(n + log n) = O(n)
    
    // Method 2: Create new sorted array
    vector<int> sorted = input;        // Auxiliary: O(n)
    sort(sorted.begin(), sorted.end());
    // Total space: O(n + n) = O(n)
}
```

## 5. Các Lớp Độ Phức Tạp Quan Trọng

### 5.1 Thứ Tự Tăng Dần Của Các Hàm Độ Phức Tạp

```
O(1) < O(log log n) < O(log n) < O(n^(1/3)) < O(n^(1/2)) < O(n) < 
O(n log n) < O(n²) < O(n³) < O(2^n) < O(n!) < O(n^n)
```

### 5.2 Ví Dụ Thực Tế

```cpp
class ComplexityExamples {
public:
    // O(1) - Constant Time
    int getFirstElement(vector<int>& arr) {
        return arr[0];
    }
    
    // O(log n) - Logarithmic Time
    int binarySearch(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;
            if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
    
    // O(n) - Linear Time
    int findSum(vector<int>& arr) {
        int sum = 0;
        for (int x : arr) {
            sum += x;
        }
        return sum;
    }
    
    // O(n log n) - Linearithmic Time
    void mergeSort(vector<int>& arr) {
        if (arr.size() <= 1) return;
        
        int mid = arr.size() / 2;
        vector<int> left(arr.begin(), arr.begin() + mid);
        vector<int> right(arr.begin() + mid, arr.end());
        
        mergeSort(left);
        mergeSort(right);
        merge(arr, left, right);
    }
    
    // O(n²) - Quadratic Time
    void bubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    
    // O(2^n) - Exponential Time
    int fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    // O(n!) - Factorial Time
    void generatePermutations(vector<int>& arr, int start, vector<vector<int>>& result) {
        if (start == arr.size()) {
            result.push_back(arr);
            return;
        }
        
        for (int i = start; i < arr.size(); i++) {
            swap(arr[start], arr[i]);
            generatePermutations(arr, start + 1, result);
            swap(arr[start], arr[i]);  // backtrack
        }
    }
    
private:
    void merge(vector<int>& arr, vector<int>& left, vector<int>& right) {
        int i = 0, j = 0, k = 0;
        
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }
        
        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }
};
```

## 6. Amortized Analysis (Phân Tích Khấu Hao)

### 6.1 Khái Niệm

**Amortized Analysis** là phương pháp phân tích độ phức tạp trung bình của một chuỗi operations, thay vì phân tích từng operation riêng lẻ.

```cpp
class DynamicArray {
private:
    int* arr;
    int size;
    int capacity;
    
public:
    DynamicArray() : size(0), capacity(1) {
        arr = new int[capacity];
    }
    
    // Amortized O(1) - Mặc dù worst case là O(n)
    void push_back(int value) {
        if (size == capacity) {
            // Resize: O(n) - Happens rarely
            capacity *= 2;
            int* newArr = new int[capacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        
        arr[size++] = value;  // O(1) - Happens always
    }
    
    ~DynamicArray() {
        delete[] arr;
    }
};

// Phân tích Amortized:
// - n operations push_back
// - Resize xảy ra tại: 1, 2, 4, 8, 16, ..., 2^k ≤ n
// - Tổng cost resize: 1 + 2 + 4 + ... + 2^k ≤ 2n
// - Tổng cost: 2n + n = 3n
// - Amortized cost per operation: 3n/n = O(1)
```

### 6.2 Các Phương Pháp Amortized Analysis

**1. Aggregate Method**
```cpp
// Ví dụ: Binary Counter
class BinaryCounter {
private:
    vector<bool> bits;
    
public:
    BinaryCounter(int n) : bits(n, false) {}
    
    void increment() {
        int i = 0;
        while (i < bits.size() && bits[i]) {
            bits[i] = false;  // Flip from 1 to 0
            i++;
        }
        if (i < bits.size()) {
            bits[i] = true;   // Set first 0 to 1
        }
    }
};

// Aggregate Analysis:
// - n increments
// - Bit 0 flips n times
// - Bit 1 flips n/2 times  
// - Bit 2 flips n/4 times
// - Total flips: n + n/2 + n/4 + ... < 2n
// - Amortized cost: 2n/n = O(1)
```

**2. Accounting Method**
```cpp
// Ví dụ: Stack with MultiPop
class StackWithMultiPop {
private:
    vector<int> stack;
    
public:
    // Cost: 1, Charge: 2 (1 for push, 1 credit for future pop)
    void push(int x) {
        stack.push_back(x);
    }
    
    // Cost: 1, Charge: 0 (use credit from push)
    int pop() {
        if (!stack.empty()) {
            int val = stack.back();
            stack.pop_back();
            return val;
        }
        return -1;
    }
    
    // Cost: min(k, size), Charge: 0 (use credits)
    void multiPop(int k) {
        while (k > 0 && !stack.empty()) {
            pop();
            k--;
        }
    }
};
```

## 7. Complexity Classes trong Computer Science

### 7.1 P vs NP Problem

```cpp
// P Class: Polynomial Time Solvable
class PProblems {
public:
    // Sorting: O(n log n)
    void sort(vector<int>& arr) {
        sort(arr.begin(), arr.end());
    }
    
    // Shortest Path: O(V² + E)
    vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start) {
        int n = graph.size();
        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            for (auto& edge : graph[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
};

// NP Class: Nondeterministic Polynomial Time
class NPProblems {
public:
    // Traveling Salesman Problem - Brute Force: O(n!)
    int tsp(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> cities;
        for (int i = 1; i < n; i++) {
            cities.push_back(i);
        }
        
        int minCost = INT_MAX;
        
        do {
            int cost = graph[0][cities[0]];
            for (int i = 0; i < cities.size() - 1; i++) {
                cost += graph[cities[i]][cities[i + 1]];
            }
            cost += graph[cities.back()][0];
            
            minCost = min(minCost, cost);
        } while (next_permutation(cities.begin(), cities.end()));
        
        return minCost;
    }
    
    // Subset Sum Problem - Dynamic Programming: O(n × sum)
    bool subsetSum(vector<int>& arr, int target) {
        int n = arr.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= arr[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i - 1]];
                }
            }
        }
        
        return dp[n][target];
    }
};
```

### 7.2 Approximation Algorithms

```cpp
// Khi không thể giải chính xác trong thời gian polynomial
class ApproximationAlgorithms {
public:
    // Vertex Cover - 2-approximation
    vector<int> vertexCover(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> covered(n, false);
        vector<int> cover;
        
        for (int u = 0; u < n; u++) {
            if (!covered[u]) {
                for (int v : graph[u]) {
                    if (!covered[v]) {
                        cover.push_back(u);
                        cover.push_back(v);
                        covered[u] = covered[v] = true;
                        break;
                    }
                }
            }
        }
        
        return cover;
    }
    
    // TSP - 2-approximation using MST
    vector<int> tspApprox(vector<vector<int>>& graph) {
        int n = graph.size();
        
        // 1. Find MST
        vector<vector<int>> mst = findMST(graph);
        
        // 2. DFS traversal of MST
        vector<bool> visited(n, false);
        vector<int> tour;
        
        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            tour.push_back(u);
            
            for (int v : mst[u]) {
                if (!visited[v]) {
                    dfs(v);
                }
            }
        };
        
        dfs(0);
        tour.push_back(0);  // Return to start
        
        return tour;
    }
    
private:
    vector<vector<int>> findMST(vector<vector<int>>& graph) {
        // Prim's algorithm implementation
        int n = graph.size();
        vector<vector<int>> mst(n);
        vector<bool> inMST(n, false);
        vector<int> key(n, INT_MAX);
        vector<int> parent(n, -1);
        
        key[0] = 0;
        
        for (int count = 0; count < n - 1; count++) {
            int u = -1;
            for (int v = 0; v < n; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }
            
            inMST[u] = true;
            
            for (int v = 0; v < n; v++) {
                if (!inMST[v] && graph[u][v] < key[v]) {
                    key[v] = graph[u][v];
                    parent[v] = u;
                }
            }
        }
        
        for (int i = 1; i < n; i++) {
            mst[parent[i]].push_back(i);
            mst[i].push_back(parent[i]);
        }
        
        return mst;
    }
};
```

## 8. Practical Complexity Analysis

### 8.1 Profiling và Measurement

```cpp
#include <chrono>

class PerformanceMeasurement {
public:
    template<typename Func>
    static double measureTime(Func func) {
        auto start = chrono::high_resolution_clock::now();
        func();
        auto end = chrono::high_resolution_clock::now();
        
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        return duration.count() / 1000.0;  // milliseconds
    }
    
    static void compareAlgorithms() {
        vector<int> sizes = {100, 1000, 10000, 100000};
        
        cout << "Size\t\tBubble Sort\tQuick Sort\tMerge Sort" << endl;
        cout << "----\t\t-----------\t----------\t----------" << endl;
        
        for (int n : sizes) {
            vector<int> arr1 = generateRandomArray(n);
            vector<int> arr2 = arr1;
            vector<int> arr3 = arr1;
            
            double bubbleTime = measureTime([&]() {
                bubbleSort(arr1);
            });
            
            double quickTime = measureTime([&]() {
                quickSort(arr2, 0, arr2.size() - 1);
            });
            
            double mergeTime = measureTime([&]() {
                mergeSort(arr3);
            });
            
            cout << n << "\t\t" << bubbleTime << "\t\t" 
                 << quickTime << "\t\t" << mergeTime << endl;
        }
    }
    
private:
    static vector<int> generateRandomArray(int n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }
        return arr;
    }
    
    static void bubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    static void mergeSort(vector<int>& arr) {
        if (arr.size() <= 1) return;
        
        int mid = arr.size() / 2;
        vector<int> left(arr.begin(), arr.begin() + mid);
        vector<int> right(arr.begin() + mid, arr.end());
        
        mergeSort(left);
        mergeSort(right);
        
        int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }
        
        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }
};
```

### 8.2 Memory Profiling

```cpp
class MemoryAnalysis {
public:
    static void analyzeMemoryUsage() {
        cout << "=== MEMORY USAGE ANALYSIS ===" << endl;
        
        // Test different data structures
        testVector();
        testList();
        testMap();
        testSet();
        
        cout << "=============================" << endl;
    }
    
private:
    static void testVector() {
        cout << "Vector memory usage:" << endl;
        
        for (int n : {1000, 10000, 100000}) {
            vector<int> vec(n);
            
            size_t memoryUsed = vec.capacity() * sizeof(int);
            cout << "Size " << n << ": " << memoryUsed << " bytes" << endl;
        }
        cout << endl;
    }
    
    static void testList() {
        cout << "List memory usage:" << endl;
        
        for (int n : {1000, 10000, 100000}) {
            list<int> lst;
            for (int i = 0; i < n; i++) {
                lst.push_back(i);
            }
            
            // Approximate memory: n * (sizeof(int) + 2 * sizeof(pointer))
            size_t memoryUsed = n * (sizeof(int) + 2 * sizeof(void*));
            cout << "Size " << n << ": ~" << memoryUsed << " bytes" << endl;
        }
        cout << endl;
    }
    
    static void testMap() {
        cout << "Map memory usage:" << endl;
        
        for (int n : {1000, 10000, 100000}) {
            map<int, int> mp;
            for (int i = 0; i < n; i++) {
                mp[i] = i;
            }
            
            // Approximate memory for Red-Black Tree
            size_t memoryUsed = n * (2 * sizeof(int) + 3 * sizeof(void*) + sizeof(bool));
            cout << "Size " << n << ": ~" << memoryUsed << " bytes" << endl;
        }
        cout << endl;
    }
    
    static void testSet() {
        cout << "Set memory usage:" << endl;
        
        for (int n : {1000, 10000, 100000}) {
            set<int> st;
            for (int i = 0; i < n; i++) {
                st.insert(i);
            }
            
            // Approximate memory for Red-Black Tree
            size_t memoryUsed = n * (sizeof(int) + 3 * sizeof(void*) + sizeof(bool));
            cout << "Size " << n << ": ~" << memoryUsed << " bytes" << endl;
        }
        cout << endl;
    }
};
```

## 9. Optimization Techniques

### 9.1 Algorithmic Optimizations

```cpp
class OptimizationTechniques {
public:
    // Memoization - Tối ưu từ O(2^n) xuống O(n)
    int fibonacciMemo(int n, vector<int>& memo) {
        if (n <= 1) return n;
        
        if (memo[n] != -1) return memo[n];
        
        memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
        return memo[n];
    }
    
    // Bottom-up DP - Tối ưu space từ O(n) xuống O(1)
    int fibonacciOptimal(int n) {
        if (n <= 1) return n;
        
        int prev2 = 0, prev1 = 1;
        for (int i = 2; i <= n; i++) {
            int current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
    
    // Early termination
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        
        // Chỉ kiểm tra đến √n
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        
        return true;
    }
    
    // Preprocessing - Sieve of Eratosthenes
    vector<bool> sieveOfEratosthenes(int n) {
        vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false;
        
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        
        return isPrime;
    }
};
```

### 9.2 Data Structure Optimizations

```cpp
class DataStructureOptimizations {
public:
    // Fenwick Tree - Range sum queries in O(log n)
    class FenwickTree {
    private:
        vector<int> tree;
        int n;
        
    public:
        FenwickTree(int size) : n(size) {
            tree.assign(n + 1, 0);
        }
        
        void update(int idx, int delta) {
            for (++idx; idx <= n; idx += idx & -idx) {
                tree[idx] += delta;
            }
        }
        
        int query(int idx) {
            int sum = 0;
            for (++idx; idx > 0; idx -= idx & -idx) {
                sum += tree[idx];
            }
            return sum;
        }
        
        int rangeQuery(int left, int right) {
            return query(right) - (left > 0 ? query(left - 1) : 0);
        }
    };
    
    // Segment Tree - Range queries with updates
    class SegmentTree {
    private:
        vector<int> tree;
        int n;
        
        void build(vector<int>& arr, int node, int start, int end) {
            if (start == end) {
                tree[node] = arr[start];
            } else {
                int mid = (start + end) / 2;
                build(arr, 2 * node, start, mid);
                build(arr, 2 * node + 1, mid + 1, end);
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }
        
        void updateHelper(int node, int start, int end, int idx, int val) {
            if (start == end) {
                tree[node] = val;
            } else {
                int mid = (start + end) / 2;
                if (idx <= mid) {
                    updateHelper(2 * node, start, mid, idx, val);
                } else {
                    updateHelper(2 * node + 1, mid + 1, end, idx, val);
                }
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }
        
        int queryHelper(int node, int start, int end, int l, int r) {
            if (r < start || end < l) {
                return 0;
            }
            if (l <= start && end <= r) {
                return tree[node];
            }
            int mid = (start + end) / 2;
            return queryHelper(2 * node, start, mid, l, r) +
                   queryHelper(2 * node + 1, mid + 1, end, l, r);
        }
        
    public:
        SegmentTree(vector<int>& arr) {
            n = arr.size();
            tree.assign(4 * n, 0);
            build(arr, 1, 0, n - 1);
        }
        
        void update(int idx, int val) {
            updateHelper(1, 0, n - 1, idx, val);
        }
        
        int query(int l, int r) {
            return queryHelper(1, 0, n - 1, l, r);
        }
    };
};
```

## 10. Kết Luận và Ứng Dụng Thực Tế

### 10.1 Tầm Quan Trọng Trong Thực Tế

```cpp
// Ví dụ: Tối ưu hóa trong hệ thống thực tế
class RealWorldOptimization {
public:
    // Database Query Optimization
    // Thay vì O(n²) nested loops, sử dụng hash join O(n + m)
    vector<pair<int, int>> hashJoin(vector<pair<int, string>>& table1,
                                   vector<pair<int, string>>& table2) {
        unordered_map<int, string> hashTable;
        
        // Build phase: O(n)
        for (auto& row : table1) {
            hashTable[row.first] = row.second;
        }
        
        vector<pair<int, int>> result;
        
        // Probe phase: O(m)
        for (auto& row : table2) {
            if (hashTable.count(row.first)) {
                result.push_back({row.first, row.first});
            }
        }
        
        return result;  // Total: O(n + m) instead of O(n × m)
    }
    
    // Web Search - Inverted Index
    class SearchEngine {
    private:
        unordered_map<string, vector<int>> invertedIndex;
        
    public:
        void buildIndex(vector<string>& documents) {
            for (int docId = 0; docId < documents.size(); docId++) {
                istringstream iss(documents[docId]);
                string word;
                
                while (iss >> word) {
                    // Convert to lowercase and remove punctuation
                    transform(word.begin(), word.end(), word.begin(), ::tolower);
                    invertedIndex[word].push_back(docId);
                }
            }
        }
        
        vector<int> search(string query) {
            transform(query.begin(), query.end(), query.begin(), ::tolower);
            
            if (invertedIndex.count(query)) {
                return invertedIndex[query];  // O(1) lookup instead of O(n) scan
            }
            
            return {};
        }
    };
};
```

### 10.2 Guidelines for Algorithm Selection

```cpp
class AlgorithmSelection {
public:
    static void printGuidelines() {
        cout << "=== ALGORITHM SELECTION GUIDELINES ===" << endl;
        
        cout << "\n1. Sorting Algorithms:" << endl;
        cout << "   - Small arrays (n < 50): Insertion Sort" << endl;
        cout << "   - General purpose: Quick Sort or Merge Sort" << endl;
        cout << "   - Stable sort needed: Merge Sort" << endl;
        cout << "   - Memory constrained: Heap Sort" << endl;
        cout << "   - Integer range limited: Counting/Radix Sort" << endl;
        
        cout << "\n2. Search Algorithms:" << endl;
        cout << "   - Unsorted data: Linear Search O(n)" << endl;
        cout << "   - Sorted data: Binary Search O(log n)" << endl;
        cout << "   - Frequent searches: Hash Table O(1) average" << endl;
        cout << "   - Range queries: Segment Tree O(log n)" << endl;
        
        cout << "\n3. Graph Algorithms:" << endl;
        cout << "   - Shortest path (unweighted): BFS O(V + E)" << endl;
        cout << "   - Shortest path (weighted): Dijkstra O((V + E) log V)" << endl;
        cout << "   - All pairs shortest path: Floyd-Warshall O(V³)" << endl;
        cout << "   - Minimum spanning tree: Kruskal/Prim O(E log V)" << endl;
        
        cout << "\n4. Dynamic Programming:" << endl;
        cout << "   - Overlapping subproblems: Memoization" << endl;
        cout << "   - Optimal substructure: Bottom-up DP" << endl;
        cout << "   - Space optimization: Rolling array technique" << endl;
        
        cout << "=======================================" << endl;
    }
};
```

---

**Tóm tắt**: Hiểu rõ độ phức tạp tính toán giúp chúng ta:
1. **Chọn thuật toán phù hợp** cho từng bài toán
2. **Dự đoán hiệu suất** của chương trình
3. **Tối ưu hóa code** một cách có hệ thống
4. **Thiết kế hệ thống** có thể mở rộng (scalable)

**Nguyên tắc vàng**: "Premature optimization is the root of all evil" - Donald Knuth. Hãy đo lường trước khi tối ưu hóa!