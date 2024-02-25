#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

const int MAXN = 300005;
const int MOD = 998244353;

int N, M, K;
ll home[MAXN], cand[MAXN], sq[MAXN], sum[MAXN], cnt[MAXN];
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    for(auto v : graph[u]) {
        if(v == p) continue;
        dfs(v, u);
        sq[u] += sq[v];
        sq[u] %= MOD;

        sum[u] += sum[v];
        sum[u] %= MOD;

        cnt[u] += cnt[v];
        cnt[u] %= MOD;
    }
    sq[u] += 2 * sum[u] + cnt[u];
    sq[u] %= MOD;

    sum[u] += cnt[u];
    sum[u] %= MOD;

    cnt[u] += home[u];
    cnt[u] %= MOD;
}

ll dfs1(int u, int p, ll _sq, ll _sum, ll _cnt)
{
    ll ret = 0;
    for(auto v : graph[u]) {
        if(v == p) continue;
        ll _ncnt = _cnt + cnt[u] - cnt[v];
        ll _nsum = _sum + sum[u] - (sum[v] + cnt[v]) + _ncnt;
        ll _nsq = _sq + 2 * (_sum + sum[u] - (sum[v] + cnt[v])) + _ncnt + sq[u] - (sq[v] + 2 * sum[v] + cnt[v]);
        ret += dfs1(v, u, (_nsq + 2*MOD) % MOD, (_nsum + 2*MOD) % MOD, (_ncnt + 2*MOD) % MOD);
        ret %= MOD;
    }
    if(cand[u]) {
        ret += sq[u] + _sq;
        ret %= MOD;
    }
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cin >> M;
    for(int i = 0; i < M; i++) {
        int u;
        cin >> u;
        home[u] = 1;
    }
    cin >> K;
    for(int i = 0; i < K; i++) {
        int u;
        cin >> u;
        cand[u] = 1;
    }

    dfs(1, -1);

    long long result = dfs1(1, -1, 0, 0, 0);
    cout << result;
}