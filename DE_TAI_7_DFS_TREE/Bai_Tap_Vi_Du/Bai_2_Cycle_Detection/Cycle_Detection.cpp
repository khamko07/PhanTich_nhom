#include <iostream>
#include <vector>
using namespace std;

// Phát hiện chu trình trong đồ thị vô hướng sử dụng DFS
vector<vector<int>> adj;
vector<bool> visited;

bool hasCycle(int u, int parent) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        // Bỏ qua cạnh đến đỉnh cha
        if (v == parent) continue;
        
        if (visited[v]) {
            // Tìm thấy back edge -> có chu trình
            return true;
        }
        
        // Đệ quy kiểm tra đỉnh con
        if (hasCycle(v, u)) {
            return true;
        }
    }
    
    return false;
}

// Hàm debug để hiển thị quá trình tìm chu trình
bool hasCycleDebug(int u, int parent, int depth, vector<int>& path) {
    visited[u] = true;
    path.push_back(u);
    
    // In thông tin đỉnh hiện tại
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Visit vertex " << u << ", path: ";
    for (int v : path) cout << v << " ";
    cout << endl;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "Check edge " << u << " -> " << v << ": ";
        
        if (visited[v]) {
            cout << "Back edge found! Cycle detected." << endl;
            cout << "Cycle path: ";
            for (int node : path) cout << node << " ";
            cout << v << endl;
            return true;
        } else {
            cout << "Tree edge" << endl;
            if (hasCycleDebug(v, u, depth + 1, path)) {
                return true;
            }
        }
    }
    
    path.pop_back();
    return false;
}

// Phương pháp Union-Find để so sánh
class UnionFind {
public:
    vector<int> parent, rank;
    
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
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
        if (px == py) return false; // Đã trong cùng tập hợp -> chu trình
        
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

bool hasCycleUnionFind(int n, vector<pair<int, int>>& edges) {
    UnionFind uf(n);
    
    for (auto& edge : edges) {
        if (!uf.unite(edge.first, edge.second)) {
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
    vector<pair<int, int>> edges;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
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
    
    // Uncomment để xem debug info:
    // cout << "\n=== DEBUG CYCLE DETECTION ===" << endl;
    // visited.assign(n, false);
    // vector<int> path;
    // for (int i = 0; i < n; i++) {
    //     if (!visited[i]) {
    //         if (hasCycleDebug(i, -1, 0, path)) {
    //             break;
    //         }
    //     }
    // }
    
    // Uncomment để so sánh với Union-Find:
    // bool ufResult = hasCycleUnionFind(n, edges);
    // cout << "Union-Find result: " << (ufResult ? "YES" : "NO") << endl;
    // cout << "Results match: " << (foundCycle == ufResult ? "YES" : "NO") << endl;
    
    return 0;
}