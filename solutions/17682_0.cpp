#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

const int MAXN = 3030;

ll h, w, dp[MAXN][MAXN];

int main()
{
    cin >> h >> w;
    for(int i = 0; i <= h; i++) dp[i][0] = 1;
    for(int i = 0; i <= w; i++) dp[0][i] = 1;
    for(int n = 1; n <= h; n++) {
        for(int m = 1; m <= w; m++) {
            dp[n][m] += dp[n-1][m];
            dp[n][m] %= MOD;
            dp[n][m] += 4 * m * dp[n-1][m-1] % MOD;
            if(m >= 2) dp[n][m] += m * (m-1) / 2 * dp[n-1][m-2] % MOD;
            dp[n][m] %= MOD;
            if(n >= 2) dp[n][m] += m * (n-1) * dp[n-2][m-1] % MOD;
            dp[n][m] %= MOD;
        }
    }
    cout << (dp[h][w]-1+MOD) % MOD << "\n";
}