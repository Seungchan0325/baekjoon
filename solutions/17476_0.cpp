#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const int MAXN = 100005;
const llint INF = 1e18;

struct T {
    llint mn, mx, sum;
};

int N, M, A[MAXN];
T tree[4*MAXN];
llint lazy1[4*MAXN], lazy2[4*MAXN];

T merge(T a, T b)
{
    return {min(a.mn, b.mn), max(a.mx, b.mx), a.sum + b.sum};
}

void build(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].mn = tree[idx].mx = tree[idx].sum = A[s];
        return;
    }

    int m = (s + e) >> 1;
    build(s, m, 2*idx); build(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void propagate(int s, int e, int idx)
{
    if(lazy1[idx]) {
        tree[idx].mn = lazy1[idx];
        tree[idx].mx = lazy1[idx];
        tree[idx].sum = (e - s + 1) * lazy1[idx];
        if(s != e) {
            lazy1[2*idx] = lazy1[idx];
            lazy2[2*idx] = 0;
            lazy1[2*idx+1] = lazy1[idx];
            lazy2[2*idx+1] = 0;
        }
        lazy1[idx] = 0;
    }

    if(lazy2[idx]) {
        tree[idx].mn += lazy2[idx];
        tree[idx].mx += lazy2[idx];
        tree[idx].sum += (e - s + 1) * lazy2[idx];
        if(s != e) {
            lazy2[2*idx] += lazy2[idx];
            lazy2[2*idx+1] += lazy2[idx];
        }
        lazy2[idx] = 0;
    }
}

void update_sqrt(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        llint sq = sqrt(tree[idx].mn);
        if(tree[idx].mx < (sq+1)*(sq+1)) {
            lazy1[idx] = sq;
            propagate(s, e, idx);
            return;
        }

        if(tree[idx].mn + 1 == tree[idx].mx) {
            lazy2[idx] = floor(sqrt(tree[idx].mn)) - tree[idx].mn;
            propagate(s, e, idx);
            return;
        }
    }

    int m = (s + e) >> 1;
    update_sqrt(l, r, s, m, 2*idx);
    update_sqrt(l, r, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update_add(int l, int r, int delta, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy2[idx] += delta;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update_add(l, r, delta, s, m, 2*idx);
    update_add(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return T{INF, -INF, 0};

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) >> 1;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    build();

    cin >> M;
    while(M--) {
        int t;
        cin >> t;

        if(t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            update_add(l, r, x);
        } else if(t == 2) {
            int l, r;
            cin >> l >> r;
            update_sqrt(l, r);
        } else {
            int l, r;
            cin >> l >> r;
            T result = query(l, r);
            cout << result.sum << "\n";
        }
    }
}