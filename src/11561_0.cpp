#include <iostream>
#include <vector>
#include <limits>

using namespace std;

using ull = unsigned long long;

ull operate(ull n, ull k) {
    ull a = k * (k + 1) / 2;
    if(a <= n)
        return true;
    else
        return false;
}

void solve() {
    ull n;
    cin >> n;

    ull start = 1, end = 1e9, mid, answer = 0;
    while(start <= end) {
        mid = (start + end) / 2;
        if(operate(n, mid) == false) {
            end = mid - 1;
        } else {
            answer = mid;
            start = mid + 1;
        }
    }
    cout << answer << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
        solve();
}