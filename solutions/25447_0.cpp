#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct Node {
    int count;
    int width;
    int sum;
};

int N, M, ans[MAXN];
vector<tuple<int, int, int>> g[MAXN];
vector<int> xs;
Node tree[8*MAXN];

void init(int s = 0, int e = ssize(xs)-2, int idx = 1)
{
    if(s == e) {
        tree[idx].width = xs[s+1]-xs[s];
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx].width = tree[2*idx].width + tree[2*idx+1].width;
}

void update(int l, int r, int v, int s = 0, int e = ssize(xs)-2, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        tree[idx].count += v;
        if(tree[idx].count) tree[idx].sum = tree[idx].width;
        else if(s != e) {
            tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
        } else {
            tree[idx].sum = 0;
        }
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    if(tree[idx].count == 0) tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
}

void dfs(int u, int p)
{
    ans[u] = tree[1].sum;
    for(auto [v, l, r] : g[u]) {
        if(v == p) continue;
        l = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        r = upper_bound(xs.begin(), xs.end(), r) - xs.begin()-1;
        update(l, r, 1);
        dfs(v, u);
        update(l, r, -1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i < N; i++) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        g[u].emplace_back(v, l, r);
        g[v].emplace_back(u, l, r);
        xs.push_back(l);
        xs.push_back(r+1);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    init();
    dfs(1, -1);
    for(int i = 2; i <= N; i++) cout << ans[i] << "\n";
}