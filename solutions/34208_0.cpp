#include <bits/stdc++.h>

using namespace std;

using i128 = __int128_t;
using ll = long long;

const int MAXN = 1010101;
const ll inf = 1e18;

struct Frac {
    ll p, q;
    Frac(ll _p = 1, ll _q = 1) {
        if(_q < 0) {
            _q = -_q;
            _p = -_p;
        }
        p = _p;
        q = _q;
    }
    auto operator <=> (const Frac& o) const {
        return (i128)p * o.q <=> (i128)o.p * q;
    }
};

struct Line {
	ll k, m;
    Frac p;
    Line operator+(const Line& o) const {
        return {k+o.k, m+o.m, 0};
    }
};

Frac cross(const Line& a, const Line& b)
{
    return Frac(a.m-b.m, b.k-a.k);
}

void insert(ll k, ll m, vector<Line>& v)
{
    Line x = {k, m, inf};
    while(v.size() && v.back().k == k) {
        x.m = max(x.m, v.back().m);
        v.pop_back();
    }
    while(v.size() >= 2 && cross(v.end()[-1], x) <= cross(v.end()[-1], v.end()[-2])) {
        v.pop_back();
    }
    if(v.size()) v.back().p = cross(v.back(), x);
    v.push_back(x);
}

ll query(ll x, vector<Line>& v)
{
    int lo = -1;
    int hi = (int)v.size()-1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(v[mid].p < x) lo = mid;
        else hi = mid;
    }
    return v[hi].k * x + v[hi].m;
}

int N, Q;
ll S[MAXN];
vector<Line> cht;

void DnC(int l, int r)
{
    int m = (l + r) / 2;
    if(l != r) {
        DnC(l, m);
        DnC(m+1, r);
    }

    vector<Line> lcht, rcht;
    for(int i = m; i >= l; i--) {
        insert(m-i+1, S[m]-S[i-1], lcht);
    }
    for(int i = m; i <= r; i++) {
        insert(i-m, S[i]-S[m], rcht);
    }

    int p = 0;
    int q = 0;

    while(p < lcht.size() && q < rcht.size()) {
        cht.push_back(lcht[p]+rcht[q]);
        if(lcht[p].p < rcht[q].p) {
            p++;
        } else {
            q++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        cin >> S[i]; S[i] += S[i-1];
    }

    DnC(1, N);

    auto tmp = cht;
    sort(tmp.begin(), tmp.end(), [](Line a, Line b){
        return a.k < b.k;
    });
    cht.clear();
    for(auto l : tmp) insert(l.k, l.m, cht);

    while(Q--) {
        ll x; cin >> x;
        cout << query(x, cht) << "\n";
    }
}