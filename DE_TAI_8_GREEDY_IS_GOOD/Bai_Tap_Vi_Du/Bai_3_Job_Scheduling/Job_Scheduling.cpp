#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Job Scheduling để tối thiểu hóa tổng thời gian chờ
struct Job {
    int duration, id;
    
    Job(int d, int i) : duration(d), id(i) {}
};

bool compareByDuration(const Job& a, const Job& b) {
    if (a.duration == b.duration) {
        return a.id < b.id; // Tie-breaking
    }
    return a.duration < b.duration; // Sắp xếp theo thời gian tăng dần
}

int minimizeWaitingTime(vector<Job>& jobs) {
    // Greedy choice: Sắp xếp theo thời gian thực hiện tăng dần
    sort(jobs.begin(), jobs.end(), compareByDuration);
    
    int totalWaitingTime = 0;
    int currentTime = 0;
    
    for (const Job& job : jobs) {
        totalWaitingTime += currentTime; // Thời gian chờ của job này
        currentTime += job.duration;     // Cập nhật thời gian hiện tại
    }
    
    return totalWaitingTime;
}

// Hàm debug để hiển thị quá trình scheduling
void debugJobScheduling(vector<Job>& jobs) {
    cout << "=== DEBUG JOB SCHEDULING ===" << endl;
    cout << "Original jobs:" << endl;
    for (const Job& job : jobs) {
        cout << "Job " << job.id << ": duration=" << job.duration << endl;
    }
    
    sort(jobs.begin(), jobs.end(), compareByDuration);
    
    cout << "\nAfter sorting by duration (ascending):" << endl;
    for (const Job& job : jobs) {
        cout << "Job " << job.id << ": duration=" << job.duration << endl;
    }
    
    cout << "\nScheduling process:" << endl;
    int totalWaitingTime = 0;
    int currentTime = 0;
    
    for (int i = 0; i < jobs.size(); i++) {
        const Job& job = jobs[i];
        cout << "Schedule job " << job.id << " at time " << currentTime << endl;
        cout << "  Waiting time: " << currentTime << endl;
        cout << "  Execution time: " << job.duration << endl;
        
        totalWaitingTime += currentTime;
        currentTime += job.duration;
        
        cout << "  Finish time: " << currentTime << endl;
        cout << "  Total waiting time so far: " << totalWaitingTime << endl << endl;
    }
    
    cout << "Final total waiting time: " << totalWaitingTime << endl;
    cout << "Average waiting time: " << (double)totalWaitingTime / jobs.size() << endl;
    cout << "============================" << endl;
}

// Phương pháp brute force để so sánh
int jobSchedulingBruteForce(vector<Job>& jobs) {
    int n = jobs.size();
    vector<int> indices(n);
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    int minWaitingTime = INT_MAX;
    
    do {
        int totalWaitingTime = 0;
        int currentTime = 0;
        
        for (int i = 0; i < n; i++) {
            totalWaitingTime += currentTime;
            currentTime += jobs[indices[i]].duration;
        }
        
        minWaitingTime = min(minWaitingTime, totalWaitingTime);
    } while (next_permutation(indices.begin(), indices.end()));
    
    return minWaitingTime;
}

// Chứng minh tính đúng đắn bằng exchange argument
void proveCorrectness() {
    cout << "=== PROOF OF CORRECTNESS ===" << endl;
    cout << "Theorem: Shortest Processing Time First (SPT) minimizes total waiting time." << endl;
    cout << "Proof by exchange argument:" << endl;
    cout << "1. Suppose optimal solution O doesn't follow SPT rule." << endl;
    cout << "2. Then there exist adjacent jobs i, j where duration[i] > duration[j]." << endl;
    cout << "3. Swapping i and j reduces total waiting time by (duration[i] - duration[j])." << endl;
    cout << "4. This contradicts optimality of O." << endl;
    cout << "5. Therefore, SPT rule is optimal. QED." << endl;
    cout << "============================" << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<Job> jobs;
    for (int i = 0; i < n; i++) {
        int duration;
        cin >> duration;
        jobs.push_back(Job(duration, i));
    }
    
    int minWaitingTime = minimizeWaitingTime(jobs);
    cout << minWaitingTime << endl;
    
    // Uncomment để xem debug info:
    // debugJobScheduling(jobs);
    
    // Uncomment để xem chứng minh:
    // proveCorrectness();
    
    // Uncomment để so sánh với brute force (chỉ với n <= 8):
    // if (n <= 8) {
    //     int bruteResult = jobSchedulingBruteForce(jobs);
    //     cout << "Brute force result: " << bruteResult << endl;
    //     cout << "Results match: " << (minWaitingTime == bruteResult ? "YES" : "NO") << endl;
    // }
    
    return 0;
}