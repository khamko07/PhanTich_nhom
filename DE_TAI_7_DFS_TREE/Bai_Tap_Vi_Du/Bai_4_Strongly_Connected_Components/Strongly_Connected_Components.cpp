#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Tìm thành phần liên thông mạnh sử dụng thuật toán Kosaraju
vector<vector<int>> adj, radj; // adj: đồ thị gốc, radj: đồ thị transpose
vector<bool> visited;
vector<int> order;

// DFS lần 1: tính finish time
void dfs1(int u) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    
    order.push_back(u); // Thêm vào theo finish time
}

// DFS lần 2: tìm SCC trên đồ thị transpose
void dfs2(int u, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    
    for (int v : radj[u]) {
        if (!visited[v]) {
            dfs2(v, component);
        }
    }
}

// Hàm debug để hiển thị quá trình Kosaraju
vector<vector<int>> findSCCDebug(int n) {
    cout << "=== DEBUG KOSARAJU ALGORITHM ===" << endl;
    
    // Bước 1: DFS trên đồ thị gốc
    cout << "Step 1: DFS on original graph" << endl;
    visited.assign(n, false);
    order.clear();
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "Start DFS from vertex " << i << endl;
            dfs1(i);
        }
    }
    
    cout << "Finish order: ";
    for (int x : order) cout << x << " ";
    cout << endl << endl;
    
    // Bước 2: DFS trên đồ thị transpose theo thứ tự ngược
    cout << "Step 2: DFS on transpose graph in reverse order" << endl;
    visited.assign(n, false);
    vector<vector<int>> sccs;
    
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (!visited[u]) {
            cout << "Start DFS from vertex " << u << endl;
            vector<int> component;
            dfs2(u, component);
            sccs.push_back(component);
            
            cout << "Found SCC: ";
            for (int v : component) cout << v << " ";
            cout << endl;
        }
    }
    
    cout << "Total SCCs found: " << sccs.size() << endl;
    cout << "===============================" << endl;
    
    return sccs;
}

// Thuật toán Tarjan để so sánh
vector<int> ids, low, on_stack;
vector<bool> visited_tarjan;
vector<int> stack_tarjan;
vector<vector<int>> sccs_tarjan;
int id_counter = 0;

void tarjan(int u) {
    stack_tarjan.push_back(u);
    on_stack[u] = true;
    ids[u] = low[u] = id_counter++;
    
    for (int v : adj[u]) {
        if (ids[v] == -1) {
            tarjan(v);
        }
        if (on_stack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }
    
    if (ids[u] == low[u]) {
        vector<int> component;
        while (true) {
            int v = stack_tarjan.back();
            stack_tarjan.pop_back();
            on_stack[v] = false;
            component.push_back(v);
            if (v == u) break;
        }
        sccs_tarjan.push_back(component);
    }
}

vector<vector<int>> findSCCTarjan(int n) {
    ids.assign(n, -1);
    low.assign(n, 0);
    on_stack.assign(n, false);
    sccs_tarjan.clear();
    stack_tarjan.clear();
    id_counter = 0;
    
    for (int i = 0; i < n; i++) {
        if (ids[i] == -1) {
            tarjan(i);
        }
    }
    
    return sccs_tarjan;
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
    
    // Thuật toán Kosaraju
    // Bước 1: DFS trên đồ thị gốc
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
    
    // In kết quả
    cout << sccs.size() << endl;
    for (auto& scc : sccs) {
        for (int u : scc) {
            cout << u << " ";
        }
        cout << endl;
    }
    
    // Uncomment để xem debug info:
    // findSCCDebug(n);
    
    // Uncomment để so sánh với Tarjan:
    // vector<vector<int>> tarjanResult = findSCCTarjan(n);
    // cout << "Tarjan result: " << tarjanResult.size() << " SCCs" << endl;
    // for (auto& scc : tarjanResult) {
    //     for (int u : scc) cout << u << " ";
    //     cout << endl;
    // }
    
    return 0;
}