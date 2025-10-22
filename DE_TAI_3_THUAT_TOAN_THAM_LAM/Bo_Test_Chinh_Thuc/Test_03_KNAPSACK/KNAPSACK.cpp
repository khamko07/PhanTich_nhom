#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }
    
    sort(items.begin(), items.end(), compare);
    
    double totalValue = 0;
    
    for (auto& item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * ((double)capacity / item.weight);
            break;
        }
    }
    
    return totalValue;
}

int main() {
    int n, capacity;
    cin >> n >> capacity;
    vector<Item> items(n);
    
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
    }
    
    cout << (int)fractionalKnapsack(items, capacity) << endl;
    return 0;
}