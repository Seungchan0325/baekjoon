#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010;
const int mod = 1'000'000'000;

ll n, dp[MAXN];

int main()
{
    cin >> n;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            dp[i] = (dp[i] + dp[j] * dp[i-j-1]) % mod;
        }
    }
    cout << dp[n-2] << "\n";
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    dp[2] = 1;
    dp[4] = 1;
    for(int i = 6; i <= n; i+=2) {
        for(int j = 2; j < i; j+=2) {
            for(int k = j+1; k < i; k+=2) {
                dp[i] = (dp[i] + (dp[j] * dp[k-j+1] % mod) * dp[i-k+1] % mod) % mod;
            }
        }
    }
    cout << dp[n] << "\n";
}