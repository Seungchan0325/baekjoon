#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick
{
    ll n;
    vector<ll> tree;
    void init(ll _n)
    {
        n = _n;
        tree.resize(n+1);
    }
    void update(ll x, ll v)
    {
        while(x <= n) {
            tree[x] += v;
            x += x & -x;
        }
    }
    ll query(ll x)
    {
        ll ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

const int MAXN = 303030;

int n, a[MAXN];
ll lef[MAXN], rig[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    vector<int> v;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        v.push_back(a[i]);
    }
    auto vs = v;
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(vs.begin(), vs.end(), a[i]) - vs.begin() + 1;
    }

    Fenwick f; f.init(vs.size());

    for(int i = 1; i <= n; i++) {
        lef[i] = f.query(vs.size()) - f.query(a[i]);
        f.update(a[i], 1);
    }
    f = Fenwick(); f.init(vs.size());
    for(int i = n; i >= 1; i--) {
        rig[i] = f.query(vs.size()) - f.query(a[i]);
        f.update(a[i], 1);
    }

    ll ans = 0;
    for(int i = 0; i <= n; i++) {
        ans += min(lef[i], rig[i]);
    }
    cout << ans;
}