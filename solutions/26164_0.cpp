#include <bits/stdc++.h>

using namespace std;

const int MAXN = 404040;
const int LOGN = 20;

unsigned char msk[MAXN];
int a[MAXN], rb[MAXN], ai[LOGN][MAXN], bi[LOGN][MAXN], c[MAXN], rc[MAXN], tmp[MAXN];

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

vector<int> unit_monge_multiply(vector<int> pa, vector<int> pb)
{
    int n = pa.size();
    for(int i = 0; i < n; i++) a[i] = pa[i];
    for(int i = 0; i < n; i++) rb[pb[i]] = i;
    unit_monge_multiply(0, n, 0);
    return vector<int>(c, c+n);
}

vector<int> make_seaweed(vector<int> ra)
{
    if(ra.size() == 1) return {0, 1};
    int n = ra.size();
    int m = n / 2;

    vector<int> l, r, li, ri;
    for(int i = 0; i < n; i++) {
        if(ra[i] < m) l.push_back(ra[i]), li.push_back(i);
        else r.push_back(ra[i]-m), ri.push_back(i);
    }
    int p = l.size();
    int q = r.size();

    auto s1 = make_seaweed(l);
    auto s2 = make_seaweed(r);
    vector<int> p1(2*n), p2(2*n);
    iota(p1.begin(), p1.end(), 0);
    iota(p2.begin(), p2.end(), 0);
    for(auto& i : s1) i = i < p ? li[i] + q : i + 2*q;
    for(auto& i : s2) i = i < q ? ri[i] : i + p;
    for(auto i : ri) p1[i+n] = i + q;
    for(auto i : li) p2[i+n-p] = i;
    for(int i = 0; i < p; i++) p1[i+q] = s1[i];
    for(int i = 0; i < p; i++) p1[li[i]+n] = s1[i+p];
    for(int i = 0; i < q; i++) p2[i] = s2[i];
    for(int i = 0; i < q; i++) p2[ri[i]+n-p] = s2[i+q];

    return unit_monge_multiply(p1, p2);
}

struct SegTree {
    int n;
    vector<int> tree;
    void init(int _n) {
        n = _n;
        tree.resize(2*n);
    }
    void update(int x, int v) {
        tree[x += n] += v;
        while(x>>=1) tree[x] = tree[x<<1] + tree[x<<1|1];
    }
    int query(int l, int r)
    {
        int res = 0;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) res += tree[l++];
            if(~r&1) res += tree[r--];
        }
        return res;
    }
};

int main()
{
    int N;
    cin >> N;
    vector<int> RA(N);
    for(int i = 0; i < N; i++) {
        int x; cin >> x; x--;
        RA[x] = i;
    }
    auto s = make_seaweed(RA);
    vector<int> rs(2*N);
    for(int i = 0; i < 2*N; i++) rs[s[i]] = i;
    SegTree seg; seg.init(2*N);
    for(int i = 0; i < N-1; i++) {
        seg.update(rs[i], 1);
        cout << seg.query(0, N-i-2)+1 << " ";
    }
}
