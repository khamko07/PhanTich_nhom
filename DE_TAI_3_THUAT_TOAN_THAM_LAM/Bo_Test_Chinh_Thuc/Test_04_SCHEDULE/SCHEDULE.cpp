#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minWaitingTime(vector<int>& jobs) {
    sort(jobs.begin(), jobs.end());
    
    int totalWait = 0;
    int currentTime = 0;
    
    for (int i = 0; i < jobs.size(); i++) {
        totalWait += currentTime;
        currentTime += jobs[i];
    }
    
    return totalWait;
}

int main() {
    int n;
    cin >> n;
    vector<int> jobs(n);
    
    for (int i = 0; i < n; i++) {
        cin >> jobs[i];
    }
    
    cout << minWaitingTime(jobs) << endl;
    return 0;
}