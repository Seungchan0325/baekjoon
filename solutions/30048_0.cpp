#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 1e9 + 7;

ll dp[505][505], sum[505][505];

int main()
{
    int N, E;
    cin >> N >> E;

    dp[1][0] = 1;
    for(int n = 2; n <= N; n++) {
        for(int e = n-1; e >= 0; e--) sum[n-1][e] = (dp[n-1][e] + sum[n-1][e+1]) % mod;
        for(int e = 0; e <= n; e++) {
            dp[n][e] = dp[n-1][e-1];
            for(int i = 1, j = n-2; i>0 && j>0; i++, j--) {
                dp[n][e] = (dp[n][e] + dp[i][e]*dp[j][e]) % mod;
                dp[n][e] = (dp[n][e] + dp[i][e]*sum[j][e+1]) % mod;
                dp[n][e] = (dp[n][e] + dp[j][e]*sum[i][e+1]) % mod;
            }
        }
    }
    cout << dp[N][E] << "\n";
}