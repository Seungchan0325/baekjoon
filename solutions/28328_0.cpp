#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250005;

int n, dp[MAXN][2], dp2[MAXN][3];
vector<int> graph[MAXN];

ll nC2(ll n)
{
    return n * (n - 1) / 2;
}

void dfs(int u, int p)
{
    dp[u][0] = 0;
    dp[u][1] = 1;

    for(auto v : graph[u]) {
        if(v == p) continue;

        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

/* condition
 * 0. dp[u][0] or dp[u][1]
 * 1. dp[u][0]
 * 2. dp[u][1]
 */
ll cntImmovable(int u, int p, int condition)
{
    int& ret = dp2[u][condition];
    if(ret != -1) return ret;

    ret = 0;
    if(condition == 2) ret++;

    for(auto v : graph[u]) {
        if(v == p) continue;

        if(condition == 0) {
            ll min_v = cntImmovable(v, u, 1);
            if(dp[v][0] == dp[v][1]) {
                min_v = min(cntImmovable(v, u, 0), min_v);
            } else if(dp[v][0] > dp[v][1]) {
                min_v = min(cntImmovable(v, u, 1), min_v);
            } else if(dp[v][0] < dp[v][1]) {
                min_v = min(cntImmovable(v, u, 2), min_v);
            }
            ret += min_v;
        } else if(condition == 1) {
            if(dp[v][0] < dp[v][1]) {
                ret += cntImmovable(v, u, 2);
            } else if(dp[v][0] == dp[v][1]) {
                ret += cntImmovable(v, u, 0);
            } else if(dp[v][0] > dp[v][1]) {
                ret += cntImmovable(v, u, 1);
            } else {
                assert(0);
            }
        } else if(condition == 2) {
            ret += cntImmovable(v, u, 1);
        } else {
            assert(0);
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1);
    ll cnt;
    memset(dp2, -1, sizeof(dp2));
    if(dp[1][0] == dp[1][1])
        cnt = cntImmovable(1, -1, 0);
    else if(dp[1][0] > dp[1][1])
        cnt = cntImmovable(1, -1, 1);
    else if(dp[1][0] < dp[1][1])
        cnt = cntImmovable(1, -1, 2);
    else
        assert(0);

    ll result = nC2(n) - nC2(cnt);
    cout << result;
}