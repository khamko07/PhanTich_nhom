#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class PageRank {
private:
    vector<vector<int>> graph;
    vector<double> ranks;
    double damping;
    int n;
    
public:
    PageRank(int nodes, double d = 0.85) : n(nodes), damping(d) {
        graph.resize(n);
        ranks.resize(n, 1.0 / n);
    }
    
    void addLink(int from, int to) {
        graph[from].push_back(to);
    }
    
    void calculatePageRank(int iterations) {
        for (int iter = 0; iter < iterations; iter++) {
            vector<double> newRanks(n, (1.0 - damping) / n);
            
            for (int i = 0; i < n; i++) {
                if (!graph[i].empty()) {
                    double contribution = ranks[i] / graph[i].size();
                    for (int neighbor : graph[i]) {
                        newRanks[neighbor] += damping * contribution;
                    }
                } else {
                    // Dangling node - distribute equally
                    double contribution = ranks[i] / n;
                    for (int j = 0; j < n; j++) {
                        newRanks[j] += damping * contribution;
                    }
                }
            }
            
            ranks = newRanks;
        }
    }
    
    void printRanks() {
        for (int i = 0; i < n; i++) {
            cout << fixed << setprecision(4) << ranks[i] << endl;
        }
    }
    
    // Debug function để hiển thị quá trình tính toán
    void debugPageRank(int iterations) {
        cout << "=== DEBUG PAGERANK CALCULATION ===" << endl;
        cout << "Initial ranks: ";
        for (double rank : ranks) {
            cout << fixed << setprecision(4) << rank << " ";
        }
        cout << endl;
        
        for (int iter = 0; iter < iterations; iter++) {
            cout << "\nIteration " << (iter + 1) << ":" << endl;
            
            vector<double> newRanks(n, (1.0 - damping) / n);
            cout << "Base rank (1-d)/n = " << (1.0 - damping) / n << endl;
            
            for (int i = 0; i < n; i++) {
                if (!graph[i].empty()) {
                    double contribution = ranks[i] / graph[i].size();
                    cout << "Node " << i << " contributes " << contribution 
                         << " to each of its " << graph[i].size() << " neighbors" << endl;
                    
                    for (int neighbor : graph[i]) {
                        newRanks[neighbor] += damping * contribution;
                    }
                }
            }
            
            ranks = newRanks;
            cout << "New ranks: ";
            for (double rank : ranks) {
                cout << fixed << setprecision(4) << rank << " ";
            }
            cout << endl;
        }
        cout << "=================================" << endl;
    }
    
    // Hàm phân tích convergence
    void analyzeConvergence(int maxIterations) {
        cout << "\n=== CONVERGENCE ANALYSIS ===" << endl;
        vector<double> prevRanks = ranks;
        
        for (int iter = 1; iter <= maxIterations; iter++) {
            calculatePageRank(1);
            
            double maxDiff = 0;
            for (int i = 0; i < n; i++) {
                maxDiff = max(maxDiff, abs(ranks[i] - prevRanks[i]));
            }
            
            cout << "Iteration " << iter << ": Max difference = " 
                 << scientific << setprecision(6) << maxDiff << endl;
            
            if (maxDiff < 1e-6) {
                cout << "Converged after " << iter << " iterations!" << endl;
                break;
            }
            
            prevRanks = ranks;
        }
        cout << "============================" << endl;
    }
};

// Hàm so sánh với thuật toán khác
void compareWithSimpleRanking(const vector<vector<int>>& graph) {
    cout << "\n=== COMPARISON WITH SIMPLE RANKING ===" << endl;
    
    int n = graph.size();
    vector<int> inDegree(n, 0);
    
    // Tính in-degree
    for (int i = 0; i < n; i++) {
        for (int neighbor : graph[i]) {
            inDegree[neighbor]++;
        }
    }
    
    cout << "Simple ranking (by in-degree):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << inDegree[i] << " incoming links" << endl;
    }
    
    cout << "PageRank considers link quality, not just quantity!" << endl;
    cout << "=======================================" << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    PageRank pr(n);
    vector<vector<int>> adjacencyList(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        pr.addLink(u, v);
        adjacencyList[u].push_back(v);
    }
    
    int iterations;
    cin >> iterations;
    
    pr.calculatePageRank(iterations);
    pr.printRanks();
    
    // Uncomment để xem debug info:
    // pr.debugPageRank(5);
    // pr.analyzeConvergence(50);
    // compareWithSimpleRanking(adjacencyList);
    
    return 0;
}