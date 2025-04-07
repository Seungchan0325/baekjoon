#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1011;
const int MAXM = 111;
const int MOD = 998244353;

int N, M, cache[MAXN][MAXM][3];

int dp(int idx, int prv, int slope)
{
    if(idx == N) return 1;
    int& ret = cache[idx][prv][slope];
    if(ret != -1) return ret;
    ret = 0;
    for(int i = 1; i <= M; i++) {
        if(slope == 0 && prv > i) ret += dp(idx+1, i, 0);
        if(slope == 0 && prv == i) ret += dp(idx+1, i, 1);
        if(slope == 0 && prv < i) ret += dp(idx+1, i, 2);

        if(slope == 1 && prv > i) ret += dp(idx+1, i, 0);
        if(slope == 1 && prv == i) ret += dp(idx+1, i, 1);
        if(slope == 1 && prv < i) ret += dp(idx+1, i, 2);

        if(slope == 2 && prv == i) ret += dp(idx+1, i, 1);
        if(slope == 2 && prv < i) ret += dp(idx+1, i, 2);
        ret %= MOD;
    }
     return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));
    cin >> N >> M;
    int ans = 0;
    for(int i = 1; i <= M; i++)
        ans = (ans + dp(1, i, 1)) % MOD;
    cout << ans;
}