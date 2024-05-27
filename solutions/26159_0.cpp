#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const int MAXN = 100005;

int N;
ll sz[MAXN];
vector<int> g[MAXN];
vector<int> a;

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i < N; i++) {
        int ai;
        cin >> ai;
        a.push_back(ai);
    }

    dfs(1, -1);

    sort(sz + 2, sz + 1 + N, [](ll l, ll r) {
        return l * (N - l) > r * (N - r);
    });
    sort(a.begin(), a.end());

    ll cnt = 0;
    for(int i = 2; i <= N; i++) {
        cnt += sz[i] * (N - sz[i]) % MOD * a[i-2];
        cnt %= MOD;
    }
    cout << cnt;
}