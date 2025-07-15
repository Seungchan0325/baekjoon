#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

const int MAXN = 303030;

/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = numeric_limits<ll>::max();
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

long long n, c[MAXN], s[MAXN];

void solve()
{
    for(int i = 1; i <= n; i++) s[i] = s[i-1] + c[i];

    LineContainer cht;

    auto add = [&](ll x) {
        cht.add(x, s[x]);
    };
    
    auto qry = [&](ll x) -> ll {
        return cht.query(-c[x]) - s[x] + s[n] + c[x]*x;
    };

    ll ans = numeric_limits<ll>::min();
    add(0);
    for(int i = 2; i <= n; i++)
    {
        add(i-2);
        ans = max(ans, qry(i));
    }
    cout << (long long)ans << "\n";
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    solve();
    reverse(c+1, c+n+1);
    solve();
}