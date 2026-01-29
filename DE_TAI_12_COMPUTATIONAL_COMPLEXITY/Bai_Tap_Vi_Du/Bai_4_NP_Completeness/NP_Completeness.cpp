#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>
#include <map>
#include <bitset>
using namespace std;

class NPCompletenessDemo {
private:
    bool debugMode;
    
public:
    NPCompletenessDemo(bool debug = false) : debugMode(debug) {}
    
    // ===== SUBSET SUM PROBLEM (NP-Complete) =====
    
    // Brute force solution - O(2^n)
    bool subsetSumBruteForce(const vector<int>& nums, int target) {
        int n = nums.size();
        
        if (debugMode) {
            cout << "=== SUBSET SUM - BRUTE FORCE ===" << endl;
            cout << "Array: ";
            for (int x : nums) cout << x << " ";
            cout << "\nTarget: " << target << endl;
            cout << "Checking all 2^" << n << " = " << (1 << n) << " subsets" << endl;
        }
        
        // Try all possible subsets using bit manipulation
        for (int mask = 0; mask < (1 << n); mask++) {
            int sum = 0;
            vector<int> subset;
            
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    sum += nums[i];
                    subset.push_back(nums[i]);
                }
            }
            
            if (debugMode && subset.size() <= 5) { // Only show small subsets
                cout << "Subset: {";
                for (int i = 0; i < subset.size(); i++) {
                    cout << subset[i];
                    if (i < subset.size() - 1) cout << ", ";
                }
                cout << "} = " << sum << endl;
            }
            
            if (sum == target) {
                if (debugMode) {
                    cout << "Found solution: {";
                    for (int i = 0; i < subset.size(); i++) {
                        cout << subset[i];
                        if (i < subset.size() - 1) cout << ", ";
                    }
                    cout << "}" << endl;
                    cout << "===============================" << endl;
                }
                return true;
            }
        }
        
        if (debugMode) {
            cout << "No solution found" << endl;
            cout << "===============================" << endl;
        }
        return false;
    }
    
    // Dynamic Programming solution - O(n * sum)
    bool subsetSumDP(const vector<int>& nums, int target) {
        int n = nums.size();
        
        if (debugMode) {
            cout << "=== SUBSET SUM - DYNAMIC PROGRAMMING ===" << endl;
            cout << "Array: ";
            for (int x : nums) cout << x << " ";
            cout << "\nTarget: " << target << endl;
            cout << "DP table size: " << n << " x " << target << endl;
        }
        
        // dp[i][j] = true if subset of first i elements has sum j
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        
        // Base case: sum 0 is always possible (empty subset)
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                // Don't include current element
                dp[i][j] = dp[i-1][j];
                
                // Include current element if possible
                if (j >= nums[i-1]) {
                    dp[i][j] = dp[i][j] || dp[i-1][j - nums[i-1]];
                }
            }
        }
        
        if (debugMode) {
            cout << "DP computation completed" << endl;
            cout << "Result: " << (dp[n][target] ? "Found" : "Not found") << endl;
            cout << "=====================================" << endl;
        }
        
        return dp[n][target];
    }
    
    // ===== TRAVELING SALESMAN PROBLEM (NP-Hard) =====
    
    struct TSPResult {
        vector<int> path;
        int minCost;
        int comparisons;
    };
    
    // Brute force TSP - O(n!)
    TSPResult tspBruteForce(const vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> cities;
        for (int i = 1; i < n; i++) {
            cities.push_back(i);
        }
        
        TSPResult result;
        result.minCost = INT_MAX;
        result.comparisons = 0;
        
        if (debugMode) {
            cout << "=== TSP - BRUTE FORCE ===" << endl;
            cout << "Cities: " << n << endl;
            cout << "Permutations to check: " << factorial(n-1) << endl;
        }
        
        do {
            int currentCost = 0;
            int current = 0; // Start from city 0
            
            // Calculate cost of current permutation
            for (int city : cities) {
                currentCost += graph[current][city];
                current = city;
            }
            currentCost += graph[current][0]; // Return to start
            
            result.comparisons++;
            
            if (currentCost < result.minCost) {
                result.minCost = currentCost;
                result.path = {0};
                for (int city : cities) {
                    result.path.push_back(city);
                }
                result.path.push_back(0);
                
                if (debugMode) {
                    cout << "New best path: ";
                    for (int i = 0; i < result.path.size(); i++) {
                        cout << result.path[i];
                        if (i < result.path.size() - 1) cout << " -> ";
                    }
                    cout << " (cost: " << result.minCost << ")" << endl;
                }
            }
            
        } while (next_permutation(cities.begin(), cities.end()));
        
        if (debugMode) {
            cout << "Total permutations checked: " << result.comparisons << endl;
            cout << "=========================" << endl;
        }
        
        return result;
    }
    
    // Dynamic Programming TSP with bitmask - O(n^2 * 2^n)
    TSPResult tspDP(const vector<vector<int>>& graph) {
        int n = graph.size();
        
        if (debugMode) {
            cout << "=== TSP - DYNAMIC PROGRAMMING ===" << endl;
            cout << "Cities: " << n << endl;
            cout << "States: " << n << " x " << (1 << n) << " = " << (n * (1 << n)) << endl;
        }
        
        // dp[mask][i] = minimum cost to visit all cities in mask, ending at city i
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
        vector<vector<int>> parent(1 << n, vector<int>(n, -1));
        
        dp[1][0] = 0; // Start at city 0
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (!(mask & (1 << u)) || dp[mask][u] == INT_MAX) continue;
                
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue; // Already visited
                    
                    int newMask = mask | (1 << v);
                    int newCost = dp[mask][u] + graph[u][v];
                    
                    if (newCost < dp[newMask][v]) {
                        dp[newMask][v] = newCost;
                        parent[newMask][v] = u;
                    }
                }
            }
        }
        
        // Find minimum cost to return to start
        TSPResult result;
        result.minCost = INT_MAX;
        int lastCity = -1;
        
        for (int i = 1; i < n; i++) {
            int cost = dp[(1 << n) - 1][i] + graph[i][0];
            if (cost < result.minCost) {
                result.minCost = cost;
                lastCity = i;
            }
        }
        
        // Reconstruct path
        result.path.clear();
        int mask = (1 << n) - 1;
        int current = lastCity;
        
        while (current != -1) {
            result.path.push_back(current);
            int prev = parent[mask][current];
            mask ^= (1 << current);
            current = prev;
        }
        
        reverse(result.path.begin(), result.path.end());
        result.path.push_back(0); // Return to start
        
        if (debugMode) {
            cout << "DP computation completed" << endl;
            cout << "Optimal path: ";
            for (int i = 0; i < result.path.size(); i++) {
                cout << result.path[i];
                if (i < result.path.size() - 1) cout << " -> ";
            }
            cout << " (cost: " << result.minCost << ")" << endl;
            cout << "=================================" << endl;
        }
        
        return result;
    }
    
    // ===== GRAPH COLORING PROBLEM (NP-Complete) =====
    
    bool isValidColoring(const vector<vector<int>>& graph, const vector<int>& colors) {
        int n = graph.size();
        
        for (int i = 0; i < n; i++) {
            for (int j : graph[i]) {
                if (colors[i] == colors[j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool graphColoringBacktrack(const vector<vector<int>>& graph, vector<int>& colors, 
                               int vertex, int numColors, int& attempts) {
        int n = graph.size();
        
        if (vertex == n) {
            return isValidColoring(graph, colors);
        }
        
        for (int color = 1; color <= numColors; color++) {
            colors[vertex] = color;
            attempts++;
            
            // Check if current coloring is valid so far
            bool valid = true;
            for (int neighbor : graph[vertex]) {
                if (neighbor < vertex && colors[neighbor] == color) {
                    valid = false;
                    break;
                }
            }
            
            if (valid && graphColoringBacktrack(graph, colors, vertex + 1, numColors, attempts)) {
                return true;
            }
        }
        
        colors[vertex] = 0;
        return false;
    }
    
    int findChromaticNumber(const vector<vector<int>>& graph) {
        int n = graph.size();
        
        if (debugMode) {
            cout << "=== GRAPH COLORING ===" << endl;
            cout << "Vertices: " << n << endl;
            cout << "Finding chromatic number..." << endl;
        }
        
        for (int colors = 1; colors <= n; colors++) {
            vector<int> coloring(n, 0);
            int attempts = 0;
            
            if (debugMode) {
                cout << "Trying with " << colors << " colors..." << endl;
            }
            
            if (graphColoringBacktrack(graph, coloring, 0, colors, attempts)) {
                if (debugMode) {
                    cout << "Success! Coloring found: ";
                    for (int i = 0; i < n; i++) {
                        cout << "v" << i << ":c" << coloring[i] << " ";
                    }
                    cout << "\nAttempts: " << attempts << endl;
                    cout << "======================" << endl;
                }
                return colors;
            }
            
            if (debugMode) {
                cout << "Failed after " << attempts << " attempts" << endl;
            }
        }
        
        return n; // Worst case
    }
    
    // ===== PERFORMANCE ANALYSIS =====
    
    void analyzeComplexityGrowth() {
        cout << "\n=== COMPLEXITY GROWTH ANALYSIS ===" << endl;
        
        vector<int> sizes = {5, 10, 15, 20};
        
        cout << "Problem Size vs Time Complexity:" << endl;
        cout << "n\tO(n)\tO(n²)\tO(2^n)\tO(n!)" << endl;
        cout << "---\t----\t-----\t------\t----" << endl;
        
        for (int n : sizes) {
            cout << n << "\t" << n << "\t" << (n*n) << "\t" 
                 << (1 << min(n, 20)) << "\t";
            
            if (n <= 10) {
                cout << factorial(n);
            } else {
                cout << "huge";
            }
            cout << endl;
        }
        
        cout << "\nObservation: Exponential and factorial complexities" << endl;
        cout << "become intractable very quickly!" << endl;
        cout << "===================================" << endl;
    }
    
    void demonstrateNPvsP() {
        cout << "\n=== P vs NP DEMONSTRATION ===" << endl;
        
        cout << "P Problems (Polynomial Time):" << endl;
        cout << "- Sorting: O(n log n)" << endl;
        cout << "- Shortest Path: O(V log V + E)" << endl;
        cout << "- Matrix Multiplication: O(n³)" << endl;
        cout << "- Linear Programming: Polynomial" << endl;
        
        cout << "\nNP-Complete Problems:" << endl;
        cout << "- Subset Sum: Best known O(2^n)" << endl;
        cout << "- TSP: Best known O(n!)" << endl;
        cout << "- Graph Coloring: Best known O(k^n)" << endl;
        cout << "- SAT: Best known O(2^n)" << endl;
        
        cout << "\nKey Insight: If any NP-Complete problem" << endl;
        cout << "can be solved in polynomial time, then P = NP!" << endl;
        cout << "=============================" << endl;
    }
    
private:
    long long factorial(int n) {
        if (n <= 1) return 1;
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
            if (result > 1e9) return 1e9; // Prevent overflow
        }
        return result;
    }
};

// Utility functions for testing
vector<vector<int>> generateRandomGraph(int n, double density = 0.5) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)rand() / RAND_MAX < density) {
                int weight = rand() % 100 + 1;
                graph[i][j] = graph[j][i] = weight;
            }
        }
    }
    
    // Ensure connected graph
    for (int i = 0; i < n - 1; i++) {
        if (graph[i][i+1] == 0) {
            graph[i][i+1] = graph[i+1][i] = rand() % 100 + 1;
        }
    }
    
    return graph;
}

vector<vector<int>> generateRandomAdjacencyList(int n, double density = 0.3) {
    vector<vector<int>> graph(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)rand() / RAND_MAX < density) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    
    return graph;
}

int main() {
    // Read problem type
    int problemType;
    cin >> problemType;
    
    NPCompletenessDemo demo(false); // Set to true for debug mode
    
    if (problemType == 1) {
        // Subset Sum Problem
        int n, target;
        cin >> n >> target;
        
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        
        bool result = demo.subsetSumDP(nums, target);
        cout << (result ? "YES" : "NO") << endl;
        
    } else if (problemType == 2) {
        // TSP Problem
        int n;
        cin >> n;
        
        vector<vector<int>> graph(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> graph[i][j];
            }
        }
        
        auto result = demo.tspDP(graph);
        cout << result.minCost << endl;
        
    } else if (problemType == 3) {
        // Graph Coloring
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> graph(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        int chromaticNumber = demo.findChromaticNumber(graph);
        cout << chromaticNumber << endl;
    }
    
    // Uncomment for demonstrations:
    
    // Complexity growth analysis
    // demo.analyzeComplexityGrowth();
    
    // P vs NP demonstration
    // demo.demonstrateNPvsP();
    
    // Performance comparison
    // NPCompletenessDemo debugDemo(true);
    // vector<int> testNums = {3, 34, 4, 12, 5, 2};
    // debugDemo.subsetSumBruteForce(testNums, 9);
    // debugDemo.subsetSumDP(testNums, 9);
    
    return 0;
}