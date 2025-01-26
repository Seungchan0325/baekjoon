#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 301010;

struct Fenwick {
    int N;
    vector<ll> tree;
    void init(int _N)
    {
        N = _N;
        tree.resize(N+1);
    }
    void update(int x, ll v)
    {
        while(x <= N) {
            tree[x] += v;
            x += x & -x;
        }
    }
    ll query(int x)
    {
        x = min(x, N);
        ll ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

struct RollBackStack {
    int N = 0;
    ll offset = 0;
    vector<ll> st;
    stack<tuple<int, int, ll>> roll;
    void push(ll v)
    {
        v -= offset;
        if(st.size() < N + 1) {
            roll.emplace(N, -1, -1);
            st.push_back(v);
            N++;
        } else {
            roll.emplace(N, N, st[N]);
            st[N] = v;
            N++;
        }
    }
    void pop(int idx)
    {
        roll.emplace(N, -1, -1);
        N = idx;
    }
    ll top()
    {
        return st[N-1] + offset;
    }
    void add(ll v)
    {
        offset += v;
    }
    int find(ll v)
    {
        v -= offset;
        int idx = lower_bound(st.begin(), st.begin() + N, v) - st.begin();
        return idx;
    }
    void rollback()
    {
        auto [n, idx, v] = roll.top(); roll.pop();
        N = n;
        if(idx != -1) {
            st[idx] = v;
        }
    }
};

bool erased[MAXN];
int N, sz[MAXN];
ll S[MAXN], C[MAXN];
vector<pair<int, ll>> g[MAXN];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

void dfs0(int u, int p, ll s, ll mx, vector<tuple<ll, ll, ll>>& prefix, RollBackStack& reset)
{
    mx = max(mx, s);
    prefix.emplace_back(u, mx, reset.N-1);
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        reset.add(w);
        int idx = reset.find(0);
        reset.pop(idx);
        reset.push(0);
        dfs0(v, u, s + w, mx, prefix, reset);
        reset.rollback();
        reset.rollback();
        reset.add(-w);
    }
}

void dfs1(int u, int p, ll s, ll mx, vector<tuple<ll, ll, ll>>& sufix)
{
    sufix.emplace_back(s, max(mx, 0LL), (mx < 0 ? sz[u] : 0));
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dfs1(v, u, s+w, max(mx+w, w), sufix);
    }
}

void DnC(int u)
{
    dfs(u, -1);
    int cent = get_cent(sz[u], u, -1);
    dfs(cent, -1);
    erased[cent] = true;

    vector<ll> ss;
    ss.push_back(0); // for centroid
    vector<vector<tuple<ll, ll, ll>>> suffixes(g[cent].size());
    for(int i = 0; i < g[cent].size(); i++) {
        auto [v, w] = g[cent][i];
        if(erased[v]) continue;
        
        vector<tuple<ll, ll, ll>> suffix;
        dfs1(v, cent, w, w, suffix);
        for(auto [s, mx, reset] : suffix) {
            ss.push_back(-s + mx);
        }
        suffixes[i] = suffix;
    }

    sort(ss.begin(), ss.end());
    ss.erase(unique(ss.begin(), ss.end()), ss.end());

    Fenwick cnt{}, ps{}, pmx{}, preset{};
    cnt.init(ss.size());
    ps.init(ss.size());
    pmx.init(ss.size());
    preset.init(ss.size());

    for(int i = 0; i < g[cent].size(); i++) {
        auto [v, w] = g[cent][i];
        if(erased[v]) continue;
        for(auto [s, mx, reset] : suffixes[i]) {
            int idx = lower_bound(ss.begin(), ss.end(), -s + mx) - ss.begin() + 1;
            cnt.update(idx, 1);
            ps.update(idx, s);
            pmx.update(idx, mx);
            preset.update(idx, reset);
        }
    }

    {
        int idx = upper_bound(ss.begin(), ss.end(), 0) - ss.begin();
        S[cent] += ps.query(idx) + pmx.query(ss.size()) - pmx.query(idx);
        C[cent] += preset.query(ss.size()) - preset.query(idx);
        cnt.update(idx, 1);
    }

    for(int i = 0; i < g[cent].size(); i++) {
        auto [v, w] = g[cent][i];
        if(erased[v]) continue;

        for(auto [s, mx, reset] : suffixes[i]) {
            int idx = lower_bound(ss.begin(), ss.end(), -s + mx) - ss.begin() + 1;
            cnt.update(idx, -1);
            ps.update(idx, -s);
            pmx.update(idx, -mx);
            preset.update(idx, -reset);
        }

        vector<tuple<ll, ll, ll>> prefix;
        RollBackStack reset{};
        reset.push(0);
        reset.add(w);
        int idx = reset.find(0);
        reset.pop(idx);
        reset.push(0);
        dfs0(v, cent, w, max(0LL, w), prefix, reset);
        
        for(auto [i, mx, reset] : prefix) {
            C[i] += (ll)reset * (sz[cent] - sz[v]);
            int idx = upper_bound(ss.begin(), ss.end(), mx) - ss.begin();
            S[i] += mx * cnt.query(idx) + ps.query(idx) + pmx.query(ss.size()) - pmx.query(idx);
            C[i] += preset.query(ss.size()) - preset.query(idx);
        }

        for(auto [s, mx, reset] : suffixes[i]) {
            int idx = lower_bound(ss.begin(), ss.end(), -s + mx) - ss.begin() + 1;
            cnt.update(idx, 1);
            ps.update(idx, s);
            pmx.update(idx, mx);
            preset.update(idx, reset);
        }
    }

    for(auto [v, w] : g[cent]) {
        if(erased[v]) continue;
        DnC(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    DnC(1);
    cout << "1\n";
    for(int i = 1; i <= N; i++) cout << S[i] << " ";
    cout << "\n";
    for(int i = 1; i <= N; i++) cout << C[i] << " ";
}