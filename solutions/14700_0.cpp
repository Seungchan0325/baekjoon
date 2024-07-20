#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 305;

int N, M, cache[MAXN][1<<18];

int dp(int x, int bit)
{
    if(x == N*M) return 1;
    int& ret = cache[x][bit];
    if(ret != -1) return ret;

    ret = dp(x+1, bit>>1);
    if(x%M == 0) {
        ret += dp(x+1, (bit>>1)|(1<<M));
    } else {
        if((~bit&1) || (~bit&2) || (~bit&(1<<M))) {
            ret += dp(x+1, (bit>>1)|(1<<M));
        }
    }

    ret %= MOD;

    return ret;
}

int main()
{
    cin >> N >> M;
    if(N < M) swap(N, M);
    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0);
    cout << result;
}