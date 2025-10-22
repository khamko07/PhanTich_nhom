#include <iostream>
#include <string>
using namespace std;

void generate_binary(int n, string current = "") {
    if (current.length() == n) {
        cout << current << endl;
        return;
    }
    
    generate_binary(n, current + "0");
    generate_binary(n, current + "1");
}

int main() {
    int n;
    cin >> n;
    generate_binary(n);
    return 0;
}