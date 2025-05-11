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

int n;
string a, b;

int main()
{
    cin >> n;
    cin >> a >> b;
    queue<int> q[26];
    for(int i = 0; i < n; i++) {
        q[b[i]-'A'].push(i+1);
    }
    vector<int> v;
    for(int i = 0; i < n; i++) {
        v.push_back(q[a[i]-'A'].front());
        q[a[i]-'A'].pop();
    }

    ll ans = 0;
    Fenwick f;
    f.init(n);
    for(int i = 0; i < n; i++) {
        ans += f.query(n) - f.query(v[i]);
        f.update(v[i], 1);
    }
    cout << ans;
}