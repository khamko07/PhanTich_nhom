#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <cmath>
#include <chrono>
using namespace std;

class SpaceComplexityAnalyzer {
private:
    bool debugMode;
    
public:
    SpaceComplexityAnalyzer(bool debug = false) : debugMode(debug) {}
    
    // ===== FACTORIAL IMPLEMENTATIONS =====
    
    // Recursive factorial - O(n) space due to call stack
    long long factorialRecursive(int n, int depth = 0) {
        if (debugMode) {
            cout << "Recursive call depth: " << depth << ", n = " << n << endl;
        }
        
        if (n <= 1) {
            if (debugMode) {
                cout << "Base case reached at depth: " << depth << endl;
            }
            return 1;
        }
        
        return n * factorialRecursive(n - 1, depth + 1);
    }
    
    // Iterative factorial - O(1) space
    long long factorialIterative(int n) {
        if (debugMode) {
            cout << "Iterative factorial - using O(1) space" << endl;
        }
        
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
            if (debugMode && i <= 5) {
                cout << "Step " << i << ": result = " << result << endl;
            }
        }
        
        return result;
    }
    
    // ===== FIBONACCI IMPLEMENTATIONS =====
    
    // Recursive fibonacci - O(n) space due to call stack
    long long fibonacciRecursive(int n, int depth = 0) {
        if (debugMode && depth < 10) {
            cout << "Fib recursive call: n = " << n << ", depth = " << depth << endl;
        }
        
        if (n <= 1) return n;
        
        return fibonacciRecursive(n - 1, depth + 1) + fibonacciRecursive(n - 2, depth + 1);
    }
    
    // Iterative fibonacci - O(1) space
    long long fibonacciIterative(int n) {
        if (debugMode) {
            cout << "Iterative fibonacci - using O(1) space" << endl;
        }
        
        if (n <= 1) return n;
        
        long long prev2 = 0, prev1 = 1, current;
        
        for (int i = 2; i <= n; i++) {
            current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
            
            if (debugMode && i <= 10) {
                cout << "F(" << i << ") = " << current << endl;
            }
        }
        
        return current;
    }
    
    // Memoized fibonacci - O(n) space for memoization table
    long long fibonacciMemoized(int n, unordered_map<int, long long>& memo) {
        if (debugMode && memo.size() < 10) {
            cout << "Memoized call: n = " << n << ", memo size = " << memo.size() << endl;
        }
        
        if (n <= 1) return n;
        
        if (memo.find(n) != memo.end()) {
            if (debugMode) {
                cout << "Cache hit for n = " << n << endl;
            }
            return memo[n];
        }
        
        memo[n] = fibonacciMemoized(n - 1, memo) + fibonacciMemoized(n - 2, memo);
        return memo[n];
    }
    
    // ===== TREE TRAVERSAL IMPLEMENTATIONS =====
    
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    
    // Recursive DFS - O(h) space where h is height
    void dfsRecursive(TreeNode* root, vector<int>& result, int depth = 0) {
        if (!root) return;
        
        if (debugMode) {
            cout << "DFS Recursive: visiting " << root->val << " at depth " << depth << endl;
        }
        
        result.push_back(root->val);
        dfsRecursive(root->left, result, depth + 1);
        dfsRecursive(root->right, result, depth + 1);
    }
    
    // Iterative DFS using stack - O(h) space for stack
    void dfsIterative(TreeNode* root, vector<int>& result) {
        if (!root) return;
        
        stack<TreeNode*> st;
        st.push(root);
        
        if (debugMode) {
            cout << "DFS Iterative - using explicit stack" << endl;
        }
        
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            
            result.push_back(node->val);
            
            if (debugMode) {
                cout << "Visiting: " << node->val << ", stack size: " << st.size() << endl;
            }
            
            // Push right first, then left (so left is processed first)
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
    }
    
    // BFS using queue - O(w) space where w is maximum width
    void bfsIterative(TreeNode* root, vector<int>& result) {
        if (!root) return;
        
        queue<TreeNode*> q;
        q.push(root);
        
        if (debugMode) {
            cout << "BFS Iterative - using queue" << endl;
        }
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            result.push_back(node->val);
            
            if (debugMode) {
                cout << "Visiting: " << node->val << ", queue size: " << q.size() << endl;
            }
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    // ===== SPACE COMPLEXITY ANALYSIS =====
    
    struct SpaceAnalysisResult {
        string recursiveComplexity;
        string iterativeComplexity;
        int maxRecursiveDepth;
        int iterativeExtraSpace;
    };
    
    SpaceAnalysisResult analyzeAlgorithm(int algorithmType, int n) {
        SpaceAnalysisResult result;
        
        if (debugMode) {
            cout << "=== SPACE COMPLEXITY ANALYSIS ===" << endl;
            cout << "Algorithm type: " << algorithmType << ", n = " << n << endl;
        }
        
        switch (algorithmType) {
            case 1: // Factorial
                result.recursiveComplexity = "O(n)";
                result.iterativeComplexity = "O(1)";
                result.maxRecursiveDepth = n;
                result.iterativeExtraSpace = 1;
                
                if (debugMode) {
                    cout << "Factorial Analysis:" << endl;
                    cout << "- Recursive: O(n) due to call stack" << endl;
                    cout << "- Iterative: O(1) using only variables" << endl;
                }
                break;
                
            case 2: // Fibonacci
                result.recursiveComplexity = "O(n)";
                result.iterativeComplexity = "O(1)";
                result.maxRecursiveDepth = n;
                result.iterativeExtraSpace = 1;
                
                if (debugMode) {
                    cout << "Fibonacci Analysis:" << endl;
                    cout << "- Recursive: O(n) call stack depth" << endl;
                    cout << "- Iterative: O(1) using 3 variables" << endl;
                    cout << "- Memoized: O(n) for lookup table" << endl;
                }
                break;
                
            case 3: // Tree Traversal
                result.recursiveComplexity = "O(h)";
                result.iterativeComplexity = "O(h)";
                result.maxRecursiveDepth = (int)log2(n) + 1; // Assuming balanced tree
                result.iterativeExtraSpace = (int)log2(n) + 1;
                
                if (debugMode) {
                    cout << "Tree Traversal Analysis:" << endl;
                    cout << "- DFS Recursive: O(h) call stack" << endl;
                    cout << "- DFS Iterative: O(h) explicit stack" << endl;
                    cout << "- BFS: O(w) queue, w = max width" << endl;
                }
                break;
                
            default:
                result.recursiveComplexity = "Unknown";
                result.iterativeComplexity = "Unknown";
                result.maxRecursiveDepth = 0;
                result.iterativeExtraSpace = 0;
        }
        
        if (debugMode) {
            cout << "=================================" << endl;
        }
        
        return result;
    }
    
    // ===== MEMORY USAGE DEMONSTRATION =====
    
    void demonstrateMemoryUsage() {
        cout << "\n=== MEMORY USAGE DEMONSTRATION ===" << endl;
        
        // Different data structures and their space complexity
        cout << "Data Structure Space Complexities:" << endl;
        cout << "- Array[n]: O(n)" << endl;
        cout << "- Vector<int>(n): O(n)" << endl;
        cout << "- Stack<int>: O(n) worst case" << endl;
        cout << "- Queue<int>: O(n) worst case" << endl;
        cout << "- Map<int,int>: O(n)" << endl;
        cout << "- Set<int>: O(n)" << endl;
        cout << "- Unordered_map<int,int>: O(n)" << endl;
        
        cout << "\nAlgorithm Space Complexities:" << endl;
        cout << "- Bubble Sort: O(1) - in-place" << endl;
        cout << "- Merge Sort: O(n) - auxiliary array" << endl;
        cout << "- Quick Sort: O(log n) - recursion stack" << endl;
        cout << "- Heap Sort: O(1) - in-place" << endl;
        cout << "- Counting Sort: O(k) - counting array" << endl;
        
        cout << "==================================" << endl;
    }
    
    // ===== SPACE-TIME TRADEOFFS =====
    
    void demonstrateSpaceTimeTradeoffs() {
        cout << "\n=== SPACE-TIME TRADEOFFS ===" << endl;
        
        cout << "Classic Tradeoffs:" << endl;
        cout << "1. Memoization:" << endl;
        cout << "   - More space O(n) -> Less time O(n)" << endl;
        cout << "   - Example: Fibonacci DP vs naive recursion" << endl;
        
        cout << "\n2. Hash Tables:" << endl;
        cout << "   - More space O(n) -> Faster lookup O(1)" << endl;
        cout << "   - Example: Array lookup vs linear search" << endl;
        
        cout << "\n3. Precomputation:" << endl;
        cout << "   - More space O(n) -> Faster queries O(1)" << endl;
        cout << "   - Example: Prefix sums, lookup tables" << endl;
        
        cout << "\n4. Auxiliary Data Structures:" << endl;
        cout << "   - More space -> Better time complexity" << endl;
        cout << "   - Example: Merge sort auxiliary array" << endl;
        
        cout << "============================" << endl;
    }
    
    // ===== PERFORMANCE COMPARISON =====
    
    void compareImplementations(int n) {
        cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
        cout << "Testing with n = " << n << endl;
        
        // Factorial comparison
        auto start = chrono::high_resolution_clock::now();
        long long result1 = factorialIterative(n);
        auto end = chrono::high_resolution_clock::now();
        auto iterTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        start = chrono::high_resolution_clock::now();
        long long result2 = factorialRecursive(n);
        end = chrono::high_resolution_clock::now();
        auto recTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "Factorial Results:" << endl;
        cout << "- Iterative: " << iterTime.count() << " μs, Space: O(1)" << endl;
        cout << "- Recursive: " << recTime.count() << " μs, Space: O(n)" << endl;
        cout << "- Results match: " << (result1 == result2 ? "Yes" : "No") << endl;
        
        // Fibonacci comparison (smaller n to avoid timeout)
        int fibN = min(n, 40);
        
        start = chrono::high_resolution_clock::now();
        long long fib1 = fibonacciIterative(fibN);
        end = chrono::high_resolution_clock::now();
        auto fibIterTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        unordered_map<int, long long> memo;
        start = chrono::high_resolution_clock::now();
        long long fib2 = fibonacciMemoized(fibN, memo);
        end = chrono::high_resolution_clock::now();
        auto fibMemoTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "\nFibonacci Results (n=" << fibN << "):" << endl;
        cout << "- Iterative: " << fibIterTime.count() << " μs, Space: O(1)" << endl;
        cout << "- Memoized: " << fibMemoTime.count() << " μs, Space: O(n)" << endl;
        cout << "- Memo table size: " << memo.size() << endl;
        cout << "- Results match: " << (fib1 == fib2 ? "Yes" : "No") << endl;
        
        cout << "===============================" << endl;
    }
    
    // Helper function to create a sample binary tree
    TreeNode* createSampleTree() {
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(7);
        return root;
    }
};

int main() {
    int algorithmType, n;
    cin >> algorithmType >> n;
    
    SpaceComplexityAnalyzer analyzer(false); // Set to true for debug mode
    
    auto result = analyzer.analyzeAlgorithm(algorithmType, n);
    
    cout << result.recursiveComplexity << endl;
    cout << result.iterativeComplexity << endl;
    cout << result.maxRecursiveDepth << endl;
    cout << result.iterativeExtraSpace << endl;
    
    // Uncomment for demonstrations:
    
    // Debug mode demonstration
    // SpaceComplexityAnalyzer debugAnalyzer(true);
    // debugAnalyzer.analyzeAlgorithm(algorithmType, min(n, 10));
    
    // Memory usage demonstration
    // analyzer.demonstrateMemoryUsage();
    
    // Space-time tradeoffs
    // analyzer.demonstrateSpaceTimeTradeoffs();
    
    // Performance comparison
    // if (n <= 20) {
    //     analyzer.compareImplementations(n);
    // }
    
    return 0;
}