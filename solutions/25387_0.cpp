#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const llint MAXN = 300005;
const llint MAXQ = 300005;
const llint MOD = 998244353;

llint ans, N, Q, L[MAXQ], R[MAXQ], C[MAXQ], psum[MAXN], tree[4*MAXN], lazy[4*MAXN];

llint md(llint n)
{
    return (n + MOD) % MOD;
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] = md(lazy[idx] * md(psum[e] - psum[s-1]));
        if(s != e) {
            lazy[2*idx] = lazy[idx];
            lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int delta, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy[idx] = delta;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, delta, s, m, 2*idx);
    update(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = md(tree[2*idx] + tree[2*idx+1]);
}

llint query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) >> 1;
    return md(query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        llint t = i * (N - i + 1) % MOD;
        psum[i] = md(t + psum[i-1]);
    }
    for(int i = 1; i <= Q; i++) {
        cin >> L[i] >> R[i] >> C[i];
    }

    update(1, N, Q+1);

    for(int i = Q; i >= 1; i--) {
        llint t = query(L[i], R[i]);
        t -= md(i * md(psum[R[i]] - psum[L[i]-1] + MOD));
        t = md(t + MOD);
        llint add = md(md(i * t) * C[i]);
        ans = md(ans + add);
        update(L[i], R[i], i);
    }
    cout << ans;
}