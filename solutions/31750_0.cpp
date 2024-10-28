#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 100005;

int N, A[MAXN], S[MAXN], ans = 0;
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    S[u] += A[u];
    for(auto v : graph[u]) {
        if(v == p) continue;
        dfs(v, u);
        S[u] += S[v];
    }
}

void upd(int a, int b, int c)
{
    ans = max(ans, a*b*c);
}

void merge(multiset<int>& a, multiset<int>& b)
{
    if(a.size() < b.size()) {
        swap(a, b);
    }

    for(auto u : b) {
        auto it = a.lower_bound((S[1] - u) / 2);
        if(it != a.end()) {
            upd(S[1] - u - *it, u, *it);
        }
        if(it != a.begin()) {
            it--;
            upd(S[1] - u - *it, u, *it);
        }
    }
    a.insert(b.begin(), b.end());
}

multiset<int> solve(int u, int p)
{
    multiset<int> ret;
    for(auto v : graph[u]) {
        if(v == p) continue;
        auto res = solve(v, u);
        merge(ret, res);
    }

    auto it = ret.lower_bound(S[u]/2);
    if(it != ret.end()) {
        upd(S[1] - S[u], S[u] - *it, *it);
    }
    if(it != ret.begin()) {
        it--;
        upd(S[1] - S[u], S[u] - *it, *it);
    }

    ret.insert(S[u]);

    return ret;
}

signed main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1);
    solve(1, -1);

    cout << ans;
}