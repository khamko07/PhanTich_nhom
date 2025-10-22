#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minPlatforms(vector<pair<int, int>>& trains) {
    vector<pair<int, int>> events;
    
    for (auto& train : trains) {
        events.push_back({train.first, 1});    // arrival
        events.push_back({train.second, -1});  // departure
    }
    
    sort(events.begin(), events.end());
    
    int platforms = 0;
    int maxPlatforms = 0;
    
    for (auto& event : events) {
        platforms += event.second;
        maxPlatforms = max(maxPlatforms, platforms);
    }
    
    return maxPlatforms;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> trains(n);
    
    for (int i = 0; i < n; i++) {
        cin >> trains[i].first >> trains[i].second;
    }
    
    cout << minPlatforms(trains) << endl;
    return 0;
}