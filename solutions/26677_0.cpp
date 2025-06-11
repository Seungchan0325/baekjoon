#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;
const ll inf = 1e18;

ll n, s[MAXN];

struct SegTree {
    int n;
    vector<ll> tree;
    void init(int _n) {
        n = _n;
        tree.resize(2*n, inf);
    }
    void update(int x, ll v) {
        x += n; tree[x] = min(v, tree[x]);
        while(x >>= 1) tree[x] = min(tree[x<<1], tree[x<<1|1]);
    }
    ll query(int l, int r) {
        ll ret = inf;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret = min(ret, tree[l++]);
            if(~r&1) ret = min(ret, tree[r--]);
        }
        return ret;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<ll> vs;
    vs.push_back(s[0]);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i-1];
        vs.push_back(s[i]);
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    for(int i = 0; i <= n; i++) {
        s[i] = lower_bound(vs.begin(), vs.end(), s[i]) - vs.begin();
    }

    SegTree seg; seg.init(vs.size());
    ll dp = 0;
    for(int i = 1; i <= n; i++) {
        seg.update(s[i-1], dp - i);
        dp = seg.query(0, s[i]) + i;
    }

    if(dp >= inf) cout << "-1\n";
    else cout << dp << "\n";
}