#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1<<20;

using ll = long long;

const ll inf = 1e15;

struct Node {
   ll m, p, pm, mp, mpm;
};

int N, Q, A[MAXN];

Node merge(const Node& a, const Node& b) {
    ll m = min(a.m, b.m);
    ll p = max(a.p, b.p);
    ll pm = max({a.pm, b.pm, a.p - b.m});
    ll mp = max({a.mp, b.mp, -a.m + b.p});
    ll mpm = max({a.mpm, b.mpm, a.mp - b.m, -a.m + b.pm});
    return {m, p, pm, mp, mpm};
}

Node tree[2*MAXN];

void init()
{
    for(int i = 0; i < 2*MAXN; i++) tree[i] = {inf, -inf, -inf, -inf , -inf};
}

void update(int x, Node v)
{
    tree[x+=MAXN] = v;
    while(x>>=1) tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

Node query(int l, int r)
{
    Node left{inf, -inf, -inf, -inf , -inf}, right{inf, -inf, -inf, -inf , -inf};
    for(l+=MAXN, r+=MAXN; l<=r; l>>=1, r>>=1) {
        if(l&1) left = merge(left, tree[l++]);
        if(~r&1) right = merge(tree[r--], right);
    }
    return merge(left, right);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    init();
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        int x; cin >> x;
        Node v = {x, x, -inf, -inf, -inf};
        update(i, v);
    }
    while(Q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, y;
            cin >> x >> y;
            Node v = {y, y, -inf, -inf, -inf};
            update(x, v);
        } else {
            int l, r;
            cin >> l >> r;
            Node ans = query(l, r);
            cout << ans.mpm << "\n";
        }
    }
}