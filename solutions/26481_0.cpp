#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int n;
    vector<int> t;
    void init(int _n) {
        n = _n;
        t.clear();
        t.resize(2*n);
    }
    void update(int x, int v) {
        x += n;
        t[x] += v;
        while(x>>=1) {
            t[x] = t[x<<1] + t[x<<1|1];
        }
    }
    int query(int l, int r) {
        int ret = 0;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret += t[l++];
            if(~r&1) ret += t[r--];
        }
        return ret;
    }
};

struct Q {
    int l, r, idx;
};

const int MAXN = 101010;

unsigned char msk[MAXN];
int a[MAXN], rb[MAXN], ai[20][MAXN], bi[20][MAXN], c[MAXN], rc[MAXN], tmp[MAXN];

void unit_monge_multiply(int s, int e, int dep)
{
    if(e-s == 1) {
        c[s] = s;
        return;
    }

    int m = (s+e)/2;
    auto split = [](int a[], int ai[], int tmp[], int s, int e) {
        int m = (s + e) / 2;
        int p = s, q = m;
        for(int i = s; i < e; i++) {
            tmp[i] = a[i];
            if(a[i] < m) ai[p++] = i;
            else ai[q++] = i;
        }
        for(int i = s; i < e; i++) a[i] = tmp[ai[i]];
    };

    split(a, ai[dep], tmp, s, e);
    split(rb, bi[dep], tmp, s, e);

    unit_monge_multiply(s, m, dep+1);
    unit_monge_multiply(m, e, dep+1);

    for(int i = s; i < e; i++) tmp[i] = c[i];
    for(int i = s; i < e; i++) {
        c[ai[dep][i]] = bi[dep][tmp[i]];
        rc[bi[dep][tmp[i]]] = ai[dep][i];
        msk[ai[dep][i]] = i < m;
    }

    // compute delta(i+1, j) - delta(i, j)
    auto down_delta = [&](int i, int j) -> int {
        if(i < s || i >= e) return 0;
        if(msk[i]) return j <= c[i];
        else return c[i] < j;
    };
    // compute delta(i, j+1) - delta(i, j)
    auto right_delta = [&](int i, int j) -> int {
        if(j < s || j >= e) return 0;
        if(msk[rc[j]]) return i <= rc[j];
        else return rc[j] < i;
    };

    int i = s;
    int j = e;
    int sum = 0;
    while(j >= s) {
        while(sum < 0) sum += down_delta(i++, j);
        if(j < e && i > s && right_delta(i, j)) c[i-1] = j;
        sum -= right_delta(i, --j);
    }
    return;
}

vector<int> sub_perm_unit_monge_multiply(vector<int> pa, vector<int> pb)
{
    int n = pa.size();
    int p;
    vector<int> rpa(n, -1), rpb(n, -1), v(n, -1);;
    for(int i = 0; i < n; i++) {
        if(pa[i] >= 0) rpa[pa[i]] = i;
    }
    p = 0;
    for(int i = 0; i < n; i++) {
        if(rpa[i] < 0) a[p++] = i;
    }
    for(int i = 0; i < n; i++) {
        if(pa[i] >= 0) a[p++] = pa[i];
    }

    for(int i = 0; i < n; i++) {
        if(pb[i] >= 0) rpb[pb[i]] = i;
    }
    p = 0;
    for(int i = 0; i < n; i++) {
        if(rpb[i] >= 0) {
            rb[p] = rpb[i];
            v[p] = i;
            p++;
        }
    }
    for(int i = 0; i < n; i++) {
        if(pb[i] < 0) {
            rb[p] = i;
            v[p] = -1;
            p++;
        }
    }

    unit_monge_multiply(0, n, 0);

    p = n-1;
    vector<int> pc(n, -1);
    for(int i = n-1; i >= 0; i--) {
        if(pa[i] >= 0) {
            pc[i] = v[c[p--]];
        }
    }

    return pc;
}

vector<int> make_seaweed(vector<int> ra)
{
    if(ra.size() == 1) return {-1};
    int n = ra.size();
    int m = n/2;

    vector<int> l, r, li, ri;
    for(int i = 0; i < n; i++) {
        if(ra[i] < m) l.push_back(ra[i]), li.push_back(i);
        else r.push_back(ra[i]-m), ri.push_back(i);
    }

    auto s1 = make_seaweed(l);
    auto s2 = make_seaweed(r);

    vector<int> p1(n, -1), p2(n, -1);
    for(int i = 0; i < ri.size(); i++) p1[ri[i]] = ri[i];
    for(int i = 0; i < li.size(); i++) p2[li[i]] = li[i];
    for(int i = 0; i < s1.size(); i++) if(s1[i] >= 0) p1[li[i]] = li[s1[i]];
    for(int i = 0; i < s2.size(); i++) if(s2[i] >= 0) p2[ri[i]] = ri[s2[i]];

    return sub_perm_unit_monge_multiply(p1, p2);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    vector<int> p(n);
    for(int i = 0; i < n; i++) cin >> p[i], p[i]--;
    vector<Q> qrys(q);
    for(int i = 0; i < q; i++) {
        cin >> qrys[i].l >> qrys[i].r; qrys[i].idx = i;
        qrys[i].l--; qrys[i].r--;
    }
    sort(qrys.begin(), qrys.end(), [](Q a, Q b) { return a.l < b.l; } );
    auto s = make_seaweed(p);
    vector<int> rs(n, 0);
    for(int i = 0; i < n; i++) {
        if(s[i] >= 0) {
            rs[s[i]] = i+1;
        }
    }
    int j = 0;
    vector<int> ans(q);
    SegTree seg; seg.init(n);
    for(int i = 0; i < n; i++) {
        if(rs[i] == 0) seg.update(i, 1);
    }
    for(int i = 0; i <= n; i++) {
        while(j < q && qrys[j].l <= i) {
            ans[qrys[j].idx] = seg.query(qrys[j].l, qrys[j].r);
            j++;
        }
        if(i < n && s[i] >= 0) seg.update(s[i], 1);
    }
    
    for(int i = 0; i < q; i++) cout << ans[i] << "\n";
}