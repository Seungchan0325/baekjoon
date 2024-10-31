#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

struct Fenwick {
    int N;
    vector<ll> tree;
    Fenwick(int N) : N(N), tree(N+1) {};
    void upd(int x, ll v) {
        while(x <= N) {
            tree[x] += v;
            x += x & -x;
        }
    }
    ll qry(int x) {
        ll ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

int N, Q, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    cin >> Q;
    Fenwick pls(N), pcnt(N), mls(N), mcnt(N);
    while(Q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r;
            cin >> l >> r;
            pls.upd(l, -l+1);
            pcnt.upd(l, 1);
            mls.upd(r+1, -(r+1)+1 + r - l + 1);
            mcnt.upd(r+1, 1);
        } else {
            ll x;
            cin >> x;
            ll ans = A[x] + x * pcnt.qry(x) + pls.qry(x) - (x * mcnt.qry(x) + mls.qry(x));
            cout << ans << "\n";
        }
    }
}