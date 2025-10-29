#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <iomanip>
using namespace std;

struct Edge {
    int to;
    double weight;
    string roadName;
    
    Edge(int t, double w, string name = "") : to(t), weight(w), roadName(name) {}
};

class GPSNavigation {
private:
    vector<vector<Edge>> graph;
    vector<pair<double, double>> coordinates; // lat, lng
    int n;
    
public:
    GPSNavigation(int nodes) : n(nodes) {
        graph.resize(n);
        coordinates.resize(n);
    }
    
    void addRoad(int from, int to, double time, string roadName = "") {
        graph[from].push_back(Edge(to, time, roadName));
        // Assuming bidirectional roads
        graph[to].push_back(Edge(from, time, roadName));
    }
    
    void setCoordinate(int node, double lat, double lng) {
        coordinates[node] = {lat, lng};
    }
    
    pair<double, vector<int>> findShortestPath(int start, int destination) {
        vector<double> dist(n, INFINITY);
        vector<int> parent(n, -1);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            double d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (const Edge& edge : graph[u]) {
                int v = edge.to;
                double weight = edge.weight;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        // Reconstruct path
        vector<int> path;
        int current = destination;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        reverse(path.begin(), path.end());
        
        return {dist[destination], path};
    }
    
    vector<string> getDirections(const vector<int>& path) {
        vector<string> directions;
        
        if (path.size() < 2) return directions;
        
        for (int i = 0; i < path.size() - 1; i++) {
            int from = path[i];
            int to = path[i + 1];
            
            // Find the edge
            for (const Edge& edge : graph[from]) {
                if (edge.to == to) {
                    string direction = "Continue on ";
                    if (!edge.roadName.empty()) {
                        direction += edge.roadName;
                    } else {
                        direction += "Road " + to_string(from) + "-" + to_string(to);
                    }
                    direction += " for " + to_string(edge.weight) + " minutes";
                    directions.push_back(direction);
                    break;
                }
            }
        }
        
        directions.push_back("You have arrived at your destination!");
        return directions;
    }
    
    // Hàm tính khoảng cách thực tế giữa hai điểm (Haversine formula)
    double calculateRealDistance(int node1, int node2) {
        double lat1 = coordinates[node1].first * M_PI / 180.0;
        double lng1 = coordinates[node1].second * M_PI / 180.0;
        double lat2 = coordinates[node2].first * M_PI / 180.0;
        double lng2 = coordinates[node2].second * M_PI / 180.0;
        
        double dlat = lat2 - lat1;
        double dlng = lng2 - lng1;
        
        double a = sin(dlat/2) * sin(dlat/2) + 
                   cos(lat1) * cos(lat2) * sin(dlng/2) * sin(dlng/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        
        return 6371.0 * c; // Earth radius in km
    }
    
    // Debug function để hiển thị quá trình tìm đường
    void debugNavigation(int start, int destination) {
        cout << "=== DEBUG GPS NAVIGATION ===" << endl;
        cout << "Finding route from " << start << " to " << destination << endl;
        
        auto result = findShortestPath(start, destination);
        double totalTime = result.first;
        vector<int> path = result.second;
        
        cout << "\nShortest path found:" << endl;
        cout << "Total time: " << fixed << setprecision(2) << totalTime << " minutes" << endl;
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
        
        cout << "\nStep-by-step directions:" << endl;
        vector<string> directions = getDirections(path);
        for (int i = 0; i < directions.size(); i++) {
            cout << (i + 1) << ". " << directions[i] << endl;
        }
        
        // Calculate total distance if coordinates are available
        double totalDistance = 0;
        for (int i = 0; i < path.size() - 1; i++) {
            if (coordinates[path[i]].first != 0 || coordinates[path[i]].second != 0) {
                totalDistance += calculateRealDistance(path[i], path[i + 1]);
            }
        }
        
        if (totalDistance > 0) {
            cout << "\nTotal distance: " << fixed << setprecision(2) 
                 << totalDistance << " km" << endl;
            cout << "Average speed: " << fixed << setprecision(2) 
                 << (totalDistance / (totalTime / 60.0)) << " km/h" << endl;
        }
        
        cout << "============================" << endl;
    }
    
    // Hàm tìm đường thay thế
    vector<vector<int>> findAlternativeRoutes(int start, int destination, int numRoutes = 3) {
        vector<vector<int>> routes;
        
        // Tìm đường chính
        auto mainRoute = findShortestPath(start, destination);
        if (mainRoute.first != INFINITY) {
            routes.push_back(mainRoute.second);
        }
        
        // Tìm đường thay thế bằng cách loại bỏ một số cạnh quan trọng
        for (int excludeNode = 0; excludeNode < n && routes.size() < numRoutes; excludeNode++) {
            if (excludeNode == start || excludeNode == destination) continue;
            
            // Tạm thời loại bỏ node này
            vector<vector<Edge>> tempGraph = graph;
            graph[excludeNode].clear();
            for (int i = 0; i < n; i++) {
                auto& edges = graph[i];
                edges.erase(remove_if(edges.begin(), edges.end(),
                    [excludeNode](const Edge& e) { return e.to == excludeNode; }),
                    edges.end());
            }
            
            auto altRoute = findShortestPath(start, destination);
            if (altRoute.first != INFINITY) {
                routes.push_back(altRoute.second);
            }
            
            // Khôi phục graph
            graph = tempGraph;
        }
        
        return routes;
    }
    
    // Hàm tính toán traffic-aware routing
    pair<double, vector<int>> findTrafficAwareRoute(int start, int destination, 
                                                   const map<pair<int,int>, double>& trafficMultipliers) {
        // Tạo graph với traffic multipliers
        vector<vector<Edge>> trafficGraph = graph;
        
        for (int i = 0; i < n; i++) {
            for (auto& edge : trafficGraph[i]) {
                pair<int,int> roadKey = {i, edge.to};
                if (trafficMultipliers.count(roadKey)) {
                    edge.weight *= trafficMultipliers.at(roadKey);
                }
            }
        }
        
        // Temporarily replace graph
        vector<vector<Edge>> originalGraph = graph;
        graph = trafficGraph;
        
        auto result = findShortestPath(start, destination);
        
        // Restore original graph
        graph = originalGraph;
        
        return result;
    }
};

// Hàm so sánh với thuật toán tìm đường khác
void compareWithBFS(GPSNavigation& gps, int start, int destination) {
    cout << "\n=== COMPARISON WITH BFS ===" << endl;
    
    // BFS tìm đường với số bước ít nhất (không tối ưu về thời gian)
    queue<int> q;
    vector<bool> visited(gps.n, false);
    vector<int> parent(gps.n, -1);
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty() && !visited[destination]) {
        int u = q.front();
        q.pop();
        
        // Simulate accessing graph (in real implementation, we'd need access)
        // This is just for demonstration
    }
    
    cout << "BFS finds path with minimum number of hops" << endl;
    cout << "Dijkstra finds path with minimum travel time" << endl;
    cout << "For GPS navigation, time optimization is more important!" << endl;
    cout << "===========================" << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    GPSNavigation gps(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        double time;
        cin >> u >> v >> time;
        gps.addRoad(u, v, time, "Highway-" + to_string(i));
    }
    
    int start, end;
    cin >> start >> end;
    
    auto result = gps.findShortestPath(start, end);
    
    cout << fixed << setprecision(0) << result.first << endl;
    for (int i = 0; i < result.second.size(); i++) {
        cout << result.second[i];
        if (i < result.second.size() - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // gps.debugNavigation(start, end);
    
    // Test alternative routes:
    // auto altRoutes = gps.findAlternativeRoutes(start, end);
    // cout << "Found " << altRoutes.size() << " alternative routes" << endl;
    
    // Test traffic-aware routing:
    // map<pair<int,int>, double> traffic = {{{0,1}, 2.0}, {{1,2}, 1.5}};
    // auto trafficRoute = gps.findTrafficAwareRoute(start, end, traffic);
    // cout << "Traffic-aware route time: " << trafficRoute.first << endl;
    
    return 0;
}