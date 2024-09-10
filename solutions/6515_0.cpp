#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct T {
    int lv, rv, lcnt, rcnt, mx;
};

int N, Q, A[MAXN];
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.lv = a.lv;
    ret.rv = b.rv;
    ret.lcnt = a.lcnt;
    ret.rcnt = b.rcnt;
    ret.mx = max(a.mx, b.mx);
    if(a.rv == b.lv) {
        ret.mx = max(a.rcnt + b.lcnt, ret.mx);
    }

    if(a.lv == b.lv) {
        ret.lcnt = a.lcnt + b.lcnt;
    }

    if(b.rv == a.rv) {
        ret.rcnt = b.rcnt + a.rcnt;
    }

    if(a.lv == b.rv) {
        ret.lcnt = ret.rcnt = a.lcnt + b.rcnt;
        ret.mx = max(a.lcnt + b.rcnt, ret.mx);
    }

    ret.mx = max({ret.lcnt, ret.rcnt, ret.mx});

    return ret;
}

void update(int x, T v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }    

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    if(r <= m) return query(l, r, s, m, 2*idx);
    else if(m < l) return query(l, r, m+1, e, 2*idx+1);
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        cin >> N;
        if(N == 0) break;
        cin >> Q;
        for(int i = 1; i <= N; i++) {
            cin >> A[i];
            T v;
            v.lv = v.rv = A[i];
            v.lcnt = v.rcnt = 1;
            v.mx = 1;
            update(i, v);
        }

        while(Q--) {
            int s, e;
            cin >> s >> e;
            T t = query(s, e);
            cout << t.mx << "\n";
        }
    }
}