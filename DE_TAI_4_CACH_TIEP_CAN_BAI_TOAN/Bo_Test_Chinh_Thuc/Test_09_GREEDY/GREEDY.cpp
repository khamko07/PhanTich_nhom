#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Greedy Strategy: Áp dụng chiến lược tham lam
// Bài toán: Lập lịch công việc với deadline để tối đa hóa số công việc hoàn thành

struct Job {
    int id;
    int duration;    // Thời gian hoàn thành
    int deadline;    // Deadline
    
    Job(int i, int d, int dl) : id(i), duration(d), deadline(dl) {}
};

// Comparator cho greedy strategy
bool compareByDeadline(const Job& a, const Job& b) {
    return a.deadline < b.deadline;
}

bool compareByDuration(const Job& a, const Job& b) {
    return a.duration < b.duration;
}

bool compareByRatio(const Job& a, const Job& b) {
    // Ưu tiên công việc có tỷ lệ deadline/duration cao
    return (double)a.deadline / a.duration > (double)b.deadline / b.duration;
}

// Greedy Algorithm: Chọn công việc theo deadline sớm nhất
int scheduleJobsByDeadline(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compareByDeadline);
    
    int currentTime = 0;
    int completedJobs = 0;
    
    for (const Job& job : jobs) {
        // Kiểm tra xem có thể hoàn thành công việc này đúng hạn không
        if (currentTime + job.duration <= job.deadline) {
            currentTime += job.duration;
            completedJobs++;
        }
    }
    
    return completedJobs;
}

// Greedy Algorithm: Chọn công việc theo thời gian ngắn nhất
int scheduleJobsByDuration(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compareByDuration);
    
    int currentTime = 0;
    int completedJobs = 0;
    
    for (const Job& job : jobs) {
        if (currentTime + job.duration <= job.deadline) {
            currentTime += job.duration;
            completedJobs++;
        }
    }
    
    return completedJobs;
}

// Greedy Algorithm: Chọn theo tỷ lệ deadline/duration
int scheduleJobsByRatio(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compareByRatio);
    
    int currentTime = 0;
    int completedJobs = 0;
    
    for (const Job& job : jobs) {
        if (currentTime + job.duration <= job.deadline) {
            currentTime += job.duration;
            completedJobs++;
        }
    }
    
    return completedJobs;
}

// Hàm so sánh các chiến lược greedy
void compareGreedyStrategies(vector<Job> jobs) {
    cout << "=== GREEDY STRATEGIES COMPARISON ===" << endl;
    
    vector<Job> jobs1 = jobs, jobs2 = jobs, jobs3 = jobs;
    
    int result1 = scheduleJobsByDeadline(jobs1);
    cout << "By Deadline: " << result1 << " jobs" << endl;
    
    int result2 = scheduleJobsByDuration(jobs2);
    cout << "By Duration: " << result2 << " jobs" << endl;
    
    int result3 = scheduleJobsByRatio(jobs3);
    cout << "By Ratio: " << result3 << " jobs" << endl;
    
    cout << "Best strategy: ";
    if (result1 >= result2 && result1 >= result3) {
        cout << "Deadline-based" << endl;
    } else if (result2 >= result1 && result2 >= result3) {
        cout << "Duration-based" << endl;
    } else {
        cout << "Ratio-based" << endl;
    }
    
    cout << "===================================" << endl;
}

// Hàm in chi tiết lịch trình
void printSchedule(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compareByDeadline);
    
    int currentTime = 0;
    cout << "=== DETAILED SCHEDULE ===" << endl;
    cout << "Time\tJob\tDuration\tDeadline\tStatus" << endl;
    
    for (const Job& job : jobs) {
        if (currentTime + job.duration <= job.deadline) {
            cout << currentTime << "\t" << job.id << "\t" << job.duration 
                 << "\t\t" << job.deadline << "\t\tCompleted" << endl;
            currentTime += job.duration;
        } else {
            cout << "-\t" << job.id << "\t" << job.duration 
                 << "\t\t" << job.deadline << "\t\tSkipped" << endl;
        }
    }
    
    cout << "=========================" << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<Job> jobs;
    for (int i = 0; i < n; i++) {
        int duration, deadline;
        cin >> duration >> deadline;
        jobs.push_back(Job(i + 1, duration, deadline));
    }
    
    // Sử dụng chiến lược greedy tốt nhất (theo deadline)
    int result = scheduleJobsByDeadline(jobs);
    cout << result << endl;
    
    // Uncomment để xem so sánh các chiến lược:
    // compareGreedyStrategies(jobs);
    
    // Uncomment để xem lịch trình chi tiết:
    // printSchedule(jobs);
    
    return 0;
}