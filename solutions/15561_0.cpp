#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

struct T {
    ll lmx, rmx, mx, sum;
};

ll N, Q, U, V;
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.lmx = max(a.lmx, a.sum + b.lmx);
    ret.rmx = max(b.rmx, b.sum + a.rmx);
    ret.sum = a.sum + b.sum;
    ret.mx = max({a.mx, b.mx, a.rmx + b.lmx});
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
    if(m+1 <= l) return query(l, r, m+1, e, 2*idx+1);
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q >> U >> V;
    for(int i = 1; i <= N; i++) {
        ll k; cin >> k;
        T t;
        t.lmx = t.rmx = t.mx = U * k + V;
        t.sum = U * k + V;
        update(i, t);
    }

    while(Q--) {
        int op, A, B;
        cin >> op >> A >> B;
        if(op == 0) {
            ll ans = query(A, B).mx;
            cout << ans - V << "\n";
        } else {
            T t;
            t.lmx = t.rmx = t.mx = U * B + V;
            t.sum = U * B + V;
            update(A, t);
        }
    }
}