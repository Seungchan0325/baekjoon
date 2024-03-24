#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll MAXN = 1e5 + 100;

ll N, K;
int D;
int dp[MAXN];

int main()
{
    cin >> N >> K >> D;
    
    N -= K * (K + 1) / 2;
    if(N < 0) {
        cout << 0;
        return 0;
    }

    dp[0] = 1;
    for(int k = 1; k <= K; k++) {
        vector<vector<int>> sum(k, vector<int>(1));
        for(int n = 0; n <= N; n++) {
            int mod = n % k;
            int h = n / k;
            int ph = n - k * min(n/k, D-1);

            // sum[mod][h + 1] += (sum[mod][h + 1] + dp[n] + sum[mod][h]) % MOD;
            sum[mod].push_back((sum[mod].back() + dp[n]) % MOD);
            dp[n] = (sum[mod][h + 1] - sum[mod][ph / k] + MOD) % MOD;
        }
        // for(int h = 0; h <= min(n/k, D-1); h++) {
        //     dp[n] = (dp[n - k * h] + dp[n]) % MOD;
        // }
    }

    cout << dp[N];
}