#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

struct T {
    int left, right;
    int lmx, rmx;
    int mx0, mx1;
    int len;
};

int N, Q;
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.len = a.len + b.len;
    ret.left = a.left;
    ret.right = b.right;
    ret.lmx = a.lmx;
    ret.rmx = b.rmx;
    ret.mx0 = max(a.mx0, b.mx0);
    ret.mx1 = max(a.mx1, b.mx1);
    if(a.right == b.left) {
        if(a.lmx == a.len) ret.lmx += b.lmx;
        if(b.rmx == b.len) ret.rmx += a.rmx;
        if(a.right == 0) ret.mx0 = max(ret.mx0, a.rmx + b.lmx);
        else ret.mx1 = max(ret.mx1, a.rmx + b.lmx);
    }
    if(ret.left) ret.mx1 = max(ret.mx1, ret.lmx);
    else ret.mx0 = max(ret.mx0, ret.lmx);
    if(ret.right) ret.mx1 = max(ret.mx1, ret.rmx);
    else ret.mx0 = max(ret.mx0, ret.rmx);
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
    
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        int a;
        if(c=='0') a = 0;
        else a = 1;
        T v{};
        v.left = v.right = a;
        v.len = 1;
        v.lmx = v.rmx = 1;
        if(a) v.mx1 = 1;
        else v.mx0 = 1;
        update(i, v);
    }
    while(Q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int p, t;
            cin >> p >> t;
            T v{};
            v.left = v.right = t;
            v.len = 1;
            v.lmx = v.rmx = 1;
            if(t) v.mx1 = 1;
            else v.mx0 = 1;
            update(p, v);
        } else {
            int l, r, x, y;
            cin >> l >> r >> x >> y;

            auto q = query(l, r);
            if(q.mx0 < x || q.mx1 < y || (x == 0 && y == 0)) {
                cout << "-1\n";
                continue;
            }

            int lo = l;
            int hi = r+1;
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                auto q = query(mid, r);
                if(q.mx0 >= x && q.mx1 >= y) lo = mid;
                else hi = mid;
            }

            int s = lo;

            lo = s-1;
            hi = r;
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                auto q = query(s, mid);
                if(q.mx0 >= x && q.mx1 >= y) hi = mid;
                else lo = mid;
            }

            int e = hi;

            cout << s << " " << e << "\n";
        }
    }
}