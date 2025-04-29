#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

int N, a[MAXN];
vector<int> car[MAXN];
map<int, ll> dp[MAXN];

int main()
{
    cin >> N;
    vector<int> v;
    for(int i = 0; i < N; i++) cin >> a[i], v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 0; i < N; i++) {
        int idx = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        car[idx].push_back(i);
        car[idx].push_back(i+N);
        dp[idx][i] = 1e18;
        dp[idx][i+N] = 1e18;
    }
    dp[0][0] = dp[0][N] = 0;

    for(int i = 1; i <= v.size(); i++) {
        sort(car[i].begin(), car[i].end());
        int l = 0;
        int r = ssize(car[i]) / 2 - 1;
        for(; r < car[i].size(); l++,r++) {
            ll mn = 1e18;
            auto it = dp[i-1].lower_bound(car[i][l]);
            if(it != dp[i-1].end()) mn = min(mn, abs(it->first - car[i][l]) + it->second);
            if(it != dp[i-1].begin()) --it, mn = min(mn, abs(it->first - car[i][l]) + it->second);
            dp[i][car[i][r]] = min(dp[i][car[i][r]], car[i][r] - car[i][l] + mn);

            mn = 1e18;
            it = dp[i-1].lower_bound(car[i][r]);
            if(it != dp[i-1].end()) mn = min(mn, abs(it->first - car[i][r]) + it->second);
            if(it != dp[i-1].begin()) --it, mn = min(mn, abs(it->first - car[i][r]) + it->second);
            dp[i][car[i][l]] = min(dp[i][car[i][l]], car[i][r] - car[i][l] + mn);
        }

        for(auto [k, item] : dp[i]) {
            if(dp[i].contains(k+N)) dp[i][k+N] = min(dp[i][k+N], item);
            if(dp[i].contains(k-N)) dp[i][k-N] = min(dp[i][k-N], item);
        }

        for(auto it = dp[i].begin(); it != dp[i].end(); ++it) {
            if(it != dp[i].begin()) {
                auto j = it; --j;
                j->second = min(j->second, it->second + it->first - j->first);
            }
            auto j = it; ++j;
            if(j != dp[i].end()) {
                j->second = min(j->second, it->second + j->first - it->first);
            }
        }

        for(auto it = dp[i].rbegin(); it != dp[i].rend(); ++it) {
            if(it != dp[i].rbegin()) {
                auto j = it; --j;
                j->second = min(j->second, it->second - it->first + j->first);
            }
            auto j = it; ++j;
            if(j != dp[i].rend()) {
                j->second = min(j->second, it->second - j->first + it->first);
            }
        }

        for(auto [k, item] : dp[i]) {
            if(dp[i].contains(k+N)) dp[i][k+N] = min(dp[i][k+N], item);
            if(dp[i].contains(k-N)) dp[i][k-N] = min(dp[i][k-N], item);
        }

        // for(auto [k, item] : dp[i]) {
        //     cout << format("dp[{}][{}] = {}\n", i, k, item);
        // }
    }

    ll mn = 1e18;
    for(auto [k, i] : dp[v.size()]) mn = min(mn, i);
    cout << mn;
}