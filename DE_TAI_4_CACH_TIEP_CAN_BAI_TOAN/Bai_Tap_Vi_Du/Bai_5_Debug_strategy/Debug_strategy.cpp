#include <iostream>
#include <vector>
using namespace std;

// Code đã sửa lỗi: tính tổng các số chẵn
int sumEven(vector<int>& arr) {
    int sum = 0;
    // Sửa lỗi 1: bắt đầu từ i = 0 thay vì i = 1
    // Sửa lỗi 2: điều kiện i < arr.size() thay vì i <= arr.size()
    for (int i = 0; i < arr.size(); i++) {
        // Sửa lỗi 3: sử dụng == thay vì = để so sánh
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

// Hàm debug: in ra các bước thực hiện
int sumEvenWithDebug(vector<int>& arr) {
    int sum = 0;
    cout << "Debug: Bắt đầu tính tổng số chẵn" << endl;
    
    for (int i = 0; i < arr.size(); i++) {
        cout << "Debug: Kiểm tra arr[" << i << "] = " << arr[i];
        
        if (arr[i] % 2 == 0) {
            sum += arr[i];
            cout << " (chẵn, cộng vào sum)" << endl;
        } else {
            cout << " (lẻ, bỏ qua)" << endl;
        }
        
        cout << "Debug: sum hiện tại = " << sum << endl;
    }
    
    cout << "Debug: Kết thúc, tổng = " << sum << endl;
    return sum;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Sử dụng hàm đã sửa lỗi
    int result = sumEven(arr);
    cout << result << endl;
    
    // Uncomment dòng dưới để xem debug info
    // sumEvenWithDebug(arr);
    
    return 0;
}