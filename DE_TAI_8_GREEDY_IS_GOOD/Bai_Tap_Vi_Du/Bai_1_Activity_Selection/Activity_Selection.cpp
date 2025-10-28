#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Activity Selection Problem - Bài toán kinh điển của Greedy
struct Activity {
    int start, finish, id;
    
    Activity(int s, int f, int i) : start(s), finish(f), id(i) {}
};

bool compareByFinish(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

vector<int> activitySelection(vector<Activity>& activities) {
    // Sắp xếp theo thời gian kết thúc tăng dần
    sort(activities.begin(), activities.end(), compareByFinish);
    
    vector<int> result;
    if (activities.empty()) return result;
    
    // Chọn hoạt động đầu tiên (kết thúc sớm nhất)
    result.push_back(activities[0].id);
    int lastFinish = activities[0].finish;
    
    // Greedy choice: chọn hoạt động tiếp theo không trùng với hoạt động đã chọn
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastFinish) {
            result.push_back(activities[i].id);
            lastFinish = activities[i].finish;
        }
    }
    
    return result;
}

// Hàm debug để hiển thị quá trình greedy
void debugActivitySelection(vector<Activity>& activities) {
    cout << "=== DEBUG ACTIVITY SELECTION ===" << endl;
    cout << "Original activities:" << endl;
    for (int i = 0; i < activities.size(); i++) {
        cout << "Activity " << activities[i].id << ": [" 
             << activities[i].start << ", " << activities[i].finish << "]" << endl;
    }
    
    sort(activities.begin(), activities.end(), compareByFinish);
    
    cout << "\nAfter sorting by finish time:" << endl;
    for (int i = 0; i < activities.size(); i++) {
        cout << "Activity " << activities[i].id << ": [" 
             << activities[i].start << ", " << activities[i].finish << "]" << endl;
    }
    
    cout << "\nGreedy selection process:" << endl;
    vector<int> result;
    if (!activities.empty()) {
        result.push_back(activities[0].id);
        int lastFinish = activities[0].finish;
        cout << "Select activity " << activities[0].id 
             << " (first activity, finish at " << lastFinish << ")" << endl;
        
        for (int i = 1; i < activities.size(); i++) {
            cout << "Consider activity " << activities[i].id 
                 << " [" << activities[i].start << ", " << activities[i].finish << "]: ";
            
            if (activities[i].start >= lastFinish) {
                result.push_back(activities[i].id);
                lastFinish = activities[i].finish;
                cout << "SELECTED (start " << activities[i].start 
                     << " >= last finish " << (lastFinish - activities[i].finish + activities[i].start) << ")" << endl;
            } else {
                cout << "REJECTED (start " << activities[i].start 
                     << " < last finish " << lastFinish << ")" << endl;
            }
        }
    }
    
    cout << "\nFinal selection: ";
    for (int id : result) cout << id << " ";
    cout << "\nTotal activities: " << result.size() << endl;
    cout << "===============================" << endl;
}

// Phương pháp brute force để so sánh (chỉ dùng cho n nhỏ)
int activitySelectionBruteForce(vector<Activity>& activities) {
    int n = activities.size();
    int maxCount = 0;
    
    // Thử tất cả các tập con
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<Activity> selected;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                selected.push_back(activities[i]);
            }
        }
        
        // Kiểm tra tính khả thi
        sort(selected.begin(), selected.end(), compareByFinish);
        bool feasible = true;
        for (int i = 1; i < selected.size(); i++) {
            if (selected[i].start < selected[i-1].finish) {
                feasible = false;
                break;
            }
        }
        
        if (feasible) {
            maxCount = max(maxCount, (int)selected.size());
        }
    }
    
    return maxCount;
}

int main() {
    int n;
    cin >> n;
    
    vector<Activity> activities;
    for (int i = 0; i < n; i++) {
        int start, finish;
        cin >> start >> finish;
        activities.push_back(Activity(start, finish, i));
    }
    
    vector<int> selected = activitySelection(activities);
    
    cout << selected.size() << endl;
    for (int i = 0; i < selected.size(); i++) {
        cout << selected[i];
        if (i < selected.size() - 1) cout << " ";
    }
    cout << endl;
    
    // Uncomment để xem debug info:
    // debugActivitySelection(activities);
    
    // Uncomment để so sánh với brute force (chỉ với n <= 15):
    // if (n <= 15) {
    //     int bruteResult = activitySelectionBruteForce(activities);
    //     cout << "Brute force result: " << bruteResult << endl;
    //     cout << "Results match: " << (selected.size() == bruteResult ? "YES" : "NO") << endl;
    // }
    
    return 0;
}