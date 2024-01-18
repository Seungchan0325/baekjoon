#include <iostream>
#include <vector>

using namespace std;

using ull = unsigned long long;

int N, M;
vector<int> sizes;

bool operate(ull limit) {
    int cnt = 0, tmp = 0;
    for(auto& i : sizes) {
        if(i > limit)
            return false;
        if(tmp + i > limit) {
            tmp = i;
            cnt++;
        } else {
            tmp += i;
        }
    }
    if(tmp != 0) cnt++;
    return cnt <= M;
}

void solve() {
    ull start = 1, end = 1e9, mid, ans;

    while(start <= end) {
        mid = (start + end) / 2;
        if(operate(mid)) {
            end = mid - 1;
            ans = mid;
        } else {
            start = mid + 1;
        }
    }
    cout << ans << endl;
}

int main() {
    cin >> N >> M;
    sizes.resize(N);
    for(auto& i : sizes)
        cin >> i;
    solve();
}