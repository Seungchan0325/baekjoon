#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXV = 101;

ll V, P, L, village[MAXV], sum[MAXV], dp[MAXV][MAXV][MAXV], par[MAXV][MAXV][MAXV];

ll dist(ll x, ll y)
{
    return min(abs(x-y), L-abs(x-y));
}

ll compute(int i, int j)
{
    int k = upper_bound(village+1, village+V+1, (village[i]+village[j])/2) - village;
    return (sum[k-1] - sum[i-1]) - (k-i) * village[i] + (j-k) * village[j] - (sum[j-1] - sum[k-1]);
}

int main()
{
    cin >> V >> P >> L;
    for(int i = 1; i <= V; i++) cin >> village[i];
    for(int i = 1; i <= V; i++) sum[i] += sum[i-1] + village[i];

    memset(dp, 0x3f, sizeof(dp));
    ll mn = 1e18;
    for(int s = 1; s <= V; s++) {
        dp[s][s][1] = 0;
        for(int i = s; i <= V; i++) {
            for(int j = s; j < i; j++) {
                for(int k = 2; k <= P; k++) {
                    if(dp[s][i][k] > dp[s][j][k-1] + compute(j, i)) {
                        dp[s][i][k] = dp[s][j][k-1] + compute(j, i);
                        par[s][i][k] = j;
                    }
                }
            }
        }
        for(int i = s; i <= V; i++) {
            for(int j = i; j <= V; j++) {
                dp[s][i][P] += min(dist(village[s], village[j]), dist(village[j], village[i]));
            }
            for(int j = 1; j <= s; j++) {
                dp[s][i][P] += min(dist(village[s], village[j]), dist(village[j], village[i]));
            }
            mn = min(mn, dp[s][i][P]);
        }
    }

    cout << mn << "\n";
    for(int s = 1; s <= V; s++) {
        for(int i = s; i <= V; i++) {
            if(mn != dp[s][i][P]) continue;

            vector<int> ans;
            for(int j = 0; j < P; j++) {
                ans.push_back(i);
                i = par[s][i][P-j];
            }
            reverse(ans.begin(), ans.end());
            for(auto i : ans) cout << village[i] << " ";
            return 0;
        }
    }
}