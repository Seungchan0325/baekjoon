#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

struct Node {
    ll l, r;
    int v;
    Node() : l(-1), r(-1), v(0) {}
};

int n, m, nd_last = 1;
ll s[MAXN];
Node nd[5'000'000];

void update(int node, ll start, ll end, ll pos, int delta)
{
    if(start == end) {
        nd[node].v += delta;
        return;
    }

    ll mid = (start + end) / 2;
    if(pos <= mid) {
        if(nd[node].l == -1) nd[node].l = nd_last++;
        update(nd[node].l, start, mid, pos, delta);
    } else {
        if(nd[node].r == -1) nd[node].r = nd_last++;
        update(nd[node].r, mid+1, end, pos, delta);
    }

    nd[node].v = 0;
    if(nd[node].l != -1) nd[node].v += nd[nd[node].l].v;
    if(nd[node].r != -1) nd[node].v += nd[nd[node].r].v;
}

int query(int node, ll start, ll end, ll left, ll right)
{
    if(node == -1 || end < left || right < start) return 0;
    if(left <= start && end <= right) return nd[node].v;
    ll mid = (start + end) / 2;
    return query(nd[node].l, start, mid, left, right) + query(nd[node].r, mid+1, end, left, right);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        update(0, 0, 1e18, s[i], 1);
    }

    for(int iter = 0; iter < m; iter++) {
        int type;
        cin >> type;

        if(type == 1) {
            int i, x;
            cin >> i >> x;
            update(0, 0, 1e18, s[i], -1);
            update(0, 0, 1e18, s[i] += x, 1);
        } else if(type == 2) {
            int i, y;
            cin >> i >> y;
            update(0, 0, 1e18, s[i], -1);
            update(0, 0, 1e18, s[i] -= y, 1);
        } else if(type == 3) {
            ll l, r;
            cin >> l >> r;
            int result = query(0, 0, 1e18, l, r);
            cout << result << "\n";
        } else if(type == 4) {
            int t;
            cin >> t;

            ll lo = 0;
            ll hi = 1e18;
            while(lo + 1 < hi) {
                ll mid = (lo + hi) / 2;
                int cnt = query(0, 0, 1e18, mid, 1e18);
                if(t <= cnt) lo = mid;
                else hi = mid;
            }

            cout << lo << "\n";
        } else {
            assert(0);
        }
    }
}