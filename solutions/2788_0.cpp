#include <bits/stdc++.h>

using namespace std;

using lint = long long;

const lint INF = 1e18;

lint N, M;

struct line {
    lint A, B;
    lint eval(lint x) { return A * x + B; }
    lint cross_after(line &x, lint T)
    {
        if(x.A == A) return INF;
        lint up = x.B - B;
        lint dn = A - x.A;
        if(dn < 0) {
            dn = -dn;
            up = -up;
        }
        lint incep = (up <= 0 ? -((-up) / dn) : (up + dn - 1) / dn);
        if(incep > T) return incep;
        return INF;
    }
};

struct kst {
    int n;
    lint T;
    vector<line> tree;
    vector<lint> melt;

    void pull(int idx) {
        lint l = tree[2*idx].eval(T);
        lint r = tree[2*idx+1].eval(T);
        tree[idx] = (l > r || (l == r && tree[2*idx].A > tree[2*idx+1].A)) ? tree[2*idx] : tree[2*idx+1];
        melt[idx] = min({melt[2*idx], melt[2*idx+1], tree[2*idx].cross_after(tree[2*idx+1], T)});
    }

    void init(int s, int e, int idx)
    {
        if(s == e) {
            tree[idx] = {0, -INF};
            melt[idx] = INF;
            return;
        };
        int m = (s + e) / 2;
        init(s, m, 2*idx);
        init(m+1, e, 2*idx+1);
        pull(idx);
    }
 
    kst(int n) : n(n), T(0), tree(4*n), melt(4*n)
    {
        init(1, n, 1);
    }

    void update(int x, line v, int s, int e, int idx)
    {
        if(e < x || x < s) return;
        if(s == e) {
            tree[idx] = v;
            return;
        }
        int m = (s + e) / 2;
        update(x, v, s, m, 2*idx);
        update(x, v, m+1, e, 2*idx+1);
        pull(idx);
    }

    void update(int x, line v)
    {
        update(x, v, 1, n, 1);
    }

    lint query(int l, int r, int s, int e, int idx)
    {
        if(e < l || r < s) return -INF;
        if(l <= s && e <= r) return tree[idx].eval(T);
        int m = (s + e) / 2;
        return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }

    lint query(int l, int r)
    {
        return query(l, r, 1, n, 1);
    }

    void heaten(int s, int e, int idx)
    {
        if(melt[idx] > T) return;

        int m = (s + e) / 2;
        heaten(s, m, 2*idx);
        heaten(m+1, e, 2*idx+1);
        pull(idx);
    }

    void heaten(lint _T) {
        assert(T <= _T);
        T = _T;
        heaten(1, n, 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    kst tree(N);
    while(M--) {
        int op;
        cin >> op;
        if(op == 1) {
            lint T, K, Z, S;
            cin >> T >> K >> Z >> S;
            tree.update(K, {Z, S - Z * T});
        } else {
            lint T, A, B;
            cin >> T >> A >> B;
            if(A > B) swap(A, B);
            tree.heaten(T);
            lint result = tree.query(A, B);
            if(result <= -INF) cout << "nema\n";
            else cout << result << "\n";
        }
    }
}