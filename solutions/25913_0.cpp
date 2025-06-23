#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;

const ll inf = 1e18;

struct SegTree {
    int n;
    vector<ll> tree;
    void init(int _n) {
        n = _n;
        tree.resize(2*n, -inf);
    }
    void update(int x, ll v) {
        x += n; tree[x] = v;
        while(x >>= 1) tree[x] = max(tree[x<<1], tree[x<<1|1]);
    }
    ll query(int l, int r) {
        ll ret = -inf;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret = max(ret, tree[l++]);
            if(~r&1) ret = max(ret, tree[r--]);
        }
        return ret;
    }
};

int n, q, a[MAXN], l[MAXN], r[MAXN];
ll p[MAXN], ans[MAXN];

void solve()
{
    vector<int> m(q); iota(m.begin(), m.end(), 1);
    sort(m.begin(), m.end(), [&](int i, int j){
        return p[l[i]-1] + p[r[i]] < p[l[j]-1] + p[r[j]];
    });
    vector<int> v(n); iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [&](int i, int j){
        return p[i] < p[j];
    });

    int j = 0;
    SegTree seg; seg.init(n+1);
    for(int i : m) {
        while(j < n && 2*p[v[j]] <= p[l[i]-1] + p[r[i]]) {
            seg.update(v[j], 2*p[v[j]]);
            j++;
        }
        int a = l[i] + (r[i] - l[i] + 1) / 3 - 1;
        int b = l[i] + 2 * (r[i] - l[i] + 1) / 3 - 1;
        ans[i] = min(ans[i], abs(-p[r[i]] - p[l[i]-1] + seg.query(a, b)));
    }
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        p[i] = p[i-1] + a[i];
    }
    cin >> q;
    vector<pair<int, int>> lr;
    for(int i = 1; i <= q; i++) {
        cin >> l[i] >> r[i];
        ans[i] = inf;
    }

    solve();
    for(int i = 1; i <= n; i++) p[i] = -p[i];
    solve();
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
}