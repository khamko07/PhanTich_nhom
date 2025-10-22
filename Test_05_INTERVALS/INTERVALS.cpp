#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start, end;
};

bool compare(Interval a, Interval b) {
    return a.end < b.end;
}

int minPoints(vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end(), compare);
    
    int count = 1;
    int lastPoint = intervals[0].end;
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i].start > lastPoint) {
            count++;
            lastPoint = intervals[i].end;
        }
    }
    
    return count;
}

int main() {
    int n;
    cin >> n;
    vector<Interval> intervals(n);
    
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].start >> intervals[i].end;
    }
    
    cout << minPoints(intervals) << endl;
    return 0;
}