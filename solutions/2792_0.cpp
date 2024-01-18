#include <iostream>
#include <vector>

using namespace std;

using ull = unsigned long long;

int N, M;
vector<int> jewel;

bool operate(int n) {
    int count = 0;
    for(auto& i : jewel) {
        count += i / n;
        if(i % n != 0) count++;
    }
    return count <= N;
}

void solve() {
    ull start = 1, end = 1e9, mid, ans;
    while(start <= end) {
        mid = (start + end) / 2;
        if(operate(mid)) {
            ans = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    cout << ans << endl;
}

int main() {
    cin >> N >> M;
    jewel.resize(M);
    for(auto& i : jewel)
        cin >> i;
    solve();
}