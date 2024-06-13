#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll SQMX = 500;
const ll MAX = 100005;

ll DP[2][MAX], psum[MAX], ans[MAX];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    vector<pair<ll, ll>> v(tc);
    for(auto& [a, b] : v) cin >> a >> b;

    DP[0][0] = 1;
    for(int k = 1; k < SQMX; k++) {
        for(int i = 0; i < MAX; i++) {
            if(i-k >= 0) DP[k%2][i] = (DP[(k-1)%2][i] + DP[(k-1)%2][i-k]) % MOD;
            else DP[k%2][i] = DP[(k-1)%2][i];

            psum[i] = DP[k%2][i];
            if(i > 0) psum[i] = (psum[i] + psum[i-1]) % MOD;
        }

        for(int i = 0; i < tc; i++) {
            auto [a, b] = v[i];

            int lo = k*(k+1)/2 - b;
            int hi = a;

            if(hi < lo) continue;

            assert(lo < MAX);
            assert(0 <= hi && hi < MAX);

            if(lo <= 0) ans[i] = (ans[i] + psum[hi]) % MOD;
            else ans[i] = (ans[i] + (psum[hi] - psum[lo-1] + MOD)) % MOD;
        }
    }

    for(int i = 0; i < tc; i++) {
        assert(ans[i] >= 0);
        cout << ans[i] << "\n";
    }
}