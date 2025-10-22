# Đề Tài 3: Thuật Toán Tham Lam

## 1. Trình Bày Lý Thuyết

### 1.1 Khái Niệm Thuật Toán Tham Lam

**Thuật toán Tham lam (Greedy Algorithm)** là một phương pháp giải quyết bài toán tối ưu bằng cách tại mỗi bước chọn lựa chọn tốt nhất tại thời điểm hiện tại, với hy vọng rằng chuỗi các lựa chọn tối ưu cục bộ sẽ dẫn đến lời giải tối ưu toàn cục.

### 1.2 Đặc Điểm Của Thuật Toán Tham Lam

**Ưu điểm:**
- Đơn giản, dễ hiểu và dễ cài đặt
- Thời gian thực thi nhanh
- Tiết kiệm bộ nhớ

**Nhược điểm:**
- Không phải lúc nào cũng cho kết quả tối ưu
- Khó chứng minh tính đúng đắn
- Cần phân tích kỹ từng bài toán cụ thể

### 1.3 Hai Tính Chất Quan Trọng

**1. Tính lựa chọn tối ưu (Greedy Choice Property):**
Từ những kết quả tối ưu cục bộ có thể đi đến kết quả tối ưu toàn cục mà không cần xem xét lại các kết quả.

**2. Tính tối ưu từ bài toán nhỏ (Optimal Substructure):**
Kết quả tối ưu được xác định bằng các kết quả tối ưu từ bài toán nhỏ hơn.

### 1.4 Bài Toán Lựa Chọn Hoạt Động (Activity Selection)

Đây là bài toán cơ sở minh họa cho thuật toán tham lam:

**Bài toán:** Cho n hoạt động, mỗi hoạt động có thời gian bắt đầu si và kết thúc fi. Chọn số lượng hoạt động tối đa sao cho không có hai hoạt động nào bị trùng thời gian.

**Thuật toán:**
1. Sắp xếp các hoạt động theo thời gian kết thúc tăng dần
2. Chọn hoạt động đầu tiên
3. Với mỗi hoạt động tiếp theo, nếu thời gian bắt đầu >= thời gian kết thúc của hoạt động vừa chọn thì chọn nó

### 1.5 Các Ứng Dụng Phổ Biến

- Bài toán đổi tiền (Coin Change)
- Bài toán cái túi phân số (Fractional Knapsack)
- Thuật toán Dijkstra (đường đi ngắn nhất)
- Thuật toán Kruskal và Prim (cây khung nhỏ nhất)
- Bài toán lập lịch (Scheduling)

## 2. Bài Tập Thực Hành

### Bài 1: Đổi Tiền Tối Ưu
**Đề bài**: Đổi số tiền S bằng ít tờ tiền nhất với các mệnh giá cho trước

**Lời giải**:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minCoins(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend()); // Sắp xếp giảm dần
    int count = 0;
    
    for (int coin : coins) {
        while (amount >= coin) {
            amount -= coin;
            count++;
        }
    }
    
    return (amount == 0) ? count : -1;
}

int main() {
    int n, amount;
    cin >> n >> amount;
    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    
    cout << minCoins(coins, amount) << endl;
    return 0;
}
```

**Giải thích**: Chọn mệnh giá lớn nhất có thể tại mỗi bước

### Bài 2: Lựa Chọn Hoạt Động
**Đề bài**: Chọn số lượng hoạt động tối đa không bị trùng thời gian

**Lời giải**:
```cpp
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
```

**Giải thích**: Chọn hoạt động kết thúc sớm nhất tại mỗi bước

### Bài 3: Cái Túi Phân Số
**Đề bài**: Chọn các vật phẩm để tối đa hóa giá trị trong cái túi có trọng lượng giới hạn

**Lời giải**:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    // Tính tỷ lệ giá trị/trọng lượng
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }
    
    sort(items.begin(), items.end(), compare);
    
    double totalValue = 0;
    
    for (auto& item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * ((double)capacity / item.weight);
            break;
        }
    }
    
    return totalValue;
}

int main() {
    int n, capacity;
    cin >> n >> capacity;
    vector<Item> items(n);
    
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
    }
    
    cout << (int)fractionalKnapsack(items, capacity) << endl;
    return 0;
}
```

**Giải thích**: Chọn vật có tỷ lệ giá trị/trọng lượng cao nhất

### Bài 4: Lập Lịch Công Việc
**Đề bài**: Sắp xếp công việc để tối thiểu hóa thời gian chờ trung bình

**Lời giải**:
```cpp
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
```

**Giải thích**: Sắp xếp công việc theo thời gian thực hiện tăng dần

### Bài 5: Tìm Số Lượng Khoảng Tối Thiểu
**Đề bài**: Tìm số lượng điểm tối thiểu để phủ tất cả các khoảng

**Lời giải**:
```cpp
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
```

**Giải thích**: Chọn điểm ở cuối khoảng kết thúc sớm nhất## 
3. Bộ Test

### Bài 1: Đổi Tiền Tối Ưu
- **Test 01**: Input: 4 mệnh giá [50,20,10,5], số tiền 67, Output: 3

### Bài 2: Lựa Chọn Hoạt Động  
- **Test 01**: Input: 3 hoạt động [(1,3),(2,4),(3,5)], Output: 2

### Bài 3: Cái Túi Phân Số
- **Test 01**: Input: 3 vật [(10,5),(20,10),(30,15)], túi 15kg, Output: 50

### Bài 4: Lập Lịch Công Việc
- **Test 01**: Input: 3 công việc [3,1,2], Output: 3

### Bài 5: Tìm Số Lượng Khoảng Tối Thiểu
- **Test 01**: Input: 3 khoảng [(1,3),(2,4),(3,5)], Output: 2

## 4. 10 Bộ Test Bổ Sung

### Test 01: COINCHANGE - Đổi tiền tối ưu
### Test 02: ACTIVITY - Lựa chọn hoạt động
### Test 03: KNAPSACK - Cái túi phân số
### Test 04: SCHEDULE - Lập lịch công việc
### Test 05: INTERVALS - Phủ khoảng
### Test 06: MAXPROFIT - Tối đa hóa lợi nhuận
### Test 07: MINCOINS - Số xu tối thiểu
### Test 08: GASSTATION - Trạm xăng
### Test 09: PLATFORM - Sân ga tàu
### Test 10: MEETING - Phòng họp

## 5. Cấu Trúc Thư Mục

```
De_tai_3_Thuat_toan_Tham_lam/
├── De_tai_3_Thuat_toan_Tham_lam.md
├── 10_Bo_Test_Thuat_toan_Tham_lam.md
├── Test_01_COINCHANGE/
│   ├── COINCHANGE.cpp
│   └── Test01/
│       ├── COINCHANGE.inp
│       └── COINCHANGE.out
├── Test_02_ACTIVITY/
│   ├── ACTIVITY.cpp
│   └── Test01/
│       ├── ACTIVITY.inp
│       └── ACTIVITY.out
├── ... (tương tự cho 8 test còn lại)
└── Test_10_MEETING/
    ├── MEETING.cpp
    └── Test01/
        ├── MEETING.inp
        └── MEETING.out
```

## 6. Lưu Ý Quan Trọng

### Khi Nào Sử Dụng Thuật Toán Tham Lam?

1. **Bài toán có tính chất tối ưu cục bộ**: Lựa chọn tốt nhất tại mỗi bước dẫn đến kết quả tối ưu toàn cục
2. **Bài toán có cấu trúc con tối ưu**: Lời giải tối ưu chứa các lời giải con tối ưu
3. **Dữ liệu lớn**: Khi cần thuật toán nhanh với độ phức tạp thấp

### Cách Chứng Minh Tính Đúng Đắn

1. **Chứng minh tính lựa chọn tối ưu**: Luôn tồn tại lời giải tối ưu chứa lựa chọn tham lam
2. **Chứng minh cấu trúc con tối ưu**: Sau khi thực hiện lựa chọn tham lam, bài toán con còn lại vẫn có cấu trúc tối ưu

### Các Lỗi Thường Gặp

- Không chứng minh tính đúng đắn của thuật toán
- Sắp xếp sai tiêu chí tham lam
- Không xử lý các trường hợp biên
- Nhầm lẫn giữa tối ưu cục bộ và toàn cục

## 7. Hướng Dẫn Sử Dụng

### Biên Dịch và Chạy
```bash
# Biên dịch
g++ -o program_name source_file.cpp

# Chạy với input file
./program_name < input_file.inp

# Hoặc chạy trực tiếp
./program_name
```

### Kiểm Tra Kết Quả
So sánh output của chương trình với file `.out` tương ứng để kiểm tra tính đúng đắn.

---

**Tác giả**: [Tên nhóm]  
**Ngày hoàn thành**: [Ngày tháng năm]  
**Tham khảo**: VNOI Wiki - https://wiki.vnoi.info/, Topcoder