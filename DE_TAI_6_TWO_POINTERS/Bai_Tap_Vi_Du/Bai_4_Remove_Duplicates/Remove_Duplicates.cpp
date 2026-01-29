#include <iostream>
#include <vector>
using namespace std;

// Remove Duplicates from Sorted Array sử dụng Two Pointers
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 0; // Pointer cho vị trí ghi
    
    for (int fast = 1; fast < nums.size(); fast++) {
        // Nếu phần tử khác với phần tử trước đó
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    
    return slow + 1; // Độ dài mảng mới
}

// Hàm debug để hiển thị quá trình
void debugRemoveDuplicates(vector<int> nums) {
    cout << "=== DEBUG REMOVE DUPLICATES ===" << endl;
    cout << "Original array: ";
    for (int x : nums) cout << x << " ";
    cout << endl << endl;
    
    if (nums.empty()) {
        cout << "Empty array!" << endl;
        return;
    }
    
    int slow = 0;
    
    cout << "Step 0: slow=0, nums[0]=" << nums[0] << " (first element)" << endl;
    
    for (int fast = 1; fast < nums.size(); fast++) {
        cout << "Step " << fast << ": fast=" << fast << ", nums[fast]=" << nums[fast];
        
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
            cout << " (different, move to slow=" << slow << ")" << endl;
        } else {
            cout << " (duplicate, skip)" << endl;
        }
        
        cout << "  Current array: ";
        for (int i = 0; i < nums.size(); i++) {
            if (i <= slow) {
                cout << nums[i] << " ";
            } else {
                cout << "_ ";
            }
        }
        cout << endl << endl;
    }
    
    cout << "Final length: " << (slow + 1) << endl;
    cout << "Result array: ";
    for (int i = 0; i <= slow; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "==============================" << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    vector<int> original = nums; // Lưu bản gốc để debug
    int newLength = removeDuplicates(nums);
    
    // In mảng kết quả
    for (int i = 0; i < newLength; i++) {
        cout << nums[i];
        if (i < newLength - 1) cout << " ";
    }
    cout << endl;
    
    cout << newLength << endl;
    
    // Uncomment để xem debug info:
    // debugRemoveDuplicates(original);
    
    return 0;
}