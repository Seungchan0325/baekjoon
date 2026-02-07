#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505050;

struct Node {
    int lazy, cnt;
};

struct Line {
    int x1, y1, x2, y2, id;
};

struct DSU {
    vector<int> uf;
    void init(int n) {
        uf.resize(n);
        iota(uf.begin(), uf.end(), 0);
    }
    int find(int x)
    {
        if(uf[x] == x) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        uf[y] = x;
    }
};

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

Node tree[8*MAXN];
DSU dsu;
multiset<int> ms[2*MAXN];
int H, W;

void apply(int idx, int v)
{
    if(!tree[idx].cnt) return;
    if(tree[idx].lazy != -1) dsu.merge(tree[idx].lazy, v);
    else tree[idx].lazy = v;
}

void push(int s, int e, int idx)
{
    if(tree[idx].lazy < 0) return;
    if(s != e) {
        apply(2*idx, tree[idx].lazy);
        apply(2*idx+1, tree[idx].lazy);
    } else if(ms[s].size()){
        dsu.merge(*ms[s].begin(), tree[idx].lazy);
    }
    tree[idx].lazy = -1;
}

void pull(int s, int e, int idx)
{
    tree[idx].cnt = tree[2*idx].cnt + tree[2*idx+1].cnt;
}

void init(int s = 0, int e = H, int idx = 1)
{
    tree[idx].cnt = 0;
    tree[idx].lazy = -1;
    if(s == e) return;
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
}

void add(int x, int v, int s = 0, int e = H, int idx = 1)
{
    push(s, e, idx);
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx].cnt += v;
        return;
    }
    int m = (s + e) / 2;
    add(x, v, s, m, 2*idx);
    add(x, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void merge(int l, int r, int v, int s = 0, int e = H, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        apply(idx, v);
        return;
    }
    int m = (s + e) / 2;
    merge(l, r, v, s, m, 2*idx);
    merge(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void force_lazy(int s = 0, int e = H, int idx = 1)
{
    push(s, e, idx);
    if(s == e) return;
    int m = (s + e) / 2;
    force_lazy(s, m, 2*idx);
    force_lazy(m+1, e, 2*idx+1);
}

vector<int> find_union(int N, vector<int> A, vector<int> B, vector<int> C, vector<int> D) {
    // 좌표 압축
    vector<int> xs, ys; xs.reserve(N<<1); ys.reserve(N<<1);
    for(int i = 0; i < N; i++) {
        xs.push_back(A[i]);
        xs.push_back(C[i]);
        ys.push_back(B[i]);
        ys.push_back(D[i]);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    H = ssize(ys)-1;
    W = ssize(xs)-1;
    for(int i = 0; i < N; i++) {
        A[i] = lower_bound(xs.begin(), xs.end(), A[i]) - xs.begin();
        C[i] = lower_bound(xs.begin(), xs.end(), C[i]) - xs.begin();
        B[i] = lower_bound(ys.begin(), ys.end(), B[i]) - ys.begin();
        D[i] = lower_bound(ys.begin(), ys.end(), D[i]) - ys.begin();
    }

    // 전처리
    vector<Line> hs, he, v;
    for(int i = 0; i < N; i++) {
        hs.push_back({A[i], B[i], C[i], D[i], i});
        he.push_back({A[i], B[i], C[i], D[i], i});
        v.push_back({A[i], B[i], A[i], D[i], i});
        v.push_back({C[i], B[i], C[i], D[i], i});
    }
    sort(hs.begin(), hs.end(), [](const Line& a, const Line& b){ return a.x1 < b.x1; });
    sort(he.begin(), he.end(), [](const Line& a, const Line& b){ return a.x2 < b.x2; });
    sort(v.begin(), v.end(), [](const Line& a, const Line& b){ return a.x1 < b.x1; });
    
    // 겹치는 선분 머지
    dsu.init(N);
    init();
    auto push = [&](int y, int v)
    {
        if(ms[y].size()) dsu.merge(*ms[y].begin(), v);
        ms[y].insert(v);
        add(y, 1);
    };
    auto pop = [&](int y, int v)
    {
        add(y, -1);
        ms[y].erase(ms[y].find(v));
    };
    for(int x = 0, p = 0, q = 0, r = 0; x <= W; x++) {
        while(p < hs.size() && hs[p].x1 <= x) {
            push(hs[p].y1, hs[p].id);
            push(hs[p].y2, hs[p].id);
            p++;
        }
        while(r < v.size() && v[r].x1 <= x) {
            merge(v[r].y1, v[r].y2, v[r].id);
            r++;
        }
        while(q < he.size() && he[q].x2 <= x) {
            pop(he[q].y1, he[q].id);
            pop(he[q].y2, he[q].id);
            q++;
        }
    }
    force_lazy();

    // 선분이 겹치지 않는 직사각형 합치기
    Fenwick f(H+5);
    multiset<pair<int, int>> s;
    for(Line& l : hs) l.id = dsu.find(l.id);
    for(Line& l : he) l.id = dsu.find(l.id);
    for(Line& l : v) l.id = dsu.find(l.id);
    for(int x = 0, p = 0, q = 0, r = 0; x <= W; x++) {
        while(p < hs.size() && hs[p].x1 <= x) {
            int y1 = hs[p].y1;
            int y2 = hs[p].y2;
            s.insert(pair(y1, hs[p].id));
            f.upd(y1+1, 1);
            f.upd(y2+1, -1);
            p++;
        }
        while(r < v.size() && v[r].x1 <= x) {
            int id = dsu.find(v[r].id);
            if(f.qry(v[r].y1)>0) {
                dsu.merge((--s.lower_bound(pair(v[r].y1, id)))->second, id);
            }
            r++;
        }
        while(q < he.size() && he[q].x2 <= x) {
            int y1 = he[q].y1;
            int y2 = he[q].y2;
            s.erase(s.find(pair(y1, he[q].id)));
            f.upd(y1+1, -1);
            f.upd(y2+1, 1);
            q++;
        }
    }

    // 출력 포맷 맞추기
    vector<int> ans(N);
    vector<int> unite(N);
    for(int i = 0; i < N; i++) unite[i] = dsu.find(i);
    sort(unite.begin(), unite.end());
    unite.erase(unique(unite.begin(), unite.end()), unite.end());
    for(int i = 0; i < N; i++) ans[i] = lower_bound(unite.begin(), unite.end(), dsu.find(i)) - unite.begin();
    return ans;
}