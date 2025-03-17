#include <bits/stdc++.h>

using namespace std;

const int MAXN = 201010;

int N, M, A[MAXN], op[MAXN], a[MAXN], b[MAXN], c[MAXN];
vector<int> cands[MAXN];

struct Fenwick {
    int n;
    vector<int> v, tree;
    void init(vector<int> _v)
    {
        v = _v;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        n = v.size();
        tree.resize(v.size() + 1);
    }

    void update(int x, int d)
    {
        x = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        assert(x > 0);
        while(x <= n) {
            tree[x] += d;
            x += x & -x;
        }
    }

    int query(int x)
    {
        x = upper_bound(v.begin(), v.end(), x) - v.begin();
        assert(x <= n);
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

struct Seg {
    int n;
    vector<Fenwick> tree;
    void init(int _n)
    {
        n = _n;
        tree.resize(4*n);
        _init(1, n, 1);
    }
    vector<int> _init(int s, int e, int idx)
    {
        if(s == e) {
            tree[idx].init(cands[s]);
            tree[idx].update(A[s], 1);
            return cands[s];
        }
        int m = (s + e) / 2;
        auto a = _init(s, m, 2*idx);
        auto b = _init(m+1, e, 2*idx+1);
        if(a.size() < b.size()) swap(a, b);
        a.insert(a.end(), b.begin(), b.end());
        tree[idx].init(a);
        for(int i = s; i <= e; i++)
            tree[idx].update(A[i], 1);
        return a;
    }
    void update(int x, int y, int d, int s, int e, int idx)
    {
        if(e < x || x < s) return;
        tree[idx].update(y, d);
        if(s == e) {
            return;
        }
        int m = (s + e) / 2;
        update(x, y, d, s, m, 2*idx);
        update(x, y, d, m+1, e, 2*idx+1);
    }
    int query(int l, int r, int k, int s, int e, int idx)
    {
        if(e < l || r < s) return 0;
        if(l <= s && e <= r) return tree[idx].query(k);
        int m = (s + e) / 2;
        return query(l, r, k, s, m, 2*idx) + query(l, r, k, m+1, e, 2*idx+1);
    }

    void update(int x, int y, int d)
    {
        update(x, y, d, 1, n, 1);
    }
    int query(int l, int r, int k)
    {
        return query(l, r, k, 1, n, 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        cands[i].push_back(A[i]);
    }
    cin >> M;
    for(int i = 1; i <= M; i++) {
        cin >> op[i] >> a[i] >> b[i];
        if(op[i] == 2) cin >> c[i];
        if(op[i] == 1) cands[a[i]].push_back(b[i]);
    }
    Seg seg;
    seg.init(N);
    for(int i = 1; i <= M; i++) {
        if(op[i] == 1) {
            seg.update(a[i], A[a[i]], -1);
            A[a[i]] = b[i];
            seg.update(a[i], A[a[i]], 1);
        } else {
            int result = seg.query(a[i], b[i], 1e9) - seg.query(a[i], b[i], c[i]);
            cout << result << "\n";
        }
    }
}