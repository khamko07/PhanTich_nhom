#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <random>
using namespace std;

class ApproximationAlgorithms {
private:
    bool debugMode;
    
public:
    ApproximationAlgorithms(bool debug = false) : debugMode(debug) {}
    
    // ===== VERTEX COVER APPROXIMATION =====
    
    struct VertexCoverResult {
        vector<int> vertices;
        int coverSize;
        double approximationRatio;
    };
    
    // 2-approximation algorithm for Vertex Cover
    VertexCoverResult vertexCoverApprox(const vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> covered(n, false);
        vector<bool> inCover(n, false);
        VertexCoverResult result;
        
        if (debugMode) {
            cout << "=== VERTEX COVER APPROXIMATION ===" << endl;
            cout << "Graph vertices: " << n << endl;
            cout << "Using 2-approximation algorithm" << endl;
        }
        
        // Create edge list
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++) {
            for (int j : graph[i]) {
                if (i < j) { // Avoid duplicate edges
                    edges.push_back({i, j});
                }
            }
        }
        
        if (debugMode) {
            cout << "Total edges: " << edges.size() << endl;
        }
        
        // Greedy approach: pick uncovered edges and add both endpoints
        for (auto& edge : edges) {
            int u = edge.first;
            int v = edge.second;
            
            if (!covered[u] && !covered[v]) {
                // Add both vertices to cover
                inCover[u] = inCover[v] = true;
                covered[u] = covered[v] = true;
                
                // Mark all edges incident to u and v as covered
                for (int neighbor : graph[u]) {
                    covered[neighbor] = true;
                }
                for (int neighbor : graph[v]) {
                    covered[neighbor] = true;
                }
                
                if (debugMode) {
                    cout << "Added vertices " << u << " and " << v << " to cover" << endl;
                }
            }
        }
        
        // Collect result
        for (int i = 0; i < n; i++) {
            if (inCover[i]) {
                result.vertices.push_back(i);
            }
        }
        
        result.coverSize = result.vertices.size();
        result.approximationRatio = 2.0; // Theoretical guarantee
        
        if (debugMode) {
            cout << "Vertex cover: {";
            for (int i = 0; i < result.vertices.size(); i++) {
                cout << result.vertices[i];
                if (i < result.vertices.size() - 1) cout << ", ";
            }
            cout << "}" << endl;
            cout << "Cover size: " << result.coverSize << endl;
            cout << "Approximation ratio: " << result.approximationRatio << endl;
            cout << "==================================" << endl;
        }
        
        return result;
    }
    
    // ===== SET COVER APPROXIMATION =====
    
    struct SetCoverResult {
        vector<int> selectedSets;
        int numSets;
        double approximationRatio;
    };
    
    // Greedy approximation for Set Cover
    SetCoverResult setCoverApprox(const vector<set<int>>& sets, const set<int>& universe) {
        SetCoverResult result;
        set<int> uncovered = universe;
        vector<bool> used(sets.size(), false);
        
        if (debugMode) {
            cout << "=== SET COVER APPROXIMATION ===" << endl;
            cout << "Universe size: " << universe.size() << endl;
            cout << "Number of sets: " << sets.size() << endl;
            cout << "Using greedy approximation" << endl;
        }
        
        while (!uncovered.empty()) {
            int bestSet = -1;
            int maxCover = 0;
            
            // Find set that covers most uncovered elements
            for (int i = 0; i < sets.size(); i++) {
                if (used[i]) continue;
                
                int coverCount = 0;
                for (int element : sets[i]) {
                    if (uncovered.count(element)) {
                        coverCount++;
                    }
                }
                
                if (coverCount > maxCover) {
                    maxCover = coverCount;
                    bestSet = i;
                }
            }
            
            if (bestSet == -1) break; // No more useful sets
            
            // Add best set to solution
            used[bestSet] = true;
            result.selectedSets.push_back(bestSet);
            
            // Remove covered elements
            for (int element : sets[bestSet]) {
                uncovered.erase(element);
            }
            
            if (debugMode) {
                cout << "Selected set " << bestSet << " (covers " << maxCover 
                     << " new elements)" << endl;
                cout << "Remaining uncovered: " << uncovered.size() << endl;
            }
        }
        
        result.numSets = result.selectedSets.size();
        result.approximationRatio = log(universe.size()) + 1; // H_n approximation
        
        if (debugMode) {
            cout << "Selected sets: {";
            for (int i = 0; i < result.selectedSets.size(); i++) {
                cout << result.selectedSets[i];
                if (i < result.selectedSets.size() - 1) cout << ", ";
            }
            cout << "}" << endl;
            cout << "Number of sets: " << result.numSets << endl;
            cout << "Approximation ratio: ≤ " << result.approximationRatio << endl;
            cout << "===============================" << endl;
        }
        
        return result;
    }
    
    // ===== TSP APPROXIMATION =====
    
    struct TSPApproxResult {
        vector<int> tour;
        int totalCost;
        double approximationRatio;
    };
    
    // 2-approximation for metric TSP using MST
    TSPApproxResult tspMSTApprox(const vector<vector<int>>& graph) {
        int n = graph.size();
        TSPApproxResult result;
        
        if (debugMode) {
            cout << "=== TSP MST APPROXIMATION ===" << endl;
            cout << "Cities: " << n << endl;
            cout << "Using MST-based 2-approximation" << endl;
        }
        
        // Step 1: Find MST using Prim's algorithm
        vector<bool> inMST(n, false);
        vector<int> key(n, INT_MAX);
        vector<int> parent(n, -1);
        vector<vector<int>> mstAdj(n);
        
        key[0] = 0;
        int mstCost = 0;
        
        for (int count = 0; count < n; count++) {
            int u = -1;
            for (int v = 0; v < n; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }
            
            inMST[u] = true;
            if (parent[u] != -1) {
                mstAdj[u].push_back(parent[u]);
                mstAdj[parent[u]].push_back(u);
                mstCost += graph[u][parent[u]];
            }
            
            for (int v = 0; v < n; v++) {
                if (!inMST[v] && graph[u][v] < key[v]) {
                    key[v] = graph[u][v];
                    parent[v] = u;
                }
            }
        }
        
        if (debugMode) {
            cout << "MST cost: " << mstCost << endl;
        }
        
        // Step 2: DFS traversal of MST to get tour
        vector<bool> visited(n, false);
        
        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            result.tour.push_back(u);
            
            for (int v : mstAdj[u]) {
                if (!visited[v]) {
                    dfs(v);
                }
            }
        };
        
        dfs(0);
        result.tour.push_back(0); // Return to start
        
        // Step 3: Calculate tour cost
        result.totalCost = 0;
        for (int i = 0; i < result.tour.size() - 1; i++) {
            result.totalCost += graph[result.tour[i]][result.tour[i+1]];
        }
        
        result.approximationRatio = 2.0;
        
        if (debugMode) {
            cout << "Tour: ";
            for (int i = 0; i < result.tour.size(); i++) {
                cout << result.tour[i];
                if (i < result.tour.size() - 1) cout << " -> ";
            }
            cout << endl;
            cout << "Tour cost: " << result.totalCost << endl;
            cout << "Approximation ratio: " << result.approximationRatio << endl;
            cout << "=============================" << endl;
        }
        
        return result;
    }
    
    // Christofides algorithm (1.5-approximation for metric TSP)
    TSPApproxResult tspChristofides(const vector<vector<int>>& graph) {
        // This is a simplified version - full implementation is quite complex
        if (debugMode) {
            cout << "=== TSP CHRISTOFIDES APPROXIMATION ===" << endl;
            cout << "Note: This is a simplified demonstration" << endl;
            cout << "Full Christofides algorithm requires:" << endl;
            cout << "1. MST construction" << endl;
            cout << "2. Find odd-degree vertices" << endl;
            cout << "3. Minimum weight perfect matching" << endl;
            cout << "4. Combine MST and matching" << endl;
            cout << "5. Find Eulerian circuit" << endl;
            cout << "6. Convert to Hamiltonian circuit" << endl;
            cout << "=====================================" << endl;
        }
        
        // For now, return MST approximation
        return tspMSTApprox(graph);
    }
    
    // ===== KNAPSACK APPROXIMATION =====
    
    struct KnapsackResult {
        vector<int> items;
        int totalValue;
        int totalWeight;
        double approximationRatio;
    };
    
    // FPTAS for 0/1 Knapsack
    KnapsackResult knapsackFPTAS(const vector<int>& values, const vector<int>& weights, 
                                 int capacity, double epsilon = 0.1) {
        int n = values.size();
        KnapsackResult result;
        
        if (debugMode) {
            cout << "=== KNAPSACK FPTAS ===" << endl;
            cout << "Items: " << n << endl;
            cout << "Capacity: " << capacity << endl;
            cout << "Epsilon: " << epsilon << endl;
        }
        
        // Find maximum value
        int maxValue = *max_element(values.begin(), values.end());
        
        // Scaling factor
        double K = (epsilon * maxValue) / n;
        
        if (debugMode) {
            cout << "Scaling factor K: " << K << endl;
        }
        
        // Scale values
        vector<int> scaledValues(n);
        for (int i = 0; i < n; i++) {
            scaledValues[i] = (int)(values[i] / K);
        }
        
        // Run DP on scaled values
        int maxScaledValue = accumulate(scaledValues.begin(), scaledValues.end(), 0);
        vector<vector<int>> dp(n + 1, vector<int>(maxScaledValue + 1, INT_MAX));
        vector<vector<bool>> take(n + 1, vector<bool>(maxScaledValue + 1, false));
        
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int v = 0; v <= maxScaledValue; v++) {
                // Don't take item i-1
                dp[i][v] = dp[i-1][v];
                
                // Take item i-1 if possible
                if (v >= scaledValues[i-1] && dp[i-1][v - scaledValues[i-1]] != INT_MAX) {
                    int newWeight = dp[i-1][v - scaledValues[i-1]] + weights[i-1];
                    if (newWeight <= capacity && newWeight < dp[i][v]) {
                        dp[i][v] = newWeight;
                        take[i][v] = true;
                    }
                }
            }
        }
        
        // Find best solution
        int bestValue = 0;
        for (int v = 0; v <= maxScaledValue; v++) {
            if (dp[n][v] <= capacity) {
                bestValue = v;
            }
        }
        
        // Reconstruct solution
        int currentValue = bestValue;
        for (int i = n; i > 0; i--) {
            if (take[i][currentValue]) {
                result.items.push_back(i-1);
                result.totalValue += values[i-1];
                result.totalWeight += weights[i-1];
                currentValue -= scaledValues[i-1];
            }
        }
        
        result.approximationRatio = 1 + epsilon;
        
        if (debugMode) {
            cout << "Selected items: {";
            for (int i = 0; i < result.items.size(); i++) {
                cout << result.items[i];
                if (i < result.items.size() - 1) cout << ", ";
            }
            cout << "}" << endl;
            cout << "Total value: " << result.totalValue << endl;
            cout << "Total weight: " << result.totalWeight << endl;
            cout << "Approximation ratio: " << result.approximationRatio << endl;
            cout << "======================" << endl;
        }
        
        return result;
    }
    
    // ===== PERFORMANCE ANALYSIS =====
    
    void compareApproximationRatios() {
        cout << "\n=== APPROXIMATION RATIOS COMPARISON ===" << endl;
        
        cout << "Problem\t\t\tBest Known Approximation" << endl;
        cout << "-------\t\t\t------------------------" << endl;
        cout << "Vertex Cover\t\t2-approximation" << endl;
        cout << "Set Cover\t\tln(n)-approximation" << endl;
        cout << "TSP (metric)\t\t1.5-approximation (Christofides)" << endl;
        cout << "TSP (general)\t\tNo constant approximation" << endl;
        cout << "Knapsack\t\t(1+ε)-approximation (FPTAS)" << endl;
        cout << "Bin Packing\t\t1.7-approximation" << endl;
        cout << "Max Cut\t\t\t0.878-approximation" << endl;
        
        cout << "\nKey Insights:" << endl;
        cout << "- Some problems have constant approximations" << endl;
        cout << "- Others have logarithmic approximations" << endl;
        cout << "- Some problems cannot be approximated well" << endl;
        cout << "- FPTAS gives arbitrarily good approximations" << endl;
        cout << "=======================================" << endl;
    }
    
    void demonstrateApproximationTradeoffs() {
        cout << "\n=== APPROXIMATION TRADEOFFS ===" << endl;
        
        cout << "Time vs Quality Tradeoffs:" << endl;
        cout << "Algorithm Type\t\tTime\t\tQuality" << endl;
        cout << "--------------\t\t----\t\t-------" << endl;
        cout << "Exact\t\t\tExponential\t100%" << endl;
        cout << "Approximation\t\tPolynomial\t≥ 1/α * OPT" << endl;
        cout << "Heuristic\t\tFast\t\tNo guarantee" << endl;
        cout << "Randomized\t\tFast\t\tExpected good" << endl;
        
        cout << "\nWhen to use approximation algorithms:" << endl;
        cout << "✓ Problem is NP-hard" << endl;
        cout << "✓ Need polynomial-time solution" << endl;
        cout << "✓ Can tolerate suboptimal solutions" << endl;
        cout << "✓ Have approximation ratio guarantees" << endl;
        
        cout << "\nFPTAS (Fully Polynomial-Time Approximation Scheme):" << endl;
        cout << "- Time: polynomial in n and 1/ε" << endl;
        cout << "- Quality: (1+ε)-approximation" << endl;
        cout << "- Best of both worlds for some problems" << endl;
        cout << "===============================" << endl;
    }
};

// Utility functions
vector<vector<int>> generateCompleteGraph(int n) {
    vector<vector<int>> graph(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                graph[i][j] = rand() % 100 + 1;
            }
        }
    }
    
    return graph;
}

int main() {
    srand(time(nullptr));
    
    int problemType;
    cin >> problemType;
    
    ApproximationAlgorithms approx(false); // Set to true for debug mode
    
    if (problemType == 1) {
        // Vertex Cover
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> graph(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        auto result = approx.vertexCoverApprox(graph);
        cout << result.coverSize << endl;
        
    } else if (problemType == 2) {
        // Set Cover
        int n, m;
        cin >> n >> m; // n = universe size, m = number of sets
        
        set<int> universe;
        for (int i = 0; i < n; i++) {
            universe.insert(i);
        }
        
        vector<set<int>> sets(m);
        for (int i = 0; i < m; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int element;
                cin >> element;
                sets[i].insert(element);
            }
        }
        
        auto result = approx.setCoverApprox(sets, universe);
        cout << result.numSets << endl;
        
    } else if (problemType == 3) {
        // TSP Approximation
        int n;
        cin >> n;
        
        vector<vector<int>> graph(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> graph[i][j];
            }
        }
        
        auto result = approx.tspMSTApprox(graph);
        cout << result.totalCost << endl;
        
    } else if (problemType == 4) {
        // Knapsack FPTAS
        int n, capacity;
        double epsilon;
        cin >> n >> capacity >> epsilon;
        
        vector<int> values(n), weights(n);
        for (int i = 0; i < n; i++) {
            cin >> values[i] >> weights[i];
        }
        
        auto result = approx.knapsackFPTAS(values, weights, capacity, epsilon);
        cout << result.totalValue << endl;
    }
    
    // Uncomment for demonstrations:
    
    // Approximation ratios comparison
    // approx.compareApproximationRatios();
    
    // Tradeoffs demonstration
    // approx.demonstrateApproximationTradeoffs();
    
    return 0;
}