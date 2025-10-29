#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Fractional Knapsack Problem - Có thể chia nhỏ vật phẩm
struct Item {
    int value, weight;
    double ratio;
    int id;
    
    Item(int v, int w, int i) : value(v), weight(w), id(i) {
        ratio = (double)value / weight;
    }
};

bool compareByRatio(const Item& a, const Item& b) {
    if (a.ratio == b.ratio) {
        return a.id < b.id; // Tie-breaking
    }
    return a.ratio > b.ratio; // Sắp xếp theo tỷ lệ giảm dần
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    // Sắp xếp theo tỷ lệ value/weight giảm dần
    sort(items.begin(), items.end(), compareByRatio);
    
    double totalValue = 0.0;
    int currentWeight = 0;
    
    for (const Item& item : items) {
        if (currentWeight + item.weight <= capacity) {
            // Lấy toàn bộ vật phẩm
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            // Lấy một phần vật phẩm
            int remainingCapacity = capacity - currentWeight;
            double fraction = (double)remainingCapacity / item.weight;
            totalValue += item.value * fraction;
            break; // Túi đã đầy
        }
    }
    
    return totalValue;
}

// Hàm debug để hiển thị quá trình greedy
void debugFractionalKnapsack(vector<Item>& items, int capacity) {
    cout << "=== DEBUG FRACTIONAL KNAPSACK ===" << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Original items:" << endl;
    for (const Item& item : items) {
        cout << "Item " << item.id << ": value=" << item.value 
             << ", weight=" << item.weight << ", ratio=" << item.ratio << endl;
    }
    
    sort(items.begin(), items.end(), compareByRatio);
    
    cout << "\nAfter sorting by ratio (descending):" << endl;
    for (const Item& item : items) {
        cout << "Item " << item.id << ": value=" << item.value 
             << ", weight=" << item.weight << ", ratio=" << item.ratio << endl;
    }
    
    cout << "\nGreedy selection process:" << endl;
    double totalValue = 0.0;
    int currentWeight = 0;
    
    for (const Item& item : items) {
        cout << "Consider item " << item.id << " (value=" << item.value 
             << ", weight=" << item.weight << ", ratio=" << item.ratio << ")" << endl;
        cout << "  Current weight: " << currentWeight << "/" << capacity << endl;
        
        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            totalValue += item.value;
            cout << "  Take FULL item -> weight=" << currentWeight 
                 << ", value=" << totalValue << endl;
        } else {
            int remainingCapacity = capacity - currentWeight;
            if (remainingCapacity > 0) {
                double fraction = (double)remainingCapacity / item.weight;
                double addedValue = item.value * fraction;
                totalValue += addedValue;
                currentWeight = capacity;
                cout << "  Take FRACTION " << fraction << " of item -> weight=" 
                     << currentWeight << ", value=" << totalValue << endl;
                break;
            } else {
                cout << "  SKIP (no remaining capacity)" << endl;
            }
        }
    }
    
    cout << "\nFinal result: " << totalValue << endl;
    cout << "=================================" << endl;
}

// So sánh với 0/1 Knapsack (DP) để thấy sự khác biệt
int knapsack01DP(vector<Item>& items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (items[i-1].weight <= w) {
                dp[i][w] = max(dp[i-1][w], 
                              dp[i-1][w - items[i-1].weight] + items[i-1].value);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

int main() {
    int n, capacity;
    cin >> n >> capacity;
    
    vector<Item> items;
    for (int i = 0; i < n; i++) {
        int value, weight;
        cin >> value >> weight;
        items.push_back(Item(value, weight, i));
    }
    
    double maxValue = fractionalKnapsack(items, capacity);
    cout << (int)maxValue << endl;
    
    // Uncomment để xem debug info:
    // debugFractionalKnapsack(items, capacity);
    
    // Uncomment để so sánh với 0/1 Knapsack:
    // int dp01Result = knapsack01DP(items, capacity);
    // cout << "0/1 Knapsack result: " << dp01Result << endl;
    // cout << "Fractional advantage: " << (maxValue - dp01Result) << endl;
    
    return 0;
}