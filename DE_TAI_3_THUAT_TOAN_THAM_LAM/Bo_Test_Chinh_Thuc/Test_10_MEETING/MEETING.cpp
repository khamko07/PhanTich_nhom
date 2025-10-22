#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int minMeetingRooms(vector<pair<int, int>>& meetings) {
    sort(meetings.begin(), meetings.end());
    
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for (auto& meeting : meetings) {
        if (!pq.empty() && pq.top() <= meeting.first) {
            pq.pop();
        }
        pq.push(meeting.second);
    }
    
    return pq.size();
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> meetings(n);
    
    for (int i = 0; i < n; i++) {
        cin >> meetings[i].first >> meetings[i].second;
    }
    
    cout << minMeetingRooms(meetings) << endl;
    return 0;
}