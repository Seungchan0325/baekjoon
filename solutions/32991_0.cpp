#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 202020;
const int mod = 1e9 + 7;

int N, P[MAXN], x[MAXN], in[MAXN], out[MAXN], ch[MAXN], st[MAXN], pv;
ll tree[4*MAXN], lazya[4*MAXN], lazyb[4*MAXN];
vector<int> g[MAXN];

void dfs(int u)
{
    st[u] = pv+1;
    for(auto v : g[u]) {
        in[v] = ++pv;
    }
    ch[u] = pv;
    for(auto v : g[u]) {
        dfs(v);
    }
    out[u] = pv;
}

void init(int s = 1, int e = N, int idx = 1)
{
    tree[idx] = 0;
    lazya[idx] = 1;
    lazyb[idx] = 0;
    if(s == e) return;
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
}

void apply(int idx, ll a, ll b)
{
    lazya[idx] = lazya[idx] * a % mod;
    lazyb[idx] = lazyb[idx] * a % mod;
    lazyb[idx] = (lazyb[idx] + b) % mod;
}

void push(int s, int e, int idx)
{
    if(s != e) {
        apply(2*idx, lazya[idx], lazyb[idx]);
        apply(2*idx+1, lazya[idx], lazyb[idx]);
    } else {
        tree[idx] = (lazya[idx] * tree[idx] % mod + lazyb[idx]) % mod;
    }
    lazya[idx] = 1;
    lazyb[idx] = 0;
}

void update(int l, int r, ll a, ll b, int s = 1, int e = N, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        apply(idx, a, b);
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, a, b, s, m, 2*idx);
    update(l, r, a, b, m+1, e, 2*idx+1);
}

ll query(int x, int s = 1, int e = N, int idx = 1)
{
    push(s, e, idx);
    if(e < x || x < s) return 0;
    if(s == e) return tree[idx];
    int m = (s + e) / 2;
    return query(x, s, m, 2*idx) + query(x, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> x[i];
    P[1] = -1;
    for(int i = 2; i <= N; i++) cin >> P[i];
    for(int i = 2; i <= N; i++) g[P[i]].push_back(i);
    in[1] = ++pv;
    dfs(1);
    init();
    for(int i = 1; i <= N; i++) update(in[i], in[i], 0, x[i]);

    int Q;
    cin >> Q;
    while(Q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int v, a, b;
            cin >> v >> a >> b;
            if(P[v] > 0) update(in[P[v]], in[P[v]], a, b);
            update(in[v], in[v], a, b);
            update(st[v], ch[v], a, b);
        } else if(t == 2) {
            int v, a, b;
            cin >> v >> a >> b;
            update(in[v], in[v], a, b);
            update(st[v], out[v], a, b);
        } else if(t == 3) {
            int v;
            cin >> v;
            ll ans = query(in[v]);
            cout << ans << "\n";
        }
    }
}