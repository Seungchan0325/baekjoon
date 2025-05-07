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

int main()
{
    while(true) {
        int n;
        cin >> n;
        if(n == 0) break;
        vector<pair<int, int>> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i].first; a[i].second = i;
        }
        sort(a.begin(), a.end());
        Fenwick f;
        f.init(n);
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            ans += f.query(n) - f.query(a[i].second+1);
            f.update(a[i].second+1, 1);
        }
        cout << ans << "\n";
    }
}