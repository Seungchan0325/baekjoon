#include <bits/stdc++.h>

using namespace std;

int MOD = 1000000000;

int n;
int cache[10][105];

int dp(int start, int length) {
    if(length == 0) return 1;
    int& ret = cache[start][length];
    if(ret != -1) return ret;

    ret = 0;
    if(0 < start) ret += dp(start - 1, length - 1);
    if(start < 9) ret += dp(start + 1, length - 1);
    ret %= MOD;

    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));
    cin >> n;
    int ans = 0;
    for(int start = 1; start <= 9; start++) {
        ans += dp(start, n - 1);
        ans %= MOD;
    }
    cout << ans;
}