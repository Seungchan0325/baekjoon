#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

bool inStack[MAXN], chk[MAXN];
int N, num[MAXN], low[MAXN], scc[MAXN], sz[MAXN], dp[MAXN], pv, t;
stack<int> s;
vector<int> g[MAXN];

int compute(int x)
{
    int ans = 0;
    while(x) {
        ans += x % 10; x /= 10;
    }
    return ans;
}

void dfs(int u)
{
    num[u] = low[u] = ++pv;
    inStack[u] = true;
    s.push(u);

    for(auto v : g[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[v], low[u]);
        } else if(inStack[v]) {
            low[u] = min(low[v], low[u]);
        }
    }

    if(num[u] == low[u]) {
        t++;
        while(s.top() != u) {
            scc[s.top()] = t;
            inStack[s.top()] = false;
            sz[t]++;
            s.pop();
        }
        scc[u] = t;
        inStack[u] = false;
        sz[t]++;
        s.pop();
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        g[i].push_back((i+compute(i)-1)%N+1);
        g[0].push_back(i);
        // g[(i+compute(i)-1)%N+1].push_back(i);
    }
    dfs(0);
    // for(int i = 1; i <= N; i++) {
        // if(!num[i]) dfs(i);
    // }
    vector<pair<int, int>> v;
    for(int i = 1; i <= N; i++) {
        v.emplace_back(-scc[i], i);
    }
    int ans = 0;
    sort(v.begin(), v.end());
    for(auto [_, u] : v) {
        if(!chk[scc[u]]) dp[scc[u]] += sz[scc[u]], chk[scc[u]] = true;
        int nxt = (u+compute(u)-1)%N+1;
        dp[scc[nxt]] = max(dp[scc[nxt]], dp[scc[u]]);
        ans = max(ans, dp[scc[u]]);
    }
    cout << ans;
}