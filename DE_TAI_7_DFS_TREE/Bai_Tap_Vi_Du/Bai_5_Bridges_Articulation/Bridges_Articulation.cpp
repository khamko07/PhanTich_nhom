#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Tìm cầu và khớp sử dụng thuật toán Tarjan
vector<vector<int>> adj;
vector<int> low, disc;
vector<bool> visited, articulation;
vector<pair<int, int>> bridges;
int timer_global = 0;

void bridgeAndArticulation(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer_global;
    int children = 0;
    
    for (int v : adj[u]) {
        if (v == parent) continue; // Bỏ qua cạnh đến cha
        
        if (visited[v]) {
            // Back edge: cập nhật low value
            low[u] = min(low[u], disc[v]);
        } else {
            // Tree edge: đệ quy
            children++;
            bridgeAndArticulation(v, u);
            
            // Cập nhật low value từ con
            low[u] = min(low[u], low[v]);
            
            // Kiểm tra cầu: low[v] > disc[u]
            if (low[v] > disc[u]) {
                bridges.push_back({min(u, v), max(u, v)});
            }
            
            // Kiểm tra khớp
            if ((parent == -1 && children > 1) ||  // Root với > 1 con
                (parent != -1 && low[v] >= disc[u])) { // Non-root
                articulation[u] = true;
            }
        }
    }
}

// Hàm debug để hiển thị quá trình Tarjan
void bridgeAndArticulationDebug(int u, int parent, int depth) {
    visited[u] = true;
    disc[u] = low[u] = ++timer_global;
    int children = 0;
    
    // In thông tin đỉnh hiện tại
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Visit " << u << ": disc=" << disc[u] << ", low=" << low[u] << endl;
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "Check edge " << u << " -> " << v << ": ";
        
        if (visited[v]) {
            cout << "Back edge, update low[" << u << "] = min(" << low[u] << ", " << disc[v] << ") = ";
            low[u] = min(low[u], disc[v]);
            cout << low[u] << endl;
        } else {
            cout << "Tree edge" << endl;
            children++;
            bridgeAndArticulationDebug(v, u, depth + 1);
            
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "Back from " << v << ": low[" << v << "]=" << low[v] << endl;
            
            low[u] = min(low[u], low[v]);
            
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "Update low[" << u << "] = " << low[u] << endl;
            
            // Kiểm tra cầu
            if (low[v] > disc[u]) {
                for (int i = 0; i < depth; i++) cout << "  ";
                cout << "Bridge found: " << u << " - " << v << endl;
                bridges.push_back({min(u, v), max(u, v)});
            }
            
            // Kiểm tra khớp
            if ((parent == -1 && children > 1) || 
                (parent != -1 && low[v] >= disc[u])) {
                for (int i = 0; i < depth; i++) cout << "  ";
                cout << "Articulation point found: " << u << endl;
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
    
    // Tìm cầu và khớp
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bridgeAndArticulation(i, -1);
        }
    }
    
    // Sắp xếp cầu theo thứ tự
    sort(bridges.begin(), bridges.end());
    
    // In kết quả cầu
    cout << bridges.size() << endl;
    for (auto bridge : bridges) {
        cout << bridge.first << " " << bridge.second << endl;
    }
    
    // In kết quả khớp
    vector<int> articulationPoints;
    for (int i = 0; i < n; i++) {
        if (articulation[i]) {
            articulationPoints.push_back(i);
        }
    }
    
    for (int i = 0; i < articulationPoints.size(); i++) {
        cout << articulationPoints[i];
        if (i < articulationPoints.size() - 1) cout << " ";
    }
    if (!articulationPoints.empty()) cout << endl;
    
    // Uncomment để xem debug info:
    // cout << "\n=== DEBUG TARJAN ALGORITHM ===" << endl;
    // visited.assign(n, false);
    // articulation.assign(n, false);
    // bridges.clear();
    // timer_global = 0;
    // for (int i = 0; i < n; i++) {
    //     if (!visited[i]) {
    //         bridgeAndArticulationDebug(i, -1, 0);
    //     }
    // }
    
    return 0;
}