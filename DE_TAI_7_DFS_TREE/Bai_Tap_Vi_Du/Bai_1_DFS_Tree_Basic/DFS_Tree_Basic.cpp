#include <iostream>
#include <vector>
using namespace std;

// Xây dựng DFS Tree cơ bản và phân loại cạnh
vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;
vector<pair<int, int>> tree_edges, back_edges;

void dfs(int u) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            // Tree edge: cạnh dẫn đến đỉnh chưa thăm
            parent[v] = u;
            tree_edges.push_back({u, v});
            dfs(v);
        } else if (parent[u] != v && u > v) {
            // Back edge: cạnh dẫn đến đỉnh đã thăm (không phải cha)
            // Điều kiện u > v để tránh thêm cạnh trùng lặp trong đồ thị vô hướng
            back_edges.push_back({u, v});
        }
    }
}

// Hàm debug để hiển thị quá trình DFS
void debugDFS(int start) {
    cout << "=== DEBUG DFS TREE ===" << endl;
    cout << "Starting DFS from vertex " << start << endl << endl;
    
    // Reset để debug
    visited.assign(adj.size(), false);
    parent.assign(adj.size(), -1);
    tree_edges.clear();
    back_edges.clear();
    
    dfsDebug(start, 0);
    
    cout << "\nDFS Tree construction completed!" << endl;
    cout << "======================" << endl;
}

void dfsDebug(int u, int depth) {
    visited[u] = true;
    
    // In thông tin đỉnh hiện tại
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Visit vertex " << u << endl;
    
    for (int v : adj[u]) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "Check edge " << u << " -> " << v << ": ";
        
        if (!visited[v]) {
            cout << "Tree edge (new vertex)" << endl;
            parent[v] = u;
            tree_edges.push_back({u, v});
            dfsDebug(v, depth + 1);
        } else if (parent[u] != v) {
            if (u > v) {
                cout << "Back edge (already visited)" << endl;
                back_edges.push_back({u, v});
            } else {
                cout << "Back edge (skip to avoid duplicate)" << endl;
            }
        } else {
            cout << "Parent edge (skip)" << endl;
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
    
    // Thực hiện DFS từ tất cả các đỉnh chưa thăm
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    // In kết quả
    cout << tree_edges.size() << endl;
    for (auto edge : tree_edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    
    cout << back_edges.size() << endl;
    for (auto edge : back_edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    
    // Uncomment để xem debug info:
    // debugDFS(0);
    
    return 0;
}