#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

struct T {
    int llen, rlen, mxlen, sz;
    bool lable, rable;
};

int lazy[4*MAXN];
int N, M;
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.llen = a.llen;
    ret.rlen = b.rlen;
    ret.sz = a.sz + b.sz;
    ret.mxlen = max(a.mxlen, b.mxlen);
    ret.lable = a.lable;
    ret.rable = b.rable;

    if(a.rable && b.lable) {
        if(a.llen == a.sz) ret.llen = a.sz + b.llen;
        if(b.rlen == b.sz) ret.rlen = b.sz + a.rlen;
        ret.mxlen = max(ret.mxlen, a.rlen + b.llen);
    }

    return ret;
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx] != -1) {
        tree[idx].llen = tree[idx].rlen = tree[idx].mxlen = (e - s + 1) * lazy[idx];
        tree[idx].lable = lazy[idx];
        tree[idx].rable = lazy[idx];
        tree[idx].sz = e - s + 1;

        if(s != e) {
            lazy[2*idx] = lazy[idx];
            lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = -1;
    }
}

void upd(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy[idx] = v;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    upd(l, r, v, s, m, 2*idx);
    upd(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int qry(int len, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(s == e) return s;
    int m = (s + e) / 2;
    propagate(s, m, 2*idx);
    propagate(m+1, e, 2*idx+1);
    if(tree[2*idx].mxlen >= len) return qry(len, s, m, 2*idx);
    if(tree[2*idx].rable && tree[2*idx+1].lable && tree[2*idx].rlen + tree[2*idx+1].llen >= len) {
        return m - tree[2*idx].rlen + 1;
    }
    return qry(len, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(lazy, -1, sizeof(lazy));

    cin >> N >> M;
    upd(1, N, 1);
    int ans = 0;
    while(M--) {
        char op;
        cin >> op;
        if(op == 'A') {
            int p;
            cin >> p;
            if(tree[1].mxlen < p) ans++;
            else {
                int idx = qry(p);
                upd(idx, idx+p-1, 0);
            }
        } else {
            int a, b;
            cin >> a >> b;
            upd(a, b, 1);
        }
    }
    cout << ans;
}