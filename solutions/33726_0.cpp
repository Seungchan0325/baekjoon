#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MAXN = 606060;
const i64 inf = 1e18;

struct MinSegTree {
    i64 n; vector<i64> tree;
    MinSegTree(i64 _n) : n(_n), tree(2*n) {}
    void update(i64 x, i64 v)
    {
        x += n;
        tree[x] = v;
        while(x>>=1) tree[x] = min(tree[x<<1], tree[x<<1|1]);
    }
    i64 query(i64 l, i64 r)
    {
        i64 ret = inf;
        for(l+=n, r+=n; l <= r; l>>=1,r>>=1) {
            if(l&1) ret = min(ret, tree[l++]);
            if(~r&1) ret = min(ret, tree[r--]);
        }
        return ret;
    }
};

struct MaxSegTree {
    i64 n; vector<i64> tree;
    MaxSegTree(i64 _n) : n(_n), tree(2*n) {}
    void update(i64 x, i64 v)
    {
        x += n;
        tree[x] = v;
        while(x>>=1) tree[x] = max(tree[x<<1], tree[x<<1|1]);
    }
    i64 query(i64 l, i64 r)
    {
        i64 ret = -inf;
        for(l+=n, r+=n; l <= r; l>>=1,r>>=1) {
            if(l&1) ret = max(ret, tree[l++]);
            if(~r&1) ret = max(ret, tree[r--]);
        }
        return ret;
    }
};

i64 n, m, p, A[MAXN], B[MAXN], C[MAXN], q, L[MAXN], R[MAXN], X[MAXN], side[MAXN];
vector<i64> companies[4*MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m >> p;
    for(i64 i = 1; i <= m; i++) cin >> A[i] >> B[i] >> C[i];
    cin >> q;
    for(i64 i = 1; i <= q; i++) cin >> L[i] >> R[i] >> X[i];

    vector<i64> vs(C+1, C+m+1);
    for(i64 i = 1; i <= q; i++) {
        vs.push_back(L[i]);
        vs.push_back(R[i]);
        vs.push_back(L[i] - X[i]);
        vs.push_back(R[i] + X[i]);
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    for(i64 i = 1; i <= m; i++) {
        i64 j = lower_bound(vs.begin(), vs.end(), C[i]) - vs.begin();
        companies[j].push_back(B[i]);
    }

    MinSegTree frt(n+1);
    MaxSegTree lst(n+1);
    MinSegTree lef(vs.size()+1), rig(vs.size()+1);
    for(i64 i = 1; i <= n; i++) lst.update(i, inf);
    for(i64 i = 1; i <= n; i++) frt.update(i, -inf);

    for(i64 i = 0; i < vs.size(); i++) {
        for(auto j : companies[i]) frt.update(j, vs[i]);
        rig.update(i, vs[i] - frt.query(2, n));
    }

    for(i64 i = (i64)vs.size()-1; i >= 0; i--) {
        for(auto j : companies[i]) lst.update(j, vs[i]);
        lef.update(i, lst.query(2, n) - vs[i]);
    }

    for(i64 i = 1; i <= q; i++) {
        i64 ll = L[i] - X[i];
        i64 lr = L[i];
        ll = lower_bound(vs.begin(), vs.end(), ll) - vs.begin();
        lr = lower_bound(vs.begin(), vs.end(), lr) - vs.begin();

        i64 rl = R[i];
        i64 rr = R[i] + X[i];
        rl = lower_bound(vs.begin(), vs.end(), rl) - vs.begin();
        rr = lower_bound(vs.begin(), vs.end(), rr) - vs.begin();

        i64 mxlen = R[i] - L[i] + X[i];

        if(lef.query(ll, lr) <= mxlen || rig.query(rl, rr) <= mxlen) cout << "Yes\n";
        else cout << "No\n";
    }
}