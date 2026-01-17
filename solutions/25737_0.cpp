#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using i128 = __int128_t;

const int MAXN = 202020;
const int MAXQ = 505050;

struct DataStruct {
    ll firstv, firsti;
    ll secondv, secondi;
    ll thirdv, thirdi;
    DataStruct() : firstv(0), firsti(-1), secondv(0), secondi(-1), thirdv(0), thirdi(-1) {}
    void U(ll v, ll i)
    {
        if(firstv < v) {
            thirdv = secondv;
            thirdi = secondi;
            secondv = firstv;
            secondi = firsti;
            firstv = v;
            firsti = i;
        } else if(secondv < v) {
            thirdv = secondv;
            thirdi = secondi;
            secondv = v;
            secondi = i;
        } else if(thirdv < v) {
            thirdv = v;
            thirdi = i;
        }
    }
    ll Q(ll x, ll y)
    {
        if(firsti != x && firsti != y) return firstv;
        if(secondi != x && secondi != y) return secondv;
        return thirdv;
    }
};

struct Query {
    ll u, v, A, B, idx;
};

struct Fraction {
    ll p, q;
    Fraction(ll _p = 1, ll _q = 1) {
        if(_q < 0) {
            _q = -_q;
            _p = -_p;
        }
        p = _p;
        q = _q;
    }
    auto operator <=> (const Fraction& o) const {
        return (i128)p * o.q <=> (i128)o.p * q;
    }
};

struct Line {
    ll a, b;
    ll get(ll p, ll q) { return a * p + b * q; }
};

Fraction intersect(const Line& a, const Line& b)
{
    return Fraction(a.b-b.b, b.a-a.a);
}

struct RollbackCHT {
    int sz;
    Line v[MAXN];
    // (index, size, value)
    stack<tuple<int, int, Line>> s;
    RollbackCHT() : sz(0), v{}, s() {}
    void add(const Line& line)
    {
        if(sz && v[sz-1].a == line.a && v[sz-1].b >= line.b) {
            s.emplace(-1, -1, -1);
            return;
        }
        int lo = -1;
        int hi = sz;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(v[mid].a == line.a && v[mid].b <= line.b) hi = mid;
            else lo = mid;
        }
        lo = -1;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(mid > 0 && intersect(v[mid], v[mid-1]) > intersect(v[mid], line)) hi = mid;
            else lo = mid;
        }
        s.emplace(hi, sz, v[hi]);
        v[hi] = line;
        sz = hi+1;
    }
    ll query(ll p, ll q)
    {
        int lo = -1;
        int hi = sz;
        while(lo+1 < hi) {
            int mid = (lo + hi) / 2;
            if(mid <= 0 || intersect(v[mid-1], v[mid]) <= Fraction(p, q)) lo = mid;
            else hi = mid;
        }
        return v[lo].get(p, q);
    }
    void rollback()
    {
        auto [idx, Sz, line] = s.top(); s.pop();
        if(idx == -1) return;
        v[idx] = line;
        sz = Sz;
    }
};

ll N, Q;
ll ans[MAXQ];
vector<pair<ll, ll>> g[MAXN];

ll h[MAXN];
DataStruct mxh[MAXN];

bool erased[MAXN];
ll cdep[MAXN], cpar[MAXN];
ll sz[MAXN], uc[MAXN], dep[MAXN], lu[MAXN];
vector<Query> Qs[MAXN];
vector<Query> Qr[MAXN];
RollbackCHT cht;

void dfs(int u, int p)
{
    h[u] = 0;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        mxh[u].U(h[v]+w, v);
        h[u] = max(h[u], h[v] + w);
    }
}

void rdfs(int u, int p, ll uph)
{
    mxh[u].U(uph, p);
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        rdfs(v, u, mxh[u].Q(v, 0)+w);
    }
}

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int u, int p, int n)
{
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(v, u, n);
    }
    return u;
}

void cdfs(int u, int p)
{
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dep[v] = dep[u] + w;
        uc[v] = max(uc[u]+w, mxh[u].Q(v, p)+w);
        lu[v] = lu[u];
        cdfs(v, u);
    }
    uc[u] = max(mxh[u].Q(p, 0), uc[u]);
}

void cht_dfs(int u, int p, ll mx)
{
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        cht.add({mx, -dep[u]+mxh[u].Q(p, v)});
        cht_dfs(v, u, max(mx, dep[u]+mxh[u].Q(p, v)));
        cht.rollback();
    }
    cht.add({mx, -dep[u]+mxh[u].Q(p, 0)});
    for(auto [u, v, A, B, idx] : Qr[u]) {
        ans[idx] = max(ans[idx], cht.query(B, A) + A * dep[u] + B * dep[v]);
    }
    cht.rollback();
}

void dnc(int u, int d, int p)
{
    get_sz(u, -1);
    int c = get_cent(u, -1, sz[u]);
    cdep[c] = d;
    cpar[c] = p;

    erased[c] = true;

    for(auto [v, w] : g[c]) {
        if(erased[v]) continue;
        dnc(v, d+1, c);
    }
}

void work(int u)
{
    get_sz(u, -1);
    int c = get_cent(u, -1, sz[u]);

    erased[c] = true;
    lu[c] = 0;
    uc[c] = 0;
    dep[c] = 0;
    for(auto [v, w] : g[c]) {
        if(erased[v]) continue;
        dep[v] = w;
        uc[v] = 0;
        lu[v] = v;
        cdfs(v, c);
    }

    for(auto [u, v, A, B, idx] : Qs[c]) {
        if(c == v) {
            swap(u, v);
            swap(A, B);
        }
        ans[idx] = 0;
        if(c == u) {
            ans[idx] = max(ans[idx], A * mxh[u].Q(lu[v], 0) + B * uc[v]);
            Qr[v].push_back({v, u, B, A, idx});
        } else {
            ans[idx] = max(ans[idx], A * (dep[u] + mxh[c].Q(lu[u], lu[v])) + B * (uc[v]));
            ans[idx] = max(ans[idx], A * (uc[u]) + B * (dep[v] + mxh[c].Q(lu[u], lu[v])));
            ans[idx] = max(ans[idx], A * (uc[u]) + B * (uc[v]));
            Qr[u].push_back({u, v, A, B, idx});
            Qr[v].push_back({v, u, B, A, idx});
        }
    }

    for(auto [v, w] : g[c]) {
        if(erased[v]) continue;
        cht_dfs(v, c, 0);
    }

    for(auto [u, v, A, B, idx] : Qs[c]) {
        Qr[u].clear();
        Qr[v].clear();
    }

    for(auto [v, w] : g[c]) {
        if(erased[v]) continue;
        work(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for(int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dfs(1, -1);
    rdfs(1, -1, 0);
    dnc(1, 0, -1);

    for(int i = 1; i <= Q; i++) {
        ll u, v, A, B;
        cin >> u >> v >> A >> B;
        ll cu = u, cv = v;
        while(cu != cv) {
            if(cdep[cu] < cdep[cv]) swap(cu, cv);
            cu = cpar[cu];
        }
        Qs[cu].push_back({u, v, A, B, i});
    }

    for(int i = 1; i <= N; i++) erased[i] = false;

    work(1);

    for(int i = 1; i <= Q; i++) cout << ans[i] << "\n";
}