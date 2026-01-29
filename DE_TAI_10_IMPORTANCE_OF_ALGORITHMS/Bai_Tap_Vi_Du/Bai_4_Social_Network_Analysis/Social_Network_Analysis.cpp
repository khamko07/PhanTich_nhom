#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

class SocialNetworkAnalysis {
private:
    vector<vector<int>> graph;
    int n;
    
public:
    SocialNetworkAnalysis(int nodes) : n(nodes) {
        graph.resize(n);
    }
    
    void addFriendship(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    // Tìm các thành phần liên thông (communities)
    vector<vector<int>> findCommunities() {
        vector<bool> visited(n, false);
        vector<vector<int>> communities;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                vector<int> community;
                dfs(i, visited, community);
                if (!community.empty()) {
                    sort(community.begin(), community.end());
                    communities.push_back(community);
                }
            }
        }
        
        return communities;
    }
    
    // Tính centrality measures
    vector<double> calculateBetweennessCentrality() {
        vector<double> centrality(n, 0.0);
        
        for (int s = 0; s < n; s++) {
            // Single-source shortest paths
            vector<vector<int>> predecessors(n);
            vector<double> sigma(n, 0);
            vector<int> distance(n, -1);
            vector<double> delta(n, 0);
            
            queue<int> q;
            stack<int> st;
            
            sigma[s] = 1;
            distance[s] = 0;
            q.push(s);
            
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                st.push(v);
                
                for (int w : graph[v]) {
                    if (distance[w] < 0) {
                        q.push(w);
                        distance[w] = distance[v] + 1;
                    }
                    
                    if (distance[w] == distance[v] + 1) {
                        sigma[w] += sigma[v];
                        predecessors[w].push_back(v);
                    }
                }
            }
            
            // Accumulation
            while (!st.empty()) {
                int w = st.top();
                st.pop();
                
                for (int v : predecessors[w]) {
                    delta[v] += (sigma[v] / sigma[w]) * (1 + delta[w]);
                }
                
                if (w != s) {
                    centrality[w] += delta[w];
                }
            }
        }
        
        // Normalize
        double normalization = 2.0 / ((n - 1) * (n - 2));
        for (int i = 0; i < n; i++) {
            centrality[i] *= normalization;
        }
        
        return centrality;
    }
    
    // Tính closeness centrality
    vector<double> calculateClosenessCentrality() {
        vector<double> centrality(n, 0.0);
        
        for (int i = 0; i < n; i++) {
            vector<int> distance(n, -1);
            queue<int> q;
            
            distance[i] = 0;
            q.push(i);
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : graph[u]) {
                    if (distance[v] == -1) {
                        distance[v] = distance[u] + 1;
                        q.push(v);
                    }
                }
            }
            
            double totalDistance = 0;
            int reachableNodes = 0;
            
            for (int j = 0; j < n; j++) {
                if (distance[j] > 0) {
                    totalDistance += distance[j];
                    reachableNodes++;
                }
            }
            
            if (reachableNodes > 0) {
                centrality[i] = reachableNodes / totalDistance;
            }
        }
        
        return centrality;
    }
    
    // Tìm influencers (nodes có degree cao)
    vector<pair<int, int>> findInfluencers() {
        vector<pair<int, int>> influencers;
        
        for (int i = 0; i < n; i++) {
            influencers.push_back({graph[i].size(), i});
        }
        
        sort(influencers.rbegin(), influencers.rend());
        return influencers;
    }
    
    // Tính clustering coefficient
    double calculateClusteringCoefficient(int node) {
        int degree = graph[node].size();
        if (degree < 2) return 0.0;
        
        int triangles = 0;
        set<int> neighbors(graph[node].begin(), graph[node].end());
        
        for (int i = 0; i < graph[node].size(); i++) {
            for (int j = i + 1; j < graph[node].size(); j++) {
                int u = graph[node][i];
                int v = graph[node][j];
                
                if (neighbors.count(u) && neighbors.count(v)) {
                    // Check if u and v are connected
                    for (int neighbor : graph[u]) {
                        if (neighbor == v) {
                            triangles++;
                            break;
                        }
                    }
                }
            }
        }
        
        int possibleTriangles = degree * (degree - 1) / 2;
        return (double)triangles / possibleTriangles;
    }
    
    // Phát hiện cầu (bridges) trong mạng
    vector<pair<int, int>> findBridges() {
        vector<pair<int, int>> bridges;
        vector<bool> visited(n, false);
        vector<int> disc(n), low(n), parent(n);
        int timer = 0;
        
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
        }
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                bridgeUtil(i, visited, disc, low, parent, bridges, timer);
            }
        }
        
        return bridges;
    }
    
    // Debug function để hiển thị phân tích mạng xã hội
    void debugSocialNetwork() {
        cout << "=== DEBUG SOCIAL NETWORK ANALYSIS ===" << endl;
        cout << "Network size: " << n << " users" << endl;
        
        // Show network structure
        cout << "\nNetwork connections:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "User " << i << " is friends with: ";
            for (int friend_id : graph[i]) {
                cout << friend_id << " ";
            }
            cout << "(degree: " << graph[i].size() << ")" << endl;
        }
        
        // Find communities
        auto communities = findCommunities();
        cout << "\nCommunities found: " << communities.size() << endl;
        for (int i = 0; i < communities.size(); i++) {
            cout << "Community " << (i + 1) << ": ";
            for (int user : communities[i]) {
                cout << user << " ";
            }
            cout << "(size: " << communities[i].size() << ")" << endl;
        }
        
        // Find influencers
        auto influencers = findInfluencers();
        cout << "\nTop influencers (by degree):" << endl;
        for (int i = 0; i < min(5, (int)influencers.size()); i++) {
            cout << "User " << influencers[i].second 
                 << " with " << influencers[i].first << " connections" << endl;
        }
        
        // Calculate centrality measures
        auto betweenness = calculateBetweennessCentrality();
        cout << "\nBetweenness centrality:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "User " << i << ": " << fixed << setprecision(4) 
                 << betweenness[i] << endl;
        }
        
        // Find bridges
        auto bridges = findBridges();
        cout << "\nCritical connections (bridges): " << bridges.size() << endl;
        for (auto& bridge : bridges) {
            cout << "Bridge between " << bridge.first << " and " << bridge.second << endl;
        }
        
        cout << "=====================================" << endl;
    }
    
    // Hàm mô phỏng lan truyền thông tin
    vector<int> simulateInformationSpread(int startUser, double spreadProbability = 0.3) {
        vector<bool> informed(n, false);
        vector<int> spreadOrder;
        queue<int> q;
        
        informed[startUser] = true;
        spreadOrder.push_back(startUser);
        q.push(startUser);
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            for (int neighbor : graph[current]) {
                if (!informed[neighbor]) {
                    // Simulate probability of information spread
                    double random = (double)rand() / RAND_MAX;
                    if (random < spreadProbability) {
                        informed[neighbor] = true;
                        spreadOrder.push_back(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }
        
        return spreadOrder;
    }
    
    // Tính toán network density
    double calculateNetworkDensity() {
        int totalEdges = 0;
        for (int i = 0; i < n; i++) {
            totalEdges += graph[i].size();
        }
        totalEdges /= 2; // Each edge counted twice
        
        int maxPossibleEdges = n * (n - 1) / 2;
        return (double)totalEdges / maxPossibleEdges;
    }
    
private:
    void dfs(int u, vector<bool>& visited, vector<int>& community) {
        visited[u] = true;
        community.push_back(u);
        
        for (int v : graph[u]) {
            if (!visited[v]) {
                dfs(v, visited, community);
            }
        }
    }
    
    void bridgeUtil(int u, vector<bool>& visited, vector<int>& disc, 
                   vector<int>& low, vector<int>& parent, 
                   vector<pair<int, int>>& bridges, int& timer) {
        visited[u] = true;
        disc[u] = low[u] = ++timer;
        
        for (int v : graph[u]) {
            if (!visited[v]) {
                parent[v] = u;
                bridgeUtil(v, visited, disc, low, parent, bridges, timer);
                
                low[u] = min(low[u], low[v]);
                
                if (low[v] > disc[u]) {
                    bridges.push_back({min(u, v), max(u, v)});
                }
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
};

// Hàm so sánh với random network
void compareWithRandomNetwork(int n, int m) {
    cout << "\n=== COMPARISON WITH RANDOM NETWORK ===" << endl;
    
    // Create random network with same number of nodes and edges
    SocialNetworkAnalysis randomNet(n);
    srand(time(nullptr));
    
    set<pair<int, int>> addedEdges;
    int edgesAdded = 0;
    
    while (edgesAdded < m) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && addedEdges.find({min(u,v), max(u,v)}) == addedEdges.end()) {
            randomNet.addFriendship(u, v);
            addedEdges.insert({min(u,v), max(u,v)});
            edgesAdded++;
        }
    }
    
    auto randomCommunities = randomNet.findCommunities();
    double randomDensity = randomNet.calculateNetworkDensity();
    
    cout << "Random network communities: " << randomCommunities.size() << endl;
    cout << "Random network density: " << fixed << setprecision(4) << randomDensity << endl;
    cout << "Real social networks typically have:" << endl;
    cout << "- Higher clustering coefficient" << endl;
    cout << "- Small world property (short average path length)" << endl;
    cout << "- Power-law degree distribution" << endl;
    cout << "=======================================" << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    SocialNetworkAnalysis sna(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        sna.addFriendship(u, v);
    }
    
    auto communities = sna.findCommunities();
    
    cout << communities.size() << endl;
    for (const auto& community : communities) {
        for (int i = 0; i < community.size(); i++) {
            cout << community[i];
            if (i < community.size() - 1) cout << " ";
        }
        cout << endl;
    }
    
    // Uncomment để xem debug info:
    // sna.debugSocialNetwork();
    
    // Test information spread:
    // auto spread = sna.simulateInformationSpread(0, 0.5);
    // cout << "Information reached " << spread.size() << " users" << endl;
    
    // Compare with random network:
    // compareWithRandomNetwork(n, m);
    
    return 0;
}