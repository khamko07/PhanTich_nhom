#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, end;
};

bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

int maxActivities(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), compare);
    
    int count = 1;
    int lastEnd = activities[0].end;
    
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastEnd) {
            count++;
            lastEnd = activities[i].end;
        }
    }
    
    return count;
}

int main() {
    int n;
    cin >> n;
    vector<Activity> activities(n);
    
    for (int i = 0; i < n; i++) {
        cin >> activities[i].start >> activities[i].end;
    }
    
    cout << maxActivities(activities) << endl;
    return 0;
}