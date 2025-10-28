#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Sắp xếp topo sử dụng DFS
vector<vector<int>> adj;
vector<bool> visited;
vector<int> topo_order;

void topologicalSort(int u) {
    visited[u] = true;
    
    // Thăm tất cả các đỉnh kề
    for (int v : adj[u]) {
        if (!visited[v]) {
            topologicalSort(v);
        }
    }
    
    // Thêm đỉnh vào kết quả khi hoàn thành (finish time)
    topo_order.push_back(u);
}

// Hàm debug để hiển thị quá trình sắp xếp topo
void topologicalSortDebug(int u, int depth) {
    visited[u] = true;
    
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Visit vertex " << u << endl;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "Go to vertex " << v << endl;
            topologicalSortDebug(v, depth + 1);
        }
    }
    
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Finish vertex " << u << " -> add to result" << endl;
    topo_order.push_back(u);
}

// Kiểm tra xem đồ thị có chu trình không (cần cho topo sort)
enum Color { WHITE, GRAY, BLACK };
vector<Color> color;

bool hasCycle(int u) {
    color[u] = GRAY;
    
    for (int v : adj[u]) {
        if (color[v] == GRAY) {
            return true; // Back edge -> chu trình
        }
        
        if (color[v] == WHITE && hasCycle(v)) {
            return true;
        }
    }
    
    color[u] = BLACK;
    return false;
}

// Phương pháp Kahn's algorithm để so sánh
vector<int> topologicalSortKahn(int n) {
    vector<int> indegree(n, 0);
    
    // Tính indegree
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    
    // Thêm các đỉnh có indegree = 0 vào queue
    vector<int> queue;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            queue.push_back(i);
        }
    }
    
    vector<int> result;
    while (!queue.empty()) {
        int u = queue.back();
        queue.pop_back();
        result.push_back(u);
        
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                queue.push_back(v);
            }
        }
    }
    
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n);
    visited.resize(n, false);
    color.resize(n, WHITE);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    // Kiểm tra chu trình trước khi sắp xếp topo
    bool cycleFound = false;
    for (int i = 0; i < n; i++) {
        if (color[i] == WHITE && hasCycle(i)) {
            cycleFound = true;
            break;
        }
    }
    
    if (cycleFound) {
        cout << "Graph has cycle - cannot perform topological sort" << endl;
        return 0;
    }
    
    // Thực hiện sắp xếp topo
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topologicalSort(i);
        }
    }
    
    // Đảo ngược thứ tự (vì ta thêm theo finish time)
    reverse(topo_order.begin(), topo_order.end());
    
    // In kết quả
    for (int i = 0; i < n; i++) {
        cout << topo_order[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // cout << "\n=== DEBUG TOPOLOGICAL SORT ===" << endl;
    // visited.assign(n, false);
    // topo_order.clear();
    // for (int i = 0; i < n; i++) {
    //     if (!visited[i]) {
    //         topologicalSortDebug(i, 0);
    //     }
    // }
    // reverse(topo_order.begin(), topo_order.end());
    
    // Uncomment để so sánh với Kahn's algorithm:
    // vector<int> kahnResult = topologicalSortKahn(n);
    // cout << "Kahn's result: ";
    // for (int x : kahnResult) cout << x << " ";
    // cout << endl;
    
    return 0;
}