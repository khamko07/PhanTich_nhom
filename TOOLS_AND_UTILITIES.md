# 🛠️ Công Cụ và Tiện Ích Hỗ Trợ

## 🚀 Scripts Tự Động Hóa

### 📝 Script Biên Dịch và Chạy Test

```bash
#!/bin/bash
# File: run_tests.sh

# Màu sắc cho output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}🔧 Algorithm Testing Utility${NC}"
echo "=================================="

# Kiểm tra tham số
if [ $# -eq 0 ]; then
    echo "Usage: ./run_tests.sh <cpp_file> [test_directory]"
    echo "Example: ./run_tests.sh solution.cpp Test01"
    exit 1
fi

CPP_FILE=$1
TEST_DIR=${2:-"Test01"}
EXECUTABLE="program"

# Biên dịch
echo -e "${YELLOW}📦 Compiling $CPP_FILE...${NC}"
g++ -std=c++17 -O2 -Wall -Wextra -o $EXECUTABLE $CPP_FILE

if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Compilation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Compilation successful!${NC}"

# Chạy test
if [ -d "$TEST_DIR" ]; then
    echo -e "${YELLOW}🧪 Running tests in $TEST_DIR...${NC}"
    
    for input_file in $TEST_DIR/*.inp $TEST_DIR/input.txt; do
        if [ -f "$input_file" ]; then
            echo -e "${YELLOW}Testing with $(basename $input_file)...${NC}"
            
            # Chạy chương trình
            timeout 5s ./$EXECUTABLE < "$input_file" > output.tmp
            
            if [ $? -eq 124 ]; then
                echo -e "${RED}❌ Time Limit Exceeded${NC}"
                continue
            fi
            
            # Tìm file output tương ứng
            output_file="${input_file%.*}.out"
            if [ ! -f "$output_file" ]; then
                output_file="$TEST_DIR/output.txt"
            fi
            
            if [ -f "$output_file" ]; then
                # So sánh kết quả
                if diff -q output.tmp "$output_file" > /dev/null; then
                    echo -e "${GREEN}✅ PASSED${NC}"
                else
                    echo -e "${RED}❌ FAILED${NC}"
                    echo "Expected:"
                    cat "$output_file"
                    echo "Got:"
                    cat output.tmp
                    echo "---"
                fi
            else
                echo -e "${YELLOW}⚠️  No expected output file found${NC}"
                echo "Program output:"
                cat output.tmp
            fi
        fi
    done
    
    # Cleanup
    rm -f output.tmp $EXECUTABLE
else
    echo -e "${RED}❌ Test directory $TEST_DIR not found!${NC}"
    exit 1
fi

echo -e "${GREEN}🎉 Testing completed!${NC}"
```

### 🎯 Script Tạo Template Bài Tập Mới

```bash
#!/bin/bash
# File: create_problem.sh

echo "🎯 Algorithm Problem Template Generator"
echo "======================================"

read -p "Enter topic number (1-10): " TOPIC_NUM
read -p "Enter problem number (1-5): " PROBLEM_NUM
read -p "Enter problem name: " PROBLEM_NAME

# Tạo tên thư mục
TOPIC_DIR="DE_TAI_${TOPIC_NUM}_*"
PROBLEM_DIR="Bai_${PROBLEM_NUM}_${PROBLEM_NAME// /_}"

# Tìm thư mục đề tài
TOPIC_PATH=$(find . -maxdepth 1 -type d -name "$TOPIC_DIR" | head -1)

if [ -z "$TOPIC_PATH" ]; then
    echo "❌ Topic directory not found!"
    exit 1
fi

FULL_PATH="$TOPIC_PATH/Bai_Tap_Vi_Du/$PROBLEM_DIR"

# Tạo cấu trúc thư mục
mkdir -p "$FULL_PATH/Test01"

# Tạo file C++ template
cat > "$FULL_PATH/${PROBLEM_NAME// /_}.cpp" << 'EOF'
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Main algorithm implementation
    void solve() {
        // TODO: Implement your algorithm here
    }
    
    // Debug function
    void debug() {
        cout << "=== DEBUG MODE ===" << endl;
        // TODO: Add debug information
        cout << "==================" << endl;
    }
    
    // Performance analysis
    void analyzePerformance() {
        cout << "=== PERFORMANCE ANALYSIS ===" << endl;
        // TODO: Add performance metrics
        cout << "============================" << endl;
    }
};

int main() {
    Solution solution;
    
    // Read input
    // TODO: Add input reading logic
    
    // Solve problem
    solution.solve();
    
    // Uncomment for debugging
    // solution.debug();
    
    // Uncomment for performance analysis
    // solution.analyzePerformance();
    
    return 0;
}
EOF

# Tạo file input mẫu
cat > "$FULL_PATH/Test01/input.txt" << EOF
# TODO: Add sample input
EOF

# Tạo file output mẫu
cat > "$FULL_PATH/Test01/output.txt" << EOF
# TODO: Add expected output
EOF

echo "✅ Created problem template at: $FULL_PATH"
echo "📝 Files created:"
echo "   - ${PROBLEM_NAME// /_}.cpp"
echo "   - Test01/input.txt"
echo "   - Test01/output.txt"
```

## 🔍 Công Cụ Phân Tích Code

### 📊 Performance Profiler

```cpp
// File: performance_profiler.hpp
#ifndef PERFORMANCE_PROFILER_HPP
#define PERFORMANCE_PROFILER_HPP

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class PerformanceProfiler {
private:
    std::map<std::string, std::chrono::high_resolution_clock::time_point> startTimes;
    std::map<std::string, std::vector<double>> measurements;
    
public:
    void startTimer(const std::string& name) {
        startTimes[name] = std::chrono::high_resolution_clock::now();
    }
    
    void endTimer(const std::string& name) {
        auto end = std::chrono::high_resolution_clock::now();
        if (startTimes.find(name) != startTimes.end()) {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                end - startTimes[name]);
            measurements[name].push_back(duration.count() / 1000.0); // milliseconds
        }
    }
    
    void printReport() {
        std::cout << "\n=== PERFORMANCE REPORT ===" << std::endl;
        for (const auto& [name, times] : measurements) {
            if (!times.empty()) {
                double total = 0;
                double min_time = times[0];
                double max_time = times[0];
                
                for (double time : times) {
                    total += time;
                    min_time = std::min(min_time, time);
                    max_time = std::max(max_time, time);
                }
                
                double avg = total / times.size();
                
                std::cout << name << ":" << std::endl;
                std::cout << "  Runs: " << times.size() << std::endl;
                std::cout << "  Average: " << avg << " ms" << std::endl;
                std::cout << "  Min: " << min_time << " ms" << std::endl;
                std::cout << "  Max: " << max_time << " ms" << std::endl;
                std::cout << "  Total: " << total << " ms" << std::endl;
                std::cout << std::endl;
            }
        }
        std::cout << "==========================" << std::endl;
    }
    
    void reset() {
        startTimes.clear();
        measurements.clear();
    }
};

// Global profiler instance
extern PerformanceProfiler globalProfiler;

// Convenience macros
#define PROFILE_START(name) globalProfiler.startTimer(name)
#define PROFILE_END(name) globalProfiler.endTimer(name)
#define PROFILE_REPORT() globalProfiler.printReport()

#endif // PERFORMANCE_PROFILER_HPP
```

### 🧪 Test Case Generator

```cpp
// File: test_generator.hpp
#ifndef TEST_GENERATOR_HPP
#define TEST_GENERATOR_HPP

#include <random>
#include <vector>
#include <fstream>
#include <iostream>

class TestGenerator {
private:
    std::mt19937 rng;
    
public:
    TestGenerator(unsigned seed = std::random_device{}()) : rng(seed) {}
    
    // Generate random integers
    std::vector<int> generateRandomInts(int count, int min_val, int max_val) {
        std::uniform_int_distribution<int> dist(min_val, max_val);
        std::vector<int> result;
        
        for (int i = 0; i < count; i++) {
            result.push_back(dist(rng));
        }
        
        return result;
    }
    
    // Generate random graph
    void generateRandomGraph(int nodes, int edges, const std::string& filename) {
        std::ofstream file(filename);
        file << nodes << " " << edges << std::endl;
        
        std::uniform_int_distribution<int> dist(0, nodes - 1);
        std::set<std::pair<int, int>> edgeSet;
        
        while (edgeSet.size() < edges) {
            int u = dist(rng);
            int v = dist(rng);
            if (u != v) {
                edgeSet.insert({std::min(u, v), std::max(u, v)});
            }
        }
        
        for (const auto& edge : edgeSet) {
            file << edge.first << " " << edge.second << std::endl;
        }
        
        file.close();
    }
    
    // Generate sorted array (for testing binary search, etc.)
    std::vector<int> generateSortedArray(int size, int min_val, int max_val) {
        auto arr = generateRandomInts(size, min_val, max_val);
        std::sort(arr.begin(), arr.end());
        return arr;
    }
    
    // Generate test cases for specific algorithms
    void generateBinarySearchTest(const std::string& filename) {
        std::ofstream file(filename);
        
        auto arr = generateSortedArray(1000, 1, 10000);
        std::uniform_int_distribution<int> dist(0, arr.size() - 1);
        int target = arr[dist(rng)]; // Ensure target exists
        
        file << arr.size() << " " << target << std::endl;
        for (int x : arr) {
            file << x << " ";
        }
        file << std::endl;
        
        file.close();
    }
    
    void generateSortingTest(const std::string& filename, int size) {
        std::ofstream file(filename);
        
        auto arr = generateRandomInts(size, 1, 100000);
        
        file << arr.size() << std::endl;
        for (int x : arr) {
            file << x << " ";
        }
        file << std::endl;
        
        file.close();
    }
};

#endif // TEST_GENERATOR_HPP
```

## 📈 Visualization Tools

### 🎨 Algorithm Visualizer (ASCII Art)

```cpp
// File: visualizer.hpp
#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class AlgorithmVisualizer {
public:
    // Visualize array
    static void printArray(const std::vector<int>& arr, const std::string& title = "") {
        if (!title.empty()) {
            std::cout << title << std::endl;
        }
        
        std::cout << "Index: ";
        for (int i = 0; i < arr.size(); i++) {
            std::cout << std::setw(4) << i;
        }
        std::cout << std::endl;
        
        std::cout << "Value: ";
        for (int x : arr) {
            std::cout << std::setw(4) << x;
        }
        std::cout << std::endl;
        
        std::cout << "       ";
        for (int i = 0; i < arr.size(); i++) {
            std::cout << "----";
        }
        std::cout << std::endl;
    }
    
    // Visualize sorting step
    static void printSortingStep(const std::vector<int>& arr, int left, int right, 
                                int pivot = -1, const std::string& operation = "") {
        std::cout << operation << std::endl;
        
        for (int i = 0; i < arr.size(); i++) {
            if (i == pivot) {
                std::cout << "[" << std::setw(2) << arr[i] << "]";
            } else if (i >= left && i <= right) {
                std::cout << " " << std::setw(2) << arr[i] << " ";
            } else {
                std::cout << "(" << std::setw(2) << arr[i] << ")";
            }
        }
        std::cout << std::endl;
    }
    
    // Visualize binary search
    static void printBinarySearchStep(const std::vector<int>& arr, int left, int right, 
                                     int mid, int target) {
        std::cout << "Target: " << target << ", Range: [" << left << ", " << right 
                  << "], Mid: " << mid << " (value: " << arr[mid] << ")" << std::endl;
        
        for (int i = 0; i < arr.size(); i++) {
            if (i == mid) {
                std::cout << "[" << std::setw(2) << arr[i] << "]";
            } else if (i >= left && i <= right) {
                std::cout << " " << std::setw(2) << arr[i] << " ";
            } else {
                std::cout << "(" << std::setw(2) << arr[i] << ")";
            }
        }
        std::cout << std::endl;
    }
    
    // Visualize graph (adjacency list)
    static void printGraph(const std::vector<std::vector<int>>& graph) {
        std::cout << "Graph Adjacency List:" << std::endl;
        for (int i = 0; i < graph.size(); i++) {
            std::cout << "Node " << i << ": ";
            for (int neighbor : graph[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // Visualize DFS traversal
    static void printDFSStep(int current, const std::vector<bool>& visited, 
                            const std::vector<int>& path) {
        std::cout << "Visiting node " << current << std::endl;
        std::cout << "Visited: ";
        for (int i = 0; i < visited.size(); i++) {
            std::cout << (visited[i] ? "T" : "F") << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Path: ";
        for (int node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
        std::cout << "---" << std::endl;
    }
    
    // Visualize tree structure
    static void printTree(const std::vector<std::vector<int>>& tree, int root, 
                         int depth = 0, const std::string& prefix = "") {
        std::cout << prefix << "├── " << root << std::endl;
        
        for (int i = 0; i < tree[root].size(); i++) {
            int child = tree[root][i];
            std::string newPrefix = prefix + (i == tree[root].size() - 1 ? "    " : "│   ");
            printTree(tree, child, depth + 1, newPrefix);
        }
    }
};

#endif // VISUALIZER_HPP
```

## 🎯 IDE Integration

### 📝 VS Code Tasks Configuration

```json
// File: .vscode/tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compile C++",
            "type": "shell",
            "command": "g++",
            "args": [
                "-std=c++17",
                "-O2",
                "-Wall",
                "-Wextra",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": "$gcc"
        },
        {
            "label": "Run with Test Input",
            "type": "shell",
            "command": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "options": {
                "cwd": "${fileDirname}"
            },
            "group": "test",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "dependsOn": "Compile C++",
            "runOptions": {
                "runOn": "folderOpen"
            }
        },
        {
            "label": "Run All Tests",
            "type": "shell",
            "command": "bash",
            "args": ["${workspaceFolder}/run_tests.sh", "${file}"],
            "group": "test",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            }
        }
    ]
}
```

### ⚙️ VS Code Launch Configuration

```json
// File: .vscode/launch.json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug C++",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "Compile C++",
            "miDebuggerPath": "/usr/bin/gdb"
        }
    ]
}
```

## 📚 Documentation Generator

### 📖 Auto-generate Algorithm Documentation

```python
#!/usr/bin/env python3
# File: generate_docs.py

import os
import re
from pathlib import Path

def extract_algorithm_info(cpp_file):
    """Extract algorithm information from C++ file comments"""
    with open(cpp_file, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Extract class name
    class_match = re.search(r'class\s+(\w+)', content)
    class_name = class_match.group(1) if class_match else "Unknown"
    
    # Extract time complexity from comments
    time_complexity = re.search(r'Time Complexity:\s*O\(([^)]+)\)', content)
    time_complexity = time_complexity.group(1) if time_complexity else "Not specified"
    
    # Extract space complexity from comments
    space_complexity = re.search(r'Space Complexity:\s*O\(([^)]+)\)', content)
    space_complexity = space_complexity.group(1) if space_complexity else "Not specified"
    
    # Extract description from comments
    description_match = re.search(r'/\*\*(.*?)\*/', content, re.DOTALL)
    description = description_match.group(1).strip() if description_match else "No description"
    
    return {
        'class_name': class_name,
        'time_complexity': time_complexity,
        'space_complexity': space_complexity,
        'description': description
    }

def generate_topic_summary(topic_dir):
    """Generate summary for a topic"""
    topic_name = os.path.basename(topic_dir)
    examples_dir = os.path.join(topic_dir, 'Bai_Tap_Vi_Du')
    
    summary = f"# {topic_name} - Algorithm Summary\n\n"
    
    if os.path.exists(examples_dir):
        for example_dir in sorted(os.listdir(examples_dir)):
            example_path = os.path.join(examples_dir, example_dir)
            if os.path.isdir(example_path):
                # Find C++ file
                cpp_files = [f for f in os.listdir(example_path) if f.endswith('.cpp')]
                if cpp_files:
                    cpp_file = os.path.join(example_path, cpp_files[0])
                    info = extract_algorithm_info(cpp_file)
                    
                    summary += f"## {example_dir}\n\n"
                    summary += f"**Class**: {info['class_name']}\n\n"
                    summary += f"**Time Complexity**: O({info['time_complexity']})\n\n"
                    summary += f"**Space Complexity**: O({info['space_complexity']})\n\n"
                    summary += f"**Description**: {info['description']}\n\n"
                    summary += "---\n\n"
    
    return summary

def main():
    """Generate documentation for all topics"""
    project_root = Path('.')
    
    for topic_dir in sorted(project_root.glob('DE_TAI_*')):
        if topic_dir.is_dir():
            summary = generate_topic_summary(str(topic_dir))
            
            output_file = topic_dir / 'ALGORITHM_SUMMARY.md'
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(summary)
            
            print(f"Generated summary for {topic_dir.name}")

if __name__ == "__main__":
    main()
```

## 🎮 Interactive Learning Tools

### 🕹️ Algorithm Quiz Generator

```cpp
// File: algorithm_quiz.cpp
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>

class AlgorithmQuiz {
private:
    struct Question {
        std::string question;
        std::vector<std::string> options;
        int correctAnswer;
        std::string explanation;
    };
    
    std::vector<Question> questions;
    std::mt19937 rng;
    
public:
    AlgorithmQuiz() : rng(std::random_device{}()) {
        initializeQuestions();
    }
    
    void initializeQuestions() {
        questions = {
            {
                "What is the time complexity of binary search?",
                {"O(n)", "O(log n)", "O(n log n)", "O(1)"},
                1,
                "Binary search divides the search space in half each iteration."
            },
            {
                "Which algorithm is best for finding shortest paths in unweighted graphs?",
                {"DFS", "BFS", "Dijkstra", "Floyd-Warshall"},
                1,
                "BFS finds shortest paths in unweighted graphs in O(V+E) time."
            },
            {
                "What is the key property of a greedy algorithm?",
                {"Optimal substructure", "Overlapping subproblems", "Local optimal choice", "Memoization"},
                2,
                "Greedy algorithms make locally optimal choices at each step."
            }
            // Add more questions...
        };
    }
    
    void runQuiz(int numQuestions = 5) {
        std::shuffle(questions.begin(), questions.end(), rng);
        
        int score = 0;
        std::cout << "🎯 Algorithm Knowledge Quiz\n";
        std::cout << "===========================\n\n";
        
        for (int i = 0; i < std::min(numQuestions, (int)questions.size()); i++) {
            const auto& q = questions[i];
            
            std::cout << "Question " << (i + 1) << ": " << q.question << "\n\n";
            
            for (int j = 0; j < q.options.size(); j++) {
                std::cout << (char)('A' + j) << ") " << q.options[j] << "\n";
            }
            
            std::cout << "\nYour answer: ";
            char answer;
            std::cin >> answer;
            
            int answerIndex = toupper(answer) - 'A';
            
            if (answerIndex == q.correctAnswer) {
                std::cout << "✅ Correct!\n";
                score++;
            } else {
                std::cout << "❌ Incorrect. The correct answer is " 
                         << (char)('A' + q.correctAnswer) << ".\n";
            }
            
            std::cout << "💡 " << q.explanation << "\n\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
        
        std::cout << "🏆 Final Score: " << score << "/" << numQuestions << "\n";
        
        if (score == numQuestions) {
            std::cout << "🎉 Perfect! You're an algorithm master!\n";
        } else if (score >= numQuestions * 0.8) {
            std::cout << "👍 Great job! You have solid algorithm knowledge.\n";
        } else if (score >= numQuestions * 0.6) {
            std::cout << "📚 Good effort! Keep studying to improve.\n";
        } else {
            std::cout << "💪 Keep learning! Practice makes perfect.\n";
        }
    }
};

int main() {
    AlgorithmQuiz quiz;
    quiz.runQuiz();
    return 0;
}
```

---

**🎯 Mục đích**: Những công cụ này giúp việc học tập và phát triển thuật toán trở nên hiệu quả và thú vị hơn.

**🚀 Sử dụng**: Copy các script và tools vào thư mục dự án, sau đó customize theo nhu cầu cụ thể.

**📈 Lợi ích**: Tự động hóa testing, visualization, và tạo ra trải nghiệm học tập tương tác.