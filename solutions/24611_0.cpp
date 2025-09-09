#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick {
    int N;
    vector<int> tree;
    Fenwick(int N) : N(N), tree(N+1) {}

    void upd(int x, int v)
    {
        while(x <= N) {
            tree[x] += v;
            x += x & -x;
        }
    }

    int qry(int x)
    {
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

const int MAXN = 101010;

struct DSU {
    vector<int> uf;
    void init(int n) {
        uf.resize(n);
        iota(uf.begin(), uf.end(), 0);
    }
    int find(int x) {
        if(uf[x] == x) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int x, int y) {
        x = find(x); y = find(y);
        uf[y] = x;
    }
};

struct Node {
    int lazy = 0, cnt = 0;
};

bool vst[MAXN];
int N, T, X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN], D[2*MAXN], UP[2*MAXN], DW[2*MAXN], who[2*MAXN], exterior[MAXN];
Node tree[MAXN<<3];
DSU dsu;

void apply(int idx, int v)
{
    if(!tree[idx].cnt) return;
    if(tree[idx].lazy) dsu.merge(tree[idx].lazy, v);
    else tree[idx].lazy = v;
}

void push(int s, int e, int idx)
{
    if(!tree[idx].lazy) return;
    if(s != e) {
        apply(2*idx, tree[idx].lazy);
        apply(2*idx+1, tree[idx].lazy);
    } else {
        dsu.merge(who[s], tree[idx].lazy);
    }
    tree[idx].lazy = 0;
}

void pull(int s, int e, int idx)
{
    tree[idx].cnt = tree[2*idx].cnt + tree[2*idx+1].cnt;
}

void update_range_merge(int l, int r, int v, int s = 0, int e = 2*N+1, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        apply(idx, v);
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update_range_merge(l, r, v, s, m, 2*idx);
    update_range_merge(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void update_inc(int x, int v, int s = 0, int e = 2*N+1, int idx = 1)
{
    push(s, e, idx);
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx].cnt += v;
        return;
    }
    int m = (s + e) / 2;
    update_inc(x, v, s, m, 2*idx);
    update_inc(x, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void force_lazy(int s = 0, int e = 2*N+1, int idx = 1)
{
    push(s, e, idx);
    if(s != e) {
        int m = (s + e) / 2;
        force_lazy(s, m, 2*idx);
        force_lazy(m+1, e, 2*idx+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> T;
    for(int i = 1; i <= N; i++) cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];

    for(int i = 1; i <= N; i++) {
        D[X1[i]] = 1;
        D[X2[i]] = -1;
        UP[X1[i]] = UP[X2[i]] = Y1[i];
        DW[X1[i]] = DW[X2[i]] = Y2[i];
        who[Y1[i]] = i;
        who[Y2[i]] = i;
    }

    dsu.init(2*N+5);

    ll inter = 0;
    int corners[2] = {0, 0};
    Fenwick f(2*N+2);
    for(int i = 1; i <= 2*N; i++) {
        int id = who[UP[i]];
        if(D[i] > 0) {
            exterior[id] = f.qry(UP[i]) % 2;
            corners[f.qry(UP[i])%2]++;
            corners[f.qry(DW[i])%2]++;
            inter += f.qry(DW[i]) - f.qry(UP[i]);
            f.upd(UP[i], 1);
            f.upd(DW[i], 1);
            update_inc(UP[i], 1);
            update_inc(DW[i], 1);
            update_range_merge(UP[i], DW[i], id);
        } else {
            update_range_merge(UP[i], DW[i], id);
            f.upd(UP[i], -1);
            f.upd(DW[i], -1);
            update_inc(UP[i], -1);            
            update_inc(DW[i], -1);
            corners[f.qry(UP[i])%2]++;
            corners[f.qry(DW[i])%2]++;
            inter += f.qry(DW[i]) - f.qry(UP[i]);
        }
    }
    force_lazy();

    int black_immersed = 0;
    int white_immersed = 0;
    for(int i = 1; i <= 2*N; i++) {
        int id = who[UP[i]];
        if(D[i] > 0) {
            if(!vst[dsu.find(id)]) {
                vst[dsu.find(id)] = true;
                if(exterior[id]) {
                    black_immersed++;
                } else {
                    white_immersed++;
                }
            }
        }
    }

    ll black_corners = corners[0] - corners[1] + 2 * inter;
    ll white_corners = corners[1] - corners[0] + 2 * inter;
    ll black_regions = black_corners / 4 + black_immersed;
    ll white_regions = white_corners / 4 + white_immersed + 1;
    if(T == 1) cout << black_regions + white_regions << "\n";
    else cout << white_regions << " " << black_regions << "\n";
}