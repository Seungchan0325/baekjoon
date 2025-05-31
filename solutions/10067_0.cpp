#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using llll = __int128_t;

const int MAXN = 101010;
const int MAXK = 202;
const ll inf = 1e18;

struct Line {
    ll a, b, idx;
    ll get(ll x) {
        return a * x + b;
    }
};

struct Frac {
    ll up, dw;
    Frac() : up(0), dw(1) {}
    Frac(ll _up, ll _dw) : up(_up), dw(_dw) {
        if(dw < 0) up = -up, dw = -dw;
    }
    Frac(ll x) : up(x), dw(1) {}
    bool operator < (const Frac& rhs) const {
        return (llll)up * rhs.dw < (llll)rhs.up * dw;
    }
    
    bool operator <= (const Frac& rhs) const {
        return (llll)up * rhs.dw <= (llll)rhs.up * dw;
    }
};

Frac cross(Line a, Line b)
{
    return Frac((b.b - a.b), (a.a - b.a));
}

int n, k;
ll a[MAXN];
ll dp[2][MAXN];
int prv[MAXK][MAXN];

deque<Line> v;

Line query(ll x)
{
    while(v.size() >= 2 && cross(v[0], v[1]) < x) v.pop_front();
    return v[0];
}

void insert(Line l)
{
    while(v.size() && v.back().a == l.a) {
        if(v.back().b > l.b) {
            swap(v.back(), l);
        }
        v.pop_back();
    }
    while(v.size() >= 2 && cross(v.end()[-1], l) <= cross(v.end()[-1], v.end()[-2])) v.pop_back();
    v.push_back(l);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k; k++;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }
    for(int i = 0; i <= n; i++) dp[0][i] = -inf;
    dp[0][0] = 0;
    for(int c = 1; c <= k; c++) {
        v.clear();
        for(int i = c; i <= n; i++) {
            insert(Line(2*a[i-1], dp[~c&1][i-1] - a[i-1]*a[i-1], i-1));
            dp[c&1][i] = query(a[i]).get(a[i]) - a[i] * a[i];
            prv[c][i] = query(a[i]).idx;
        }
    }
    cout << (dp[k&1][n] + a[n] * a[n]) / 2 << "\n";
    int j = n;
    for(int i = k; i > 1; i--) {
        cout << prv[i][j] << " ";
        j = prv[i][j];
    }
}