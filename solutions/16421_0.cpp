#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXK = 101010;

struct Node {
    ll on;
    ll off;
};

ll K, A[MAXK], B[MAXK], C[MAXK], D[MAXK];
Node tree[8*MAXK];
int lazy[8*MAXK];

Node merge(Node a, Node b)
{
    return {a.on + b.on, a.off + b.off};
}

void prop(int s, int e, int idx)
{
    if(lazy[idx]) {
        swap(tree[idx].on, tree[idx].off);
        if(s != e) {
            lazy[2*idx] ^= 1;
            lazy[2*idx+1] ^= 1;
        }
        lazy[idx] = 0;
    }
}

void init(vector<ll>& rs, int s, int e, int idx)
{
    if(s == e) {
        tree[idx].off = rs[s+1] - rs[s];
        return;
    }
    int m = (s + e) /2;
    init(rs, s, m, 2*idx);
    init(rs, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void upd(int l, int r, int s, int e, int idx)
{
    prop(s, e, idx);
    if(e < l || r < s) return ;

    if(l <= s && e <= r) {
        lazy[idx] ^=1;
        prop(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    upd(l, r, s, m, 2*idx);
    upd(l, r, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> K;
    for(int i = 1; i <= K; i++) cin >> A[i] >> C[i] >> B[i] >> D[i];

    vector<ll> rs;
    for(int i = 1; i <= K; i++) {
        rs.push_back(A[i]);
        rs.push_back(B[i]);
    }
    sort(rs.begin(), rs.end());
    rs.erase(unique(rs.begin(), rs.end()), rs.end());

    vector<tuple<ll, ll, ll>> u;
    for(int i = 1; i <= K; i++) {
        int x = lower_bound(rs.begin(), rs.end(), A[i]) - rs.begin();
        int y = lower_bound(rs.begin(), rs.end(), B[i]) - rs.begin() - 1;
        u.emplace_back(C[i], x, y);
        u.emplace_back(D[i], x, y);
    }

    init(rs, 0, ssize(rs)-2, 1);
    sort(u.begin(), u.end());
    ll ans = 0;
    ll pt = 1;
    ll pon = 0;
    for(auto [t, x, y] : u) {
        ans += (t - pt) * pon;
        upd(x, y, 0, ssize(rs)-2, 1);
        pon = tree[1].on;
        pt = t;
    }

    cout << ans << "\n";
}