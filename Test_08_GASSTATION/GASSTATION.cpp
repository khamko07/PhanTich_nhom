#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minStops(vector<int>& stations, int distance, int tank) {
    stations.push_back(0);
    stations.push_back(distance);
    sort(stations.begin(), stations.end());
    
    int stops = 0;
    int current = 0;
    int fuel = tank;
    
    for (int i = 1; i < stations.size(); i++) {
        int gap = stations[i] - stations[current];
        
        if (gap > tank) {
            return -1;
        }
        
        if (fuel >= gap) {
            fuel -= gap;
        } else {
            stops++;
            fuel = tank - gap;
            current = i - 1;
        }
    }
    
    return stops;
}

int main() {
    int n, distance, tank;
    cin >> n >> distance >> tank;
    vector<int> stations(n);
    
    for (int i = 0; i < n; i++) {
        cin >> stations[i];
    }
    
    cout << minStops(stations, distance, tank) << endl;
    return 0;
}