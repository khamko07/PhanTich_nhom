# Đề Tài 7: Depth-First Search Tree (Cây DFS)

## 1. Trình Bày Lý Thuyết

### 1.1 Giới Thiệu Về DFS Tree

**Depth-First Search Tree (Cây DFS)** là cây được tạo ra trong quá trình thực hiện thuật toán DFS trên đồ thị. Cây DFS không chỉ giúp duyệt đồ thị mà còn cung cấp thông tin quan trọng về cấu trúc và tính chất của đồ thị.

### 1.2 Các Loại Cạnh Trong DFS Tree

Khi thực hiện DFS, mỗi cạnh trong đồ thị được phân loại thành một trong bốn loại:

**1. Tree Edge (Cạnh cây):**
- Cạnh nối từ đỉnh cha đến đỉnh con trong cây DFS
- Được sử dụng để mở rộng cây DFS

**2. Back Edge (Cạnh ngược):**
- Cạnh nối từ đỉnh con đến tổ tiên của nó trong cây DFS
- Chỉ ra sự tồn tại của chu trình trong đồ thị

**3. Forward Edge (Cạnh tiến):**
- Cạnh nối từ tổ tiên đến hậu duệ (không phải con trực tiếp)
- Chỉ xuất hiện trong đồ thị có hướng

**4. Cross Edge (Cạnh chéo):**
- Cạnh nối giữa hai đỉnh không có quan hệ tổ tiên-hậu duệ
- Chỉ xuất hiện trong đồ thị có hướng

### 1.3 Thuật Toán DFS Cơ Bản

```cpp
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;
vector<int> disc_time, finish_time;
int timer = 0;

void dfs(int u) {
    visited[u] = true;
    disc_time[u] = ++timer;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            cout << "Tree edge: " << u << " -> " << v << endl;
            dfs(v);
        } else if (parent[u] != v) {
            if (disc_time[v] < disc_time[u]) {
                cout << "Back edge: " << u << " -> " << v << endl;
            } else {
                cout << "Forward/Cross edge: " << u << " -> " << v << endl;
            }
        }
    }
    
    finish_time[u] = ++timer;
}
```### 
1.4 Thời Gian Khám Phá và Hoàn Thành

**Discovery Time (Thời gian khám phá):**
- Thời điểm đỉnh được thăm lần đầu tiên
- Ký hiệu: disc[u]

**Finish Time (Thời gian hoàn thành):**
- Thời điểm kết thúc xử lý đỉnh
- Ký hiệu: finish[u]

**Tính chất quan trọng:**
- disc[u] < disc[v] và finish[v] < finish[u] ⟺ v là hậu duệ của u
- disc[u] < disc[v] và finish[u] < finish[v] ⟺ u và v không có quan hệ tổ tiên

### 1.5 Ứng Dụng Của DFS Tree

**1. Phát hiện chu trình:**
- Đồ thị vô hướng: có chu trình ⟺ có back edge
- Đồ thị có hướng: có chu trình ⟺ có back edge

**2. Sắp xếp topo (Topological Sort):**
- Sắp xếp các đỉnh theo thứ tự finish time giảm dần

**3. Tìm thành phần liên thông mạnh (SCC):**
- Sử dụng thuật toán Kosaraju hoặc Tarjan

**4. Tìm cầu và khớp:**
- Sử dụng low-link values

## 2. Các Thuật Toán Liên Quan

### 2.1 Phát Hiện Chu Trình

**Đồ thị vô hướng:**
```cpp
bool hasCycleUndirected(int u, int parent) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        if (visited[v]) {
            return true; // Back edge found
        }
        
        if (hasCycleUndirected(v, u)) {
            return true;
        }
    }
    
    return false;
}
```

**Đồ thị có hướng:**
```cpp
enum Color { WHITE, GRAY, BLACK };
vector<Color> color;

bool hasCycleDirected(int u) {
    color[u] = GRAY;
    
    for (int v : adj[u]) {
        if (color[v] == GRAY) {
            return true; // Back edge found
        }
        
        if (color[v] == WHITE && hasCycleDirected(v)) {
            return true;
        }
    }
    
    color[u] = BLACK;
    return false;
}
```

### 2.2 Sắp Xếp Topo (Topological Sort)

```cpp
vector<int> topo_order;

void topologicalSort(int u) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            topologicalSort(v);
        }
    }
    
    topo_order.push_back(u);
}

void performTopologicalSort(int n) {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topologicalSort(i);
        }
    }
    
    reverse(topo_order.begin(), topo_order.end());
}
```###
 2.3 Tìm Thành Phần Liên Thông Mạnh (SCC)

**Thuật toán Kosaraju:**
```cpp
vector<int> order;
vector<bool> visited;
vector<vector<int>> adj, radj; // adj: đồ thị gốc, radj: đồ thị transpose

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    order.push_back(u);
}

void dfs2(int u, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : radj[u]) {
        if (!visited[v]) {
            dfs2(v, component);
        }
    }
}

vector<vector<int>> findSCC(int n) {
    // Bước 1: DFS trên đồ thị gốc
    visited.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    // Bước 2: DFS trên đồ thị transpose theo thứ tự ngược
    visited.assign(n, false);
    vector<vector<int>> sccs;
    
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (!visited[u]) {
            vector<int> component;
            dfs2(u, component);
            sccs.push_back(component);
        }
    }
    
    return sccs;
}
```

### 2.4 Tìm Cầu và Khớp (Bridges and Articulation Points)

**Tìm cầu:**
```cpp
vector<int> low, disc;
vector<bool> visited;
vector<pair<int, int>> bridges;
int timer = 0;

void bridgeUtil(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        if (visited[v]) {
            low[u] = min(low[u], disc[v]);
        } else {
            bridgeUtil(v, u);
            low[u] = min(low[u], low[v]);
            
            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }
        }
    }
}
```

**Tìm khớp:**
```cpp
vector<bool> articulation;

void articulationUtil(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    int children = 0;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        if (visited[v]) {
            low[u] = min(low[u], disc[v]);
        } else {
            children++;
            articulationUtil(v, u);
            low[u] = min(low[u], low[v]);
            
            // Điều kiện để u là khớp
            if ((parent == -1 && children > 1) || 
                (parent != -1 && low[v] >= disc[u])) {
                articulation[u] = true;
            }
        }
    }
}
```

## 3. Bài Tập Thực Hành

### Bài 1: Xây Dựng DFS Tree
**Đề bài**: Cho đồ thị vô hướng, xây dựng DFS tree và phân loại các cạnh.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;
vector<pair<int, int>> tree_edges, back_edges;

void dfs(int u) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            tree_edges.push_back({u, v});
            dfs(v);
        } else if (parent[u] != v && u > v) {
            // Chỉ thêm back edge một lần (u > v để tránh trùng lặp)
            back_edges.push_back({u, v});
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n);
    visited.resize(n, false);
    parent.resize(n, -1);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    cout << "Tree edges: " << tree_edges.size() << endl;
    for (auto edge : tree_edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    
    cout << "Back edges: " << back_edges.size() << endl;
    for (auto edge : back_edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    
    return 0;
}
```### Bài 2: P
hát Hiện Chu Trình
**Đề bài**: Kiểm tra xem đồ thị có chu trình hay không.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

bool hasCycle(int u, int parent) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        if (visited[v]) {
            return true; // Tìm thấy back edge
        }
        
        if (hasCycle(v, u)) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n);
    visited.resize(n, false);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    bool foundCycle = false;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (hasCycle(i, -1)) {
                foundCycle = true;
                break;
            }
        }
    }
    
    cout << (foundCycle ? "YES" : "NO") << endl;
    
    return 0;
}
```

### Bài 3: Sắp Xếp Topo
**Đề bài**: Sắp xếp topo các đỉnh của đồ thị có hướng không chu trình.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> topo_order;

void topologicalSort(int u) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            topologicalSort(v);
        }
    }
    
    topo_order.push_back(u);
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n);
    visited.resize(n, false);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topologicalSort(i);
        }
    }
    
    reverse(topo_order.begin(), topo_order.end());
    
    for (int i = 0; i < n; i++) {
        cout << topo_order[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Bài 4: Tìm Thành Phần Liên Thông Mạnh
**Đề bài**: Tìm tất cả các thành phần liên thông mạnh trong đồ thị có hướng.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj, radj;
vector<bool> visited;
vector<int> order;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    order.push_back(u);
}

void dfs2(int u, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : radj[u]) {
        if (!visited[v]) {
            dfs2(v, component);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n);
    radj.resize(n);
    visited.resize(n, false);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u); // Đồ thị transpose
    }
    
    // Bước 1: DFS trên đồ thị gốc
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    // Bước 2: DFS trên đồ thị transpose
    visited.assign(n, false);
    vector<vector<int>> sccs;
    
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (!visited[u]) {
            vector<int> component;
            dfs2(u, component);
            sccs.push_back(component);
        }
    }
    
    cout << sccs.size() << endl;
    for (auto& scc : sccs) {
        for (int u : scc) {
            cout << u << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```### Bà
i 5: Tìm Cầu và Khớp
**Đề bài**: Tìm tất cả các cầu và khớp trong đồ thị vô hướng.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<int> low, disc;
vector<bool> visited, articulation;
vector<pair<int, int>> bridges;
int timer = 0;

void bridgeAndArticulation(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    int children = 0;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        if (visited[v]) {
            low[u] = min(low[u], disc[v]);
        } else {
            children++;
            bridgeAndArticulation(v, u);
            low[u] = min(low[u], low[v]);
            
            // Kiểm tra cầu
            if (low[v] > disc[u]) {
                bridges.push_back({min(u, v), max(u, v)});
            }
            
            // Kiểm tra khớp
            if ((parent == -1 && children > 1) || 
                (parent != -1 && low[v] >= disc[u])) {
                articulation[u] = true;
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n);
    low.resize(n);
    disc.resize(n);
    visited.resize(n, false);
    articulation.resize(n, false);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bridgeAndArticulation(i, -1);
        }
    }
    
    cout << "Bridges: " << bridges.size() << endl;
    for (auto bridge : bridges) {
        cout << bridge.first << " " << bridge.second << endl;
    }
    
    cout << "Articulation points: ";
    for (int i = 0; i < n; i++) {
        if (articulation[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    return 0;
}
```

## 4. Phân Tích Độ Phức Tạp

### 4.1 Độ Phức Tạp Thời Gian

| Thuật toán | Thời gian | Không gian | Ghi chú |
|------------|-----------|------------|---------|
| DFS cơ bản | O(V + E) | O(V) | V: đỉnh, E: cạnh |
| Phát hiện chu trình | O(V + E) | O(V) | Dừng sớm khi tìm thấy |
| Sắp xếp topo | O(V + E) | O(V) | Chỉ với DAG |
| Tìm SCC (Kosaraju) | O(V + E) | O(V) | Cần 2 lần DFS |
| Tìm cầu/khớp | O(V + E) | O(V) | Một lần DFS |

### 4.2 So Sánh Với BFS

| Tiêu chí | DFS | BFS |
|----------|-----|-----|
| Cấu trúc dữ liệu | Stack (đệ quy) | Queue |
| Bộ nhớ | O(h) với h = chiều cao | O(w) với w = độ rộng |
| Ứng dụng | Chu trình, SCC, Topo | Đường đi ngắn nhất |
| Cài đặt | Đơn giản hơn | Phức tạp hơn |

## 5. Các Tính Chất Quan Trọng

### 5.1 Tính Chất Của Thời Gian

**Định lý Parentheses:**
Với hai đỉnh u, v bất kỳ, một trong các điều kiện sau đúng:
1. [disc[u], finish[u]] và [disc[v], finish[v]] rời nhau
2. [disc[u], finish[u]] chứa [disc[v], finish[v]] (v là hậu duệ của u)
3. [disc[v], finish[v]] chứa [disc[u], finish[u]] (u là hậu duệ của v)

**Định lý White Path:**
v là hậu duệ của u trong DFS tree ⟺ tại thời điểm disc[u], tồn tại đường đi từ u đến v chỉ qua các đỉnh trắng (chưa thăm).

### 5.2 Phân Loại Cạnh Theo Thời Gian

Cho cạnh (u, v):
- **Tree edge**: disc[u] < disc[v] và v là con trực tiếp của u
- **Back edge**: disc[v] < disc[u] < finish[u] < finish[v]
- **Forward edge**: disc[u] < disc[v] < finish[v] < finish[u]
- **Cross edge**: disc[v] < finish[v] < disc[u] < finish[u]

## 6. Ứng Dụng Thực Tế

### 6.1 Trong Khoa Học Máy Tính
- **Compiler design**: Phân tích phụ thuộc, tối ưu hóa code
- **Database**: Phát hiện deadlock, sắp xếp transaction
- **AI**: Game tree search, planning problems

### 6.2 Trong Mạng và Hệ Thống
- **Network analysis**: Tìm điểm yếu, phân tích kết nối
- **Social networks**: Phát hiện cộng đồng, ảnh hưởng
- **Web crawling**: Duyệt và lập chỉ mục trang web

### 6.3 Trong Sinh Học và Hóa Học
- **Phylogenetic trees**: Phân tích tiến hóa
- **Protein folding**: Mô hình cấu trúc protein
- **Chemical reactions**: Phân tích đường phản ứng

## 7. Lưu Ý Quan Trọng

### 7.1 Các Lỗi Thường Gặp
1. **Quên khởi tạo** mảng visited
2. **Không xử lý** đồ thị không liên thông
3. **Nhầm lẫn** giữa đồ thị có hướng và vô hướng
4. **Stack overflow** với đồ thị sâu (dùng stack thay đệ quy)

### 7.2 Tối Ưu Hóa
- Sử dụng **iterative DFS** cho đồ thị sâu
- **Early termination** khi tìm thấy kết quả
- **Bitset** thay vector<bool> cho tốc độ
- **Memory pool** cho cấp phát bộ nhớ hiệu quả

### 7.3 Biến Thể Nâng Cao
- **Multi-source DFS**: Bắt đầu từ nhiều đỉnh
- **Bidirectional DFS**: Tìm kiếm từ hai phía
- **Parallel DFS**: Xử lý song song trên nhiều core
- **Dynamic DFS**: Cập nhật đồ thị trong quá trình duyệt

---

**Tác giả**: [Tên nhóm]  
**Ngày hoàn thành**: [Ngày tháng năm]  
**Tham khảo**: VNOI Wiki - Depth-First Search Tree, Introduction to Algorithms (CLRS)