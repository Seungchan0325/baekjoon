#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

int n;
int dp[1010][20202], a[1010];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    dp[0][10000] = 1;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= 20000; j++) {
            dp[i][j] += dp[i-1][j-a[i]] + dp[i-1][j+a[i]];
            dp[i][j] %= MOD;
        }
        ans += dp[i][10000];
        ans %= MOD;
        dp[i][10000] += 1;
        dp[i][10000] %= MOD;
    }
    cout << ans;
}