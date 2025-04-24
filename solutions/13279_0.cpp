#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

const int MOD = 100003;

using ll = long long;

int dp[2][30303];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> a(N);
    for(auto& i : a) cin >> i;
    
    dp[0][0] = 1;
    for(int x = 1; x <= N; x++) {
        dp[x%2][0] = 1;
        for(int k = 1; k <= x; k++) {
            dp[x&1][k] = ((ll)a[x-1] * dp[~x&1][k-1] + dp[~x&1][k]) % MOD;
        }
    }

    int Q; cin >> Q;
    for(int i = 0; i < Q; i++) {
        int k;
        cin >> k;
        cout << dp[N&1][k] << "\n";
    }
}