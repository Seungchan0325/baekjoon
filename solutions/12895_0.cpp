#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXT = 35;

int N, T, Q, lazy[4*MAXN];

using nd = bitset<MAXT>;

nd tree[4*MAXN];

nd merge(nd a, nd b)
{
    return a | b;
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx] = 1;
        return;
    }

    int m = (s + e) >> 1;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);

    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] = (1LL << (lazy[idx] - 1));

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
        lazy[idx] = v;

        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

nd query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return 0;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) >> 1;
    return query(l, r, s, m, 2*idx) | query(l, r, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> T >> Q;

    init();
    
    while(Q--) {
        char op; cin >> op;
        if(op == 'C') {
            int x, y, z;
            cin >> x >> y >> z;
            if(x > y) swap(x, y);
            update(x, y, z);
        } else {
            int x, y;
            cin >> x >> y;
            if(x > y) swap(x, y);
            int result = query(x, y).count();
            cout << result << "\n";
        }
    }
}