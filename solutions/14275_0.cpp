#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int MAXM = 8;
const int MOD = 1e9 + 7;

int N, M, cache[MAXN][MAXM][1<<(2*MAXM)];

int dp(int i, int j, int bit)
{
    if(i == N && j == M) {
        if((bit>>M) == 0) return 1;
        else return 0;
    }
    if(j == M) return dp(i+1, 0, bit);

    int& ret = cache[i][j][bit];
    if(ret != -1) return ret;

    ret = 0;
    if(bit&(1<<M)) {
        int cnt = 0;
        if(bit&1) cnt++;
        if(j > 0 && bit&(1<<(M-1))) cnt++;
        if(j < M-1 && bit&(1<<(M+1))) cnt++;
        
        if(cnt&1) ret += dp(i, j+1, (bit|(1<<(2*M)))>>1);
        else ret += dp(i, j+1, bit>>1);
    } else {
        ret += dp(i, j+1, bit>>1);
        ret += dp(i, j+1, (bit|(1<<(2*M)))>>1);
    }

    ret %= MOD;

    return ret;
}

int main()
{
    cin >> N >> M;
    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 0);
    cout << result;
}