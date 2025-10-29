#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;

class AmortizedAnalysis {
private:
    bool debugMode;
    
public:
    AmortizedAnalysis(bool debug = false) : debugMode(debug) {}
    
    // Dynamic Array with Amortized O(1) insertion
    class DynamicArray {
    private:
        int* arr;
        int size;
        int capacity;
        int totalOperations;
        int resizeOperations;
        bool debug;
        
    public:
        DynamicArray(bool debugMode = false) : size(0), capacity(1), totalOperations(0), resizeOperations(0), debug(debugMode) {
            arr = new int[capacity];
            if (debug) {
                cout << "=== DYNAMIC ARRAY AMORTIZED ANALYSIS ===" << endl;
                cout << "Initial capacity: " << capacity << endl;
            }
        }
        
        ~DynamicArray() {
            delete[] arr;
        }
        
        void push_back(int value) {
            totalOperations++;
            
            if (size == capacity) {
                resize();
            }
            
            arr[size++] = value;
            
            if (debug) {
                cout << "Inserted " << value << " at position " << (size-1) 
                     << ", size: " << size << ", capacity: " << capacity << endl;
            }
        }
        
        int getSize() const { return size; }
        int getCapacity() const { return capacity; }
        int getTotalOperations() const { return totalOperations; }
        int getResizeOperations() const { return resizeOperations; }
        
        double getAmortizedCost() const {
            return totalOperations > 0 ? (double)getTotalCost() / totalOperations : 0;
        }
        
        int getTotalCost() const {
            // Cost = normal insertions + resize costs
            // Resize cost = copying all elements during resize
            int resizeCost = 0;
            int cap = 1;
            while (cap < capacity) {
                resizeCost += cap;  // Cost of copying 'cap' elements
                cap *= 2;
            }
            return totalOperations + resizeCost;
        }
        
        void printAnalysis() const {
            cout << "\n--- Amortized Analysis ---" << endl;
            cout << "Total insertions: " << totalOperations << endl;
            cout << "Resize operations: " << resizeOperations << endl;
            cout << "Total cost: " << getTotalCost() << endl;
            cout << "Amortized cost per operation: " << getAmortizedCost() << endl;
            cout << "Theoretical amortized cost: O(1)" << endl;
        }
        
    private:
        void resize() {
            resizeOperations++;
            int oldCapacity = capacity;
            capacity *= 2;
            
            int* newArr = new int[capacity];
            
            // Copy all elements (this is the expensive operation)
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            
            delete[] arr;
            arr = newArr;
            
            if (debug) {
                cout << "RESIZE: " << oldCapacity << " -> " << capacity 
                     << " (copied " << size << " elements)" << endl;
            }
        }
    };
    
    // Binary Counter with Amortized Analysis
    class BinaryCounter {
    private:
        vector<bool> bits;
        int totalIncrements;
        int totalFlips;
        bool debug;
        
    public:
        BinaryCounter(int numBits, bool debugMode = false) : bits(numBits, false), totalIncrements(0), totalFlips(0), debug(debugMode) {
            if (debug) {
                cout << "\n=== BINARY COUNTER AMORTIZED ANALYSIS ===" << endl;
                cout << "Counter with " << numBits << " bits" << endl;
            }
        }
        
        void increment() {
            totalIncrements++;
            int flipsThisOperation = 0;
            
            if (debug) {
                cout << "Before increment " << totalIncrements << ": ";
                printBinary();
            }
            
            int i = 0;
            while (i < bits.size() && bits[i]) {
                bits[i] = false;  // Flip from 1 to 0
                flipsThisOperation++;
                totalFlips++;
                i++;
            }
            
            if (i < bits.size()) {
                bits[i] = true;   // Set first 0 to 1
                flipsThisOperation++;
                totalFlips++;
            }
            
            if (debug) {
                cout << "After increment:  ";
                printBinary();
                cout << "Flips in this operation: " << flipsThisOperation << endl;
            }
        }
        
        void printAnalysis() const {
            cout << "\n--- Binary Counter Analysis ---" << endl;
            cout << "Total increments: " << totalIncrements << endl;
            cout << "Total bit flips: " << totalFlips << endl;
            cout << "Average flips per increment: " << (double)totalFlips / totalIncrements << endl;
            cout << "Theoretical amortized cost: O(1)" << endl;
            
            // Show flip frequency for each bit position
            cout << "Bit flip frequencies:" << endl;
            for (int i = 0; i < bits.size(); i++) {
                int expectedFlips = totalIncrements / (1 << (i + 1));
                cout << "Bit " << i << ": ~" << expectedFlips << " flips" << endl;
            }
        }
        
    private:
        void printBinary() const {
            for (int i = bits.size() - 1; i >= 0; i--) {
                cout << (bits[i] ? '1' : '0');
            }
            cout << endl;
        }
    };
    
    // Stack with MultiPop - Accounting Method
    class StackWithMultiPop {
    private:
        vector<int> stack;
        int totalPushes;
        int totalPops;
        int totalCredits;
        bool debug;
        
    public:
        StackWithMultiPop(bool debugMode = false) : totalPushes(0), totalPops(0), totalCredits(0), debug(debugMode) {
            if (debug) {
                cout << "\n=== STACK WITH MULTIPOP - ACCOUNTING METHOD ===" << endl;
            }
        }
        
        void push(int value) {
            stack.push_back(value);
            totalPushes++;
            totalCredits += 2;  // Charge 2: 1 for push, 1 credit for future pop
            
            if (debug) {
                cout << "Push " << value << " (charged 2, added 1 credit)" << endl;
                cout << "Stack size: " << stack.size() << ", Credits: " << totalCredits << endl;
            }
        }
        
        int pop() {
            if (stack.empty()) return -1;
            
            int value = stack.back();
            stack.pop_back();
            totalPops++;
            totalCredits -= 1;  // Use 1 credit from push operation
            
            if (debug) {
                cout << "Pop " << value << " (used 1 credit)" << endl;
                cout << "Stack size: " << stack.size() << ", Credits: " << totalCredits << endl;
            }
            
            return value;
        }
        
        void multiPop(int k) {
            if (debug) {
                cout << "MultiPop(" << k << ")" << endl;
            }
            
            int popped = 0;
            while (k > 0 && !stack.empty()) {
                pop();
                popped++;
                k--;
            }
            
            if (debug) {
                cout << "Popped " << popped << " elements" << endl;
            }
        }
        
        void printAnalysis() const {
            cout << "\n--- Stack MultiPop Analysis ---" << endl;
            cout << "Total pushes: " << totalPushes << endl;
            cout << "Total pops: " << totalPops << endl;
            cout << "Remaining credits: " << totalCredits << endl;
            cout << "Total cost (accounting method): " << totalPushes * 2 << endl;
            cout << "Amortized cost per push: 2" << endl;
            cout << "Amortized cost per pop/multipop: 0 (uses credits)" << endl;
        }
    };
    
    // Potential Method Example - Splay Tree (simplified)
    class PotentialMethodDemo {
    private:
        vector<int> arr;
        int totalOperations;
        bool debug;
        
    public:
        PotentialMethodDemo(bool debugMode = false) : totalOperations(0), debug(debugMode) {
            if (debug) {
                cout << "\n=== POTENTIAL METHOD DEMONSTRATION ===" << endl;
            }
        }
        
        void insert(int value) {
            arr.push_back(value);
            totalOperations++;
            
            // Simulate potential function: Φ(D) = number of inversions
            int potential = calculatePotential();
            
            if (debug) {
                cout << "Insert " << value << ", Potential: " << potential << endl;
            }
        }
        
        void sort() {
            if (debug) {
                cout << "Sorting array..." << endl;
                cout << "Before sort - Potential: " << calculatePotential() << endl;
            }
            
            // Bubble sort to demonstrate potential change
            int n = arr.size();
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (arr[j] > arr[j + 1]) {
                        swap(arr[j], arr[j + 1]);
                        totalOperations++;
                    }
                }
            }
            
            if (debug) {
                cout << "After sort - Potential: " << calculatePotential() << endl;
            }
        }
        
        void printAnalysis() const {
            cout << "\n--- Potential Method Analysis ---" << endl;
            cout << "Total operations: " << totalOperations << endl;
            cout << "Final potential: " << calculatePotential() << endl;
            cout << "Amortized cost = Actual cost + Potential change" << endl;
        }
        
    private:
        int calculatePotential() const {
            int inversions = 0;
            for (int i = 0; i < arr.size(); i++) {
                for (int j = i + 1; j < arr.size(); j++) {
                    if (arr[i] > arr[j]) {
                        inversions++;
                    }
                }
            }
            return inversions;
        }
    };
    
    // Comprehensive comparison of all methods
    void compareAmortizedMethods() {
        cout << "\n=== COMPARISON OF AMORTIZED ANALYSIS METHODS ===" << endl;
        
        cout << "\n1. Aggregate Method:" << endl;
        cout << "   - Analyzes total cost over sequence of operations" << endl;
        cout << "   - Example: Dynamic array resize operations" << endl;
        cout << "   - Total cost / Number of operations = Amortized cost" << endl;
        
        cout << "\n2. Accounting Method:" << endl;
        cout << "   - Assigns charges to operations" << endl;
        cout << "   - Some operations overpay (create credits)" << endl;
        cout << "   - Other operations use credits" << endl;
        cout << "   - Example: Stack with multipop" << endl;
        
        cout << "\n3. Potential Method:" << endl;
        cout << "   - Uses potential function Φ(D)" << endl;
        cout << "   - Amortized cost = Actual cost + ΔΦ" << endl;
        cout << "   - Example: Splay trees, Fibonacci heaps" << endl;
        
        cout << "================================================" << endl;
    }
    
    // Performance demonstration
    void demonstrateAmortizedPerformance() {
        cout << "\n=== AMORTIZED PERFORMANCE DEMONSTRATION ===" << endl;
        
        vector<int> sizes = {100, 1000, 10000, 100000};
        
        cout << "Size\t\tDynamic Array\tVector (STL)\tTime Ratio" << endl;
        cout << "----\t\t-------------\t------------\t----------" << endl;
        
        for (int n : sizes) {
            // Test custom dynamic array
            auto start = chrono::high_resolution_clock::now();
            DynamicArray dynArr;
            for (int i = 0; i < n; i++) {
                dynArr.push_back(i);
            }
            auto end = chrono::high_resolution_clock::now();
            auto dynTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
            
            // Test STL vector
            start = chrono::high_resolution_clock::now();
            vector<int> vec;
            for (int i = 0; i < n; i++) {
                vec.push_back(i);
            }
            end = chrono::high_resolution_clock::now();
            auto vecTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
            
            double ratio = (double)dynTime / vecTime;
            
            cout << n << "\t\t" << dynTime << "\t\t" << vecTime << "\t\t" 
                 << fixed << setprecision(2) << ratio << endl;
        }
        
        cout << "\nBoth show O(1) amortized insertion time!" << endl;
        cout << "=============================================" << endl;
    }
};

int main() {
    // Read basic input
    int n;
    cin >> n;
    
    AmortizedAnalysis analyzer;
    
    // Demonstrate Dynamic Array
    AmortizedAnalysis::DynamicArray dynArr;
    for (int i = 0; i < n; i++) {
        dynArr.push_back(i);
    }
    
    cout << "Dynamic Array - Final size: " << dynArr.getSize() << endl;
    cout << "Capacity: " << dynArr.getCapacity() << endl;
    cout << "Amortized cost: " << dynArr.getAmortizedCost() << endl;
    
    // Uncomment for detailed demonstrations:
    
    // Debug mode for dynamic array
    // AmortizedAnalysis::DynamicArray debugDynArr(true);
    // for (int i = 0; i < 10; i++) {
    //     debugDynArr.push_back(i);
    // }
    // debugDynArr.printAnalysis();
    
    // Binary counter demonstration
    // AmortizedAnalysis::BinaryCounter counter(8, true);
    // for (int i = 0; i < 16; i++) {
    //     counter.increment();
    // }
    // counter.printAnalysis();
    
    // Stack with multipop
    // AmortizedAnalysis::StackWithMultiPop stack(true);
    // for (int i = 0; i < 10; i++) {
    //     stack.push(i);
    // }
    // stack.multiPop(5);
    // stack.printAnalysis();
    
    // Compare amortized methods
    // analyzer.compareAmortizedMethods();
    
    // Performance demonstration
    // analyzer.demonstrateAmortizedPerformance();
    
    return 0;
}