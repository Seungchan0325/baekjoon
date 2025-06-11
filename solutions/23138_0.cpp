#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010101;

struct Fenwick {
    int n;
    vector<ll> tree;
    void init(int _n) {
        n = _n;
        tree.resize(n+1);
    }
    void update(int x, ll v) {
        while(x <= n) {
            tree[x] += v;
            x += x & -x;
        }
    }
    ll query(int x) {
        ll ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

ll n, x[MAXN];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    Fenwick num, sum;
    num.init(n); sum.init(n);

    ll ans = 0;
    for(int i = n; i >= 1; i--) {
        ans += num.query(x[i]) * x[i] - sum.query(x[i]);
        num.update(x[i], 1);
        sum.update(x[i], x[i]);
    }
    ans %= (int)(1e9 + 7);
    cout << ans;
}