# Đề Tài 8: Greedy is Good - Thuật Toán Tham Lam Nâng Cao

## 1. Trình Bày Lý Thuyết

### 1.1 Giới Thiệu Về Thuật Toán Tham Lam Nâng Cao

**"Greedy is Good"** là một nguyên lý quan trọng trong thiết kế thuật toán, nhấn mạnh rằng trong nhiều bài toán, việc đưa ra quyết định tối ưu cục bộ tại mỗi bước sẽ dẫn đến lời giải tối ưu toàn cục. Tuy nhiên, không phải bài toán nào cũng có thể giải bằng thuật toán tham lam.

### 1.2 Đặc Điểm Của Bài Toán Greedy

**Hai tính chất cần thiết:**

**1. Greedy Choice Property (Tính chất lựa chọn tham lam):**
- Lời giải tối ưu toàn cục có thể đạt được bằng cách đưa ra lựa chọn tối ưu cục bộ
- Không cần xem xét lại các quyết định đã đưa ra

**2. Optimal Substructure (Cấu trúc con tối ưu):**
- Lời giải tối ưu của bài toán chứa lời giải tối ưu của các bài toán con
- Có thể xây dựng lời giải từ dưới lên (bottom-up)

### 1.3 Phương Pháp Chứng Minh Thuật Toán Greedy

**Bước 1: Chứng minh Greedy Choice Property**
- Chỉ ra rằng luôn tồn tại lời giải tối ưu chứa lựa chọn greedy
- Sử dụng phương pháp "exchange argument"

**Bước 2: Chứng minh Optimal Substructure**
- Sau khi đưa ra lựa chọn greedy, bài toán còn lại vẫn có cấu trúc tối ưu
- Có thể giải bài toán con một cách độc lập

**Template chứng minh:**
```
Giả sử có lời giải tối ưu O không chứa lựa chọn greedy G.
Chứng minh rằng ta có thể thay thế một phần của O bằng G 
mà không làm giảm chất lượng lời giải.
Do đó, lựa chọn greedy luôn an toàn.
```

### 1.4 Các Dạng Bài Toán Greedy Kinh Điển

**1. Activity Selection Problem:**
- Chọn tối đa số hoạt động không trùng thời gian
- Greedy choice: Chọn hoạt động kết thúc sớm nhất

**2. Fractional Knapsack:**
- Tối đa hóa giá trị trong cái túi với trọng lượng giới hạn
- Greedy choice: Chọn theo tỷ lệ value/weight giảm dần

**3. Huffman Coding:**
- Tạo mã nhị phân tối ưu cho nén dữ liệu
- Greedy choice: Kết hợp hai ký tự có tần suất thấp nhất

**4. Minimum Spanning Tree:**
- Tìm cây khung nhỏ nhất của đồ thị
- Kruskal: Chọn cạnh nhỏ nhất không tạo chu trình
- Prim: Chọn cạnh nhỏ nhất nối với cây hiện tại## 2. 
Các Thuật Toán Greedy Nâng Cao

### 2.1 Activity Selection Problem

**Bài toán:** Cho n hoạt động với thời gian bắt đầu s[i] và kết thúc f[i]. Chọn tối đa số hoạt động không trùng thời gian.

**Thuật toán:**
```cpp
struct Activity {
    int start, finish;
    int id;
};

bool compareByFinish(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

vector<int> activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), compareByFinish);
    
    vector<int> result;
    result.push_back(activities[0].id);
    int lastFinish = activities[0].finish;
    
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastFinish) {
            result.push_back(activities[i].id);
            lastFinish = activities[i].finish;
        }
    }
    
    return result;
}
```

**Chứng minh tính đúng đắn:**
- Greedy choice: Chọn hoạt động kết thúc sớm nhất
- Lý do: Hoạt động kết thúc sớm để lại nhiều thời gian nhất cho các hoạt động sau

### 2.2 Huffman Coding

**Bài toán:** Tạo mã nhị phân có độ dài trung bình nhỏ nhất cho tập ký tự với tần suất cho trước.

**Thuật toán:**
```cpp
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(int f) : ch(0), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // Min heap
    }
};

Node* buildHuffmanTree(vector<pair<char, int>>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Tạo leaf nodes
    for (auto& p : frequencies) {
        pq.push(new Node(p.first, p.second));
    }
    
    // Xây dựng cây
    while (pq.size() > 1) {
        Node* right = pq.top(); pq.pop();
        Node* left = pq.top(); pq.pop();
        
        Node* merged = new Node(left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        
        pq.push(merged);
    }
    
    return pq.top();
}

void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    
    if (root->ch != 0) { // Leaf node
        codes[root->ch] = code;
        return;
    }
    
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}
```

### 2.3 Minimum Spanning Tree - Kruskal's Algorithm

**Bài toán:** Tìm cây khung có tổng trọng số nhỏ nhất của đồ thị liên thông.

**Thuật toán:**
```cpp
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

vector<Edge> kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    vector<Edge> mst;
    
    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            if (mst.size() == n - 1) break;
        }
    }
    
    return mst;
}
```

### 2.4 Dijkstra's Algorithm

**Bài toán:** Tìm đường đi ngắn nhất từ một đỉnh đến tất cả các đỉnh khác.

**Thuật toán:**
```cpp
vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (const auto& edge : adj[u]) {
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
```##
 3. Bài Tập Thực Hành

### Bài 1: Activity Selection Problem
**Đề bài**: Chọn tối đa số hoạt động không trùng thời gian.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, finish, id;
    
    Activity(int s, int f, int i) : start(s), finish(f), id(i) {}
};

bool compareByFinish(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

vector<int> activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), compareByFinish);
    
    vector<int> result;
    if (activities.empty()) return result;
    
    result.push_back(activities[0].id);
    int lastFinish = activities[0].finish;
    
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastFinish) {
            result.push_back(activities[i].id);
            lastFinish = activities[i].finish;
        }
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    
    vector<Activity> activities;
    for (int i = 0; i < n; i++) {
        int start, finish;
        cin >> start >> finish;
        activities.push_back(Activity(start, finish, i));
    }
    
    vector<int> selected = activitySelection(activities);
    
    cout << selected.size() << endl;
    for (int id : selected) {
        cout << id << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Bài 2: Fractional Knapsack
**Đề bài**: Tối đa hóa giá trị trong cái túi với khả năng chia nhỏ vật phẩm.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
    double ratio;
    
    Item(int v, int w) : value(v), weight(w) {
        ratio = (double)value / weight;
    }
};

bool compareByRatio(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(), compareByRatio);
    
    double totalValue = 0.0;
    int currentWeight = 0;
    
    for (const Item& item : items) {
        if (currentWeight + item.weight <= capacity) {
            // Lấy toàn bộ vật phẩm
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            // Lấy một phần vật phẩm
            int remainingCapacity = capacity - currentWeight;
            totalValue += item.ratio * remainingCapacity;
            break;
        }
    }
    
    return totalValue;
}

int main() {
    int n, capacity;
    cin >> n >> capacity;
    
    vector<Item> items;
    for (int i = 0; i < n; i++) {
        int value, weight;
        cin >> value >> weight;
        items.push_back(Item(value, weight));
    }
    
    double maxValue = fractionalKnapsack(items, capacity);
    cout << (int)maxValue << endl;
    
    return 0;
}
```

### Bài 3: Job Scheduling
**Đề bài**: Sắp xếp công việc để tối thiểu hóa thời gian chờ trung bình.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int duration, id;
    
    Job(int d, int i) : duration(d), id(i) {}
};

bool compareByDuration(const Job& a, const Job& b) {
    return a.duration < b.duration;
}

int minimizeWaitingTime(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compareByDuration);
    
    int totalWaitingTime = 0;
    int currentTime = 0;
    
    for (const Job& job : jobs) {
        totalWaitingTime += currentTime;
        currentTime += job.duration;
    }
    
    return totalWaitingTime;
}

int main() {
    int n;
    cin >> n;
    
    vector<Job> jobs;
    for (int i = 0; i < n; i++) {
        int duration;
        cin >> duration;
        jobs.push_back(Job(duration, i));
    }
    
    int minWaitingTime = minimizeWaitingTime(jobs);
    cout << minWaitingTime << endl;
    
    return 0;
}
```

### Bài 4: Huffman Coding
**Đề bài**: Tạo mã Huffman cho tập ký tự với tần suất cho trước.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(int f) : ch(0), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq == b->freq) {
            return a->ch > b->ch; // Tie-breaking
        }
        return a->freq > b->freq;
    }
};

Node* buildHuffmanTree(vector<pair<char, int>>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    for (auto& p : frequencies) {
        pq.push(new Node(p.first, p.second));
    }
    
    while (pq.size() > 1) {
        Node* right = pq.top(); pq.pop();
        Node* left = pq.top(); pq.pop();
        
        Node* merged = new Node(left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        
        pq.push(merged);
    }
    
    return pq.top();
}

void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    
    if (root->ch != 0) {
        codes[root->ch] = code.empty() ? "0" : code;
        return;
    }
    
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

int main() {
    int n;
    cin >> n;
    
    vector<pair<char, int>> frequencies;
    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        cin >> ch >> freq;
        frequencies.push_back({ch, freq});
    }
    
    Node* root = buildHuffmanTree(frequencies);
    map<char, string> codes;
    generateCodes(root, "", codes);
    
    for (auto& p : codes) {
        cout << p.first << ": " << p.second << endl;
    }
    
    return 0;
}
```### Bài 5
: Minimum Spanning Tree (Kruskal)
**Đề bài**: Tìm cây khung nhỏ nhất của đồ thị có trọng số.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

pair<int, vector<Edge>> kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    vector<Edge> mst;
    int totalWeight = 0;
    
    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
            if (mst.size() == n - 1) break;
        }
    }
    
    return {totalWeight, mst};
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }
    
    auto result = kruskalMST(n, edges);
    int totalWeight = result.first;
    vector<Edge> mst = result.second;
    
    cout << totalWeight << endl;
    for (const Edge& e : mst) {
        cout << e.u << " " << e.v << " " << e.weight << endl;
    }
    
    return 0;
}
```

## 4. Kỹ Thuật Chứng Minh Thuật Toán Greedy

### 4.1 Exchange Argument (Lập luận trao đổi)

**Phương pháp:**
1. Giả sử có lời giải tối ưu OPT không chứa lựa chọn greedy
2. Chứng minh có thể "trao đổi" một phần của OPT với lựa chọn greedy
3. Lời giải mới không tệ hơn OPT
4. Kết luận: Lựa chọn greedy luôn an toàn

**Ví dụ - Activity Selection:**
```
Giả sử OPT không chọn hoạt động a1 (kết thúc sớm nhất).
OPT phải chọn hoạt động ai nào đó.
Vì f[a1] ≤ f[ai], ta có thể thay ai bằng a1 trong OPT.
Lời giải mới vẫn khả thi và có cùng số hoạt động.
```

### 4.2 Cut and Paste (Cắt và dán)

**Phương pháp:**
1. Chia lời giải tối ưu thành hai phần
2. Chứng minh phần đầu có thể thay bằng lựa chọn greedy
3. Phần sau vẫn tối ưu cho bài toán con

**Ví dụ - Huffman Coding:**
```
Giả sử cây tối ưu T không có hai ký tự tần suất thấp nhất ở cùng độ sâu tối đa.
Ta có thể "cắt" và "dán" để đưa chúng xuống cùng độ sâu.
Chi phí không tăng, và ta có thể áp dụng greedy choice.
```

### 4.3 Staying Ahead (Luôn dẫn trước)

**Phương pháp:**
1. So sánh lời giải greedy với lời giải tối ưu từng bước
2. Chứng minh greedy "không tệ hơn" tại mọi bước
3. Kết luận greedy đạt tối ưu

**Ví dụ - Job Scheduling:**
```
Sắp xếp công việc theo thời gian tăng dần.
Tại bước k, tổng thời gian chờ của greedy ≤ tổng thời gian chờ của OPT.
Do đó, greedy đạt tối ưu toàn cục.
```

## 5. Các Bài Toán Greedy Nâng Cao

### 5.1 Interval Scheduling Maximization

**Bài toán:** Cho n khoảng thời gian [si, fi], chọn tối đa số khoảng không giao nhau.

**Greedy choice:** Chọn khoảng kết thúc sớm nhất.

**Chứng minh:** Exchange argument - có thể thay thế khoảng kết thúc muộn hơn.

### 5.2 Minimizing Lateness

**Bài toán:** Cho n công việc với deadline di và thời gian ti. Sắp xếp để tối thiểu hóa độ trễ tối đa.

**Greedy choice:** Sắp xếp theo deadline tăng dần (Earliest Deadline First).

**Chứng minh:** Exchange argument - hoán đổi hai công việc liền kề không làm tăng lateness.

### 5.3 Optimal Caching

**Bài toán:** Quản lý cache với k slot, tối thiểu hóa số lần cache miss.

**Greedy choice:** Khi cache đầy, loại bỏ item sẽ được sử dụng muộn nhất (Furthest in Future).

**Chứng minh:** Exchange argument phức tạp hơn, cần xét từng bước thay thế.

### 5.4 Shortest Path (Dijkstra)

**Bài toán:** Tìm đường đi ngắn nhất từ nguồn đến tất cả đỉnh khác.

**Greedy choice:** Chọn đỉnh chưa xử lý có khoảng cách nhỏ nhất.

**Chứng minh:** Cut property - đường đi qua đỉnh khác sẽ dài hơn do trọng số không âm.

## 6. Khi Nào Greedy Không Hoạt Động

### 6.1 0/1 Knapsack Problem

**Tại sao greedy thất bại:**
- Không thể chia nhỏ vật phẩm
- Lựa chọn cục bộ có thể chặn lựa chọn tốt hơn sau này

**Ví dụ:**
```
Capacity = 10
Items: (value=10, weight=5), (value=20, weight=20), (value=15, weight=15)
Greedy by ratio: Chọn item 1 (ratio=2), không thể chọn thêm
Optimal: Chọn item 2 (value=20)
```

### 6.2 Traveling Salesman Problem

**Tại sao greedy thất bại:**
- Quyết định cục bộ có thể dẫn đến bế tắc
- Không có cấu trúc con tối ưu đơn giản

### 6.3 Graph Coloring

**Tại sao greedy thất bại:**
- Thứ tự xét đỉnh ảnh hưởng lớn đến kết quả
- Không đảm bảo tối ưu toàn cục

## 7. Mẹo Và Kỹ Thuật

### 7.1 Nhận Dạng Bài Toán Greedy

**Dấu hiệu:**
- Có thể sắp xếp theo một tiêu chí nào đó
- Lựa chọn cục bộ không ảnh hưởng đến lựa chọn sau
- Có cấu trúc con tối ưu rõ ràng

### 7.2 Thiết Kế Thuật Toán Greedy

**Bước 1:** Xác định greedy choice
**Bước 2:** Chứng minh tính đúng đắn
**Bước 3:** Cài đặt hiệu quả

### 7.3 Debug Thuật Toán Greedy

**Kiểm tra:**
- Thứ tự sắp xếp có đúng không?
- Điều kiện lựa chọn có chính xác không?
- Có xử lý trường hợp biên không?

---

**Tác giả**: [Tên nhóm]  
**Ngày hoàn thành**: [Ngày tháng năm]  
**Tham khảo**: VNOI Wiki - Greedy is Good, TopCoder Tutorial