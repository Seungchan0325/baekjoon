#include <bits/stdc++.h>

using namespace std;

using llint = long long;

const int MAXN = 1000005;
const int MAXQ = 1000005;
const llint MOD = 1e9 + 7;

int N, Q, L[MAXQ], tree[4*MAXN], lazy[4*MAXN];
llint fibo[MAXN];

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] = lazy[idx];
        if(s != e) {
            lazy[2*idx] = lazy[idx];
            lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        tree[idx] = v;
        if(s != e) {
            lazy[2*idx] = v;
            lazy[2*idx+1] = v;
        }
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int pos)
{
    int s = 1, e = N, idx = 1;
    while(s != e) {
        propagate(s, e, idx);
        int m = (s + e) >> 1;
        if(pos <= m) e = m, idx = 2*idx;
        else s = m+1, idx = 2*idx+1;
    }
    propagate(s, e, idx);
    return tree[idx];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    fibo[0] = fibo[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        fibo[i] = (fibo[i-1] + fibo[i-2]) % MOD;
    }

    cin >> N;
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        int l, r;
        cin >> l >> r;
        L[i] = l;
        update(l, r, i);
    }

    for(int i = 1; i <= N; i++) {
        int idx = query(i);
        if(idx == 0) cout << "0 ";
        else cout << fibo[i - L[idx] + 1] << " ";
    }
}