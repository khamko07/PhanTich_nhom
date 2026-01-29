#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Minimum Spanning Tree sử dụng thuật toán Kruskal
struct Edge {
    int u, v, weight;
    
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    
    bool operator<(const Edge& other) const {
        if (weight == other.weight) {
            if (u == other.u) {
                return v < other.v;
            }
            return u < other.u;
        }
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
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false; // Đã trong cùng component
        
        // Union by rank
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
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

pair<int, vector<Edge>> kruskalMST(int n, vector<Edge>& edges) {
    // Greedy choice: Sắp xếp cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    vector<Edge> mst;
    int totalWeight = 0;
    
    for (const Edge& e : edges) {
        // Greedy choice: Chọn cạnh nhỏ nhất không tạo chu trình
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
            
            // MST có đúng n-1 cạnh
            if (mst.size() == n - 1) break;
        }
    }
    
    return {totalWeight, mst};
}

// Hàm debug để hiển thị quá trình Kruskal
void debugKruskalMST(int n, vector<Edge>& edges) {
    cout << "=== DEBUG KRUSKAL MST ===" << endl;
    cout << "Original edges:" << endl;
    for (int i = 0; i < edges.size(); i++) {
        cout << "Edge " << i << ": " << edges[i].u << " - " << edges[i].v 
             << " (weight " << edges[i].weight << ")" << endl;
    }
    
    sort(edges.begin(), edges.end());
    
    cout << "\nAfter sorting by weight:" << endl;
    for (int i = 0; i < edges.size(); i++) {
        cout << "Edge " << i << ": " << edges[i].u << " - " << edges[i].v 
             << " (weight " << edges[i].weight << ")" << endl;
    }
    
    cout << "\nKruskal's algorithm process:" << endl;
    UnionFind uf(n);
    vector<Edge> mst;
    int totalWeight = 0;
    
    for (int i = 0; i < edges.size(); i++) {
        const Edge& e = edges[i];
        cout << "Consider edge " << e.u << " - " << e.v << " (weight " << e.weight << "): ";
        
        if (uf.connected(e.u, e.v)) {
            cout << "REJECTED (creates cycle)" << endl;
        } else {
            uf.unite(e.u, e.v);
            mst.push_back(e);
            totalWeight += e.weight;
            cout << "ACCEPTED (MST edge #" << mst.size() << ")" << endl;
            
            if (mst.size() == n - 1) {
                cout << "MST completed with " << (n-1) << " edges!" << endl;
                break;
            }
        }
    }
    
    cout << "\nFinal MST:" << endl;
    cout << "Total weight: " << totalWeight << endl;
    cout << "Edges in MST:" << endl;
    for (const Edge& e : mst) {
        cout << e.u << " - " << e.v << " (weight " << e.weight << ")" << endl;
    }
    cout << "========================" << endl;
}

// Thuật toán Prim để so sánh
pair<int, vector<Edge>> primMST(int n, vector<Edge>& edges) {
    // Tạo adjacency list
    vector<vector<pair<int, int>>> adj(n);
    for (const Edge& e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }
    
    vector<bool> inMST(n, false);
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    
    key[0] = 0; // Bắt đầu từ đỉnh 0
    vector<Edge> mst;
    int totalWeight = 0;
    
    for (int count = 0; count < n; count++) {
        // Tìm đỉnh có key nhỏ nhất chưa trong MST
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }
        
        inMST[u] = true;
        if (parent[u] != -1) {
            mst.push_back(Edge(parent[u], u, key[u]));
            totalWeight += key[u];
        }
        
        // Cập nhật key của các đỉnh kề
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
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
    
    // Uncomment để xem debug info:
    // debugKruskalMST(n, edges);
    
    // Uncomment để so sánh với Prim:
    // auto primResult = primMST(n, edges);
    // cout << "Prim result: " << primResult.first << endl;
    // cout << "Results match: " << (totalWeight == primResult.first ? "YES" : "NO") << endl;
    
    return 0;
}