#include <bits/stdc++.h>

using namespace std;

#define all(a) a.begin(), a.end()

const int MAXN = 202020;
const int MAXR = 25050;

struct MergeSortTree {
    int n;
    vector<vector<int>> tree;
    void _init(int s, int e, int idx, const vector<int>& v)
    {
        if(s == e) {
            tree[idx].push_back(v[s]);
            return;
        }
        int m = (s + e) / 2;
        _init(s, m, 2*idx, v);
        _init(m+1, e, 2*idx+1, v);
        tree[idx].resize(e - s + 1);
        merge(all(tree[2*idx]), all(tree[2*idx+1]), tree[idx].begin());
    }
    void init(const vector<int>& v)
    {
        n = v.size();
        if(n == 0) return;
        tree.resize(4*n);
        _init(0, n - 1, 1, v);
    }
    int query(int l, int r, int x, int s, int e, int idx)
    {
        if(r < s || e < l) return 0;
        if(l <= s && e <= r) return tree[idx].end() - lower_bound(all(tree[idx]), x);
        int m = (s + e) / 2;
        return query(l, r, x, s, m, 2*idx) + query(l, r, x, m+1, e, 2*idx+1);
    }
    int query(int l, int r, int x)
    {
        if(n == 0) return 0;
        if(r < l) return 0;
        return query(l, r, x, 0, n-1, 1);
    }
};

int N, R, Q, H[MAXN], C[MAXR], in[MAXN], out[MAXN], t;
vector<int> g[MAXN];
vector<pair<int, int>> region[MAXR];
MergeSortTree mst[MAXR];
map<int, map<int, int>> cache;

void dfs(int u)
{
    in[u] = ++t;
    for(auto v : g[u]) {
        dfs(v);
    }
    out[u] = ++t;
}

int topDown(int r1, int r2)
{
    int ret = 0;
    for(auto [s, e] : region[r1]) {
        ret += lower_bound(all(region[r2]), pair{e, 0}) - lower_bound(all(region[r2]), pair{s, 0});
    }
    return ret;
}

int bottomUp(int r1, int r2)
{
    int ret = 0;
    for(auto [s, e] : region[r2]) {
        int idx = lower_bound(all(region[r1]), pair{s, 0}) - region[r1].begin() - 1;
        ret += mst[r1].query(0, idx, s);
    }
    return ret;
}

int main()
{
    cin >> N >> R >> Q;
    cin >> H[1];
    for(int i = 2; i <= N; i++) {
        int j;
        cin >> j >> H[i];
        g[j].push_back(i);
    }

    dfs(1);

    for(int i = 1; i <= N; i++) {
        C[H[i]]++;
        region[H[i]].emplace_back(in[i], out[i]);
    }

    for(int i = 1; i <= R; i++) {
        sort(all(region[i]));
        vector<int> v;
        for(auto [s, e] : region[i]) {
            v.push_back(e);
        }
        mst[i].init(v);
    }

    while(Q--) {
        int r1, r2;
        cin >> r1 >> r2;
        int result = -1;
        if(cache[r1].count(r2)) {
            result = cache[r1][r2];
        } else {
            if(C[r1] < C[r2]) {
                result = cache[r1][r2] = topDown(r1, r2);
            } else {
                result = cache[r1][r2] = bottomUp(r1, r2);
            }
        }
        cout << result << endl;
    }
}