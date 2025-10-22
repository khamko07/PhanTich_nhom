#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int deadline, profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

int maxProfit(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compare);
    
    int maxDeadline = 0;
    for (auto& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }
    
    vector<bool> slot(maxDeadline + 1, false);
    int totalProfit = 0;
    
    for (auto& job : jobs) {
        for (int i = job.deadline; i >= 1; i--) {
            if (!slot[i]) {
                slot[i] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }
    
    return totalProfit;
}

int main() {
    int n;
    cin >> n;
    vector<Job> jobs(n);
    
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].deadline >> jobs[i].profit;
    }
    
    cout << maxProfit(jobs) << endl;
    return 0;
}