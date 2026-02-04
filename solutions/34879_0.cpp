#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;
const int inf = 1e9;

int R, C, N, M;

namespace SEG1 {
int tree[4*MAXN], lazy[4*MAXN];
bool has_lazy[4*MAXN];

void push(int s, int e, int idx)
{
    if(has_lazy[idx]) {
        tree[idx] = lazy[idx];
        if(s != e) {
            has_lazy[2*idx] = has_lazy[2*idx+1] = true;
            lazy[2*idx] = lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = 0;
        has_lazy[idx] = false;
    }
}

void update(int l, int r, int v, int s=1, int e=R, int idx=1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        has_lazy[idx] = true;
        lazy[idx] = v;
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int first_gt(int l, int r, int x, int s=1, int e=R, int idx=1)
{
    push(s, e, idx);
    if(e < l || r < s) return r+1;
    if(l <= s && e <= r && tree[idx] <= x) return r+1;
    if(s == e) return s;
    int m = (s + e) / 2;
    int lef = first_gt(l, r, x, s, m, 2*idx);
    if(lef <= r) return lef;
    return first_gt(l, r, x, m+1, e, 2*idx+1);
}

int query(int l, int r, int s=1, int e=R, int idx=1)
{
    push(s, e, idx);
    if(e < l || r < s) return -inf;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}
}

namespace SEG2 {
int tree[4*MAXN], lazy[4*MAXN];
void push(int s, int e, int idx)
{
    if(lazy[idx] != 0) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s=1, int e=R, int idx=1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] = v;
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int first_gt(int l, int r, int x, int s=1, int e=R, int idx=1)
{
    push(s, e, idx);
    if(e < l || r < s) return r+1;
    if(l <= s && e <= r && tree[idx] <= x) return r+1;
    if(s == e) return s;
    int m = (s + e) / 2;
    int lef = first_gt(l, r, x, s, m, 2*idx);
    if(lef <= r) return lef;
    return first_gt(l, r, x, m+1, e, 2*idx+1);
}

int query(int l, int r, int s=1, int e=R, int idx=1)
{
    push(s, e, idx);
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R >> C >> N >> M;
    vector<vector<pair<int, int>>> ts(C+1);
    for(int i = 0; i < N; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        ts[y].push_back({x, v});
    }
    vector<vector<pair<int, int>>> bs(C+1), be(C+2);
    for(int i = 0; i < M; i++) {
        int u, l, d, r;
        cin >> u >> l >> d >> r;
        bs[l].push_back({u, d});
        be[r+1].push_back({u, d});
    }

    SEG1::update(1, R, -inf);

    for(int i = 1; i <= C; i++) {
        for(auto [s, e] : bs[i]) {
            SEG2::update(s, e, +1);
            SEG1::update(s, e, -inf);
        }
        for(auto [s, e] : be[i]) {
            SEG2::update(s, e, -1);
            int x = SEG1::query(s-1, s-1);
            int r = SEG2::first_gt(s, R, 0)-1;
            r = SEG1::first_gt(s, r, x)-1;
            SEG1::update(s, r, x);
        }
        sort(ts[i].begin(), ts[i].end());
        if(i == 1) {
            int r = SEG2::first_gt(1, R, 0)-1;
            r = SEG1::first_gt(1, r, 0)-1;
            SEG1::update(1, r, 0);
        }
        for(auto [x, v] : ts[i]) {
            if(SEG2::query(x, x) > 0) continue;
            v += SEG1::query(x, x);
            int r = SEG2::first_gt(x, R, 0)-1;
            r = SEG1::first_gt(x, r, v)-1;
            SEG1::update(x, r, v);
        }
    }

    int ans = SEG1::query(R, R);
    if(ans < 0) cout << "-1\n";
    else cout << ans << "\n";
}