#include <bits/stdc++.h>

using namespace std;

const int SZ = 1<<20;
const int MAXM = 500005;
const int MAXSEG = 13597152;

int M, last, L[MAXSEG], R[MAXSEG], D[MAXSEG], root[MAXM], len;

void build(int node, int s = 0, int e = SZ-1)
{
    if(s == e) {
        return;
    }

    int m = (s + e) >> 1;
    build(L[node] = last++, s, m);
    build(R[node] = last++, m+1, e);
}

void update(int prv, int node, int pos, int delta, int s = 0, int e = SZ-1)
{
    if(s == e) {
        D[node] = D[prv] + delta;
        return;
    }

    int m = (s + e) >> 1;
    if(pos <= m) {
        R[node] = R[prv];
        update(L[prv], L[node] = last++, pos, delta, s, m);
    } else {
        L[node] = L[prv];
        update(R[prv], R[node] = last++, pos, delta, m+1, e);
    }
    D[node] = D[L[node]] + D[R[node]];
}

int xorquery(int l, int r, int key)
{
    int ret = 0;
    int digit = 19;
    for(int digit = 19; digit >= 0; digit--) {
        if((key&(1<<digit) && D[L[r]] - D[L[l]] > 0) || D[R[r]] - D[R[l]] == 0) {
            l = L[l];
            r = L[r];
        } else {
            l = R[l];
            r = R[r];
            ret |= (1<<digit);
        }
    }
    return ret;
}

int query(int node, int l, int r, int s = 0, int e = SZ-1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return D[node];
    int m = (s + e) >> 1;
    return query(L[node], l, r, s, m) + query(R[node], l, r, m+1, e);
}

int kth(int l, int r, int k)
{
    int ret = 0;
    for(int digit = 19; digit >= 0; digit--) {
        if(k <= D[L[r]] - D[L[l]]) {
            l = L[l];
            r = L[r];
        } else {
            k -= D[L[r]] - D[L[l]];
            ret |= (1<<digit);
            l = R[l];
            r = R[r];
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    build(root[0] = last++);
    cin >> M;
    for(int i = 1; i <= M; i++) {
        int t; cin >> t;
        if(t == 1) {
            int x;
            cin >> x;
            len++;
            update(root[len-1], root[len] = last++, x, 1);
        } else if(t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            int result = xorquery(root[l-1], root[r], x);
            cout << result << "\n";
        } else if(t == 3) {
            int k;
            cin >> k;
            len -= k;
        } else if(t == 4) {
            int l, r, x;
            cin >> l >> r >> x;
            int result = query(root[r], 0, x) - query(root[l-1], 0, x);
            cout << result << "\n";
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            int result = kth(root[l-1], root[r], k);
            cout << result << "\n";
        }
    }
}