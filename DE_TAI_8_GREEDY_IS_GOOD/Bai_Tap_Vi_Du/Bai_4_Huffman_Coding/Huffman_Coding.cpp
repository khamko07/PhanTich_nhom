#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;

// Huffman Coding - Tạo mã nhị phân tối ưu
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(int f) : ch(0), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq == b->freq) {
            // Tie-breaking: ưu tiên node có ký tự nhỏ hơn
            if (a->ch != 0 && b->ch != 0) {
                return a->ch > b->ch;
            }
            return a->ch == 0; // Internal node có priority thấp hơn
        }
        return a->freq > b->freq; // Min heap
    }
};

Node* buildHuffmanTree(vector<pair<char, int>>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Tạo leaf nodes
    for (auto& p : frequencies) {
        pq.push(new Node(p.first, p.second));
    }
    
    // Xây dựng cây Huffman
    while (pq.size() > 1) {
        Node* right = pq.top(); pq.pop();
        Node* left = pq.top(); pq.pop();
        
        // Greedy choice: Kết hợp hai node có tần suất thấp nhất
        Node* merged = new Node(left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        
        pq.push(merged);
    }
    
    return pq.top();
}

void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    
    if (root->ch != 0) { // Leaf node
        codes[root->ch] = code.empty() ? "0" : code; // Trường hợp chỉ có 1 ký tự
        return;
    }
    
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

double calculateAverageLength(const map<char, string>& codes, 
                             const vector<pair<char, int>>& frequencies) {
    int totalFreq = 0;
    double totalBits = 0;
    
    for (auto& p : frequencies) {
        totalFreq += p.second;
        totalBits += p.second * codes.at(p.first).length();
    }
    
    return totalBits / totalFreq;
}

// Hàm debug để hiển thị quá trình xây dựng cây Huffman
void debugHuffmanTree(vector<pair<char, int>>& frequencies) {
    cout << "=== DEBUG HUFFMAN CODING ===" << endl;
    cout << "Character frequencies:" << endl;
    for (auto& p : frequencies) {
        cout << "'" << p.first << "': " << p.second << endl;
    }
    
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    cout << "\nBuilding Huffman tree:" << endl;
    for (auto& p : frequencies) {
        pq.push(new Node(p.first, p.second));
        cout << "Add leaf node '" << p.first << "' with frequency " << p.second << endl;
    }
    
    int step = 1;
    while (pq.size() > 1) {
        Node* right = pq.top(); pq.pop();
        Node* left = pq.top(); pq.pop();
        
        cout << "Step " << step++ << ": Merge nodes with frequencies " 
             << left->freq << " and " << right->freq;
        
        Node* merged = new Node(left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        
        cout << " -> new internal node with frequency " << merged->freq << endl;
        
        pq.push(merged);
    }
    
    Node* root = pq.top();
    map<char, string> codes;
    generateCodes(root, "", codes);
    
    cout << "\nGenerated Huffman codes:" << endl;
    for (auto& p : codes) {
        cout << "'" << p.first << "': " << p.second << endl;
    }
    
    double avgLength = calculateAverageLength(codes, frequencies);
    cout << "\nAverage code length: " << fixed << setprecision(2) << avgLength << endl;
    cout << "============================" << endl;
}

// So sánh với Fixed-length encoding
void compareWithFixedLength(const vector<pair<char, int>>& frequencies,
                           const map<char, string>& huffmanCodes) {
    int n = frequencies.size();
    int fixedLength = 1;
    while ((1 << fixedLength) < n) {
        fixedLength++;
    }
    
    int totalFreq = 0;
    int huffmanBits = 0;
    
    for (auto& p : frequencies) {
        totalFreq += p.second;
        huffmanBits += p.second * huffmanCodes.at(p.first).length();
    }
    
    int fixedBits = totalFreq * fixedLength;
    
    cout << "=== COMPRESSION COMPARISON ===" << endl;
    cout << "Fixed-length encoding: " << fixedLength << " bits per character" << endl;
    cout << "Total bits (fixed): " << fixedBits << endl;
    cout << "Total bits (Huffman): " << huffmanBits << endl;
    cout << "Compression ratio: " << (double)huffmanBits / fixedBits << endl;
    cout << "Space saved: " << (fixedBits - huffmanBits) << " bits (" 
         << (100.0 * (fixedBits - huffmanBits) / fixedBits) << "%)" << endl;
    cout << "==============================" << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<pair<char, int>> frequencies;
    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        cin >> ch >> freq;
        frequencies.push_back({ch, freq});
    }
    
    Node* root = buildHuffmanTree(frequencies);
    map<char, string> codes;
    generateCodes(root, "", codes);
    
    // In mã Huffman
    for (auto& p : codes) {
        cout << p.first << ": " << p.second << endl;
    }
    
    // In độ dài trung bình
    double avgLength = calculateAverageLength(codes, frequencies);
    cout << fixed << setprecision(2) << avgLength << endl;
    
    // Uncomment để xem debug info:
    // debugHuffmanTree(frequencies);
    
    // Uncomment để so sánh với fixed-length:
    // compareWithFixedLength(frequencies, codes);
    
    return 0;
}