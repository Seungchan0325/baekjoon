#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;
const ll inf = 1e18;
const ll mod = 1e9 + 9;

ll n, s[MAXN], dp[MAXN];

struct SegTree {
    int n;
    vector<ll> tree;
    void init(int _n) {
        n = _n;
        tree.resize(2*n, 0);
    }
    void update(int x, ll v) {
        x += n; tree[x] += v;
        while(x >>= 1) tree[x] = (tree[x<<1] + tree[x<<1|1]) % mod;
    }
    ll query(int l, int r) {
        ll ret = 0;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret += tree[l++], ret %= mod;
            if(~r&1) ret += tree[r--], ret %= mod;
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
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        seg.update(s[i-1], dp[i-1]);
        dp[i] = seg.query(0, s[i]);
    }

    if(dp[n] >= inf) cout << "-1\n";
    else cout << dp[n] << "\n";
}