#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void update(ll tree[], ll start, ll end, ll index, ll pos, ll delta)
{
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] += delta;
        return;
    }

    ll mid = (start + end) / 2;
    update(tree, start, mid, 2*index, pos, delta);
    update(tree, mid+1, end, 2*index+1, pos, delta);
    tree[index] = tree[2*index] + tree[2*index+1];
}

ll query(ll tree[], ll start, ll end, ll index, ll left, ll right)
{
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return tree[index];

    ll mid = (start + end) / 2;
    return query(tree, start, mid, 2*index, left, right) + query(tree, mid+1, end, 2*index+1, left, right);
}

const ll MAXN = 300005;

ll n, q;
ll seg[2][4*MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> q;
    for(ll i = 1; i <= n; i++) {
        ll c;
        cin >> c;
        update(seg[i & 1], 1, n, 1, i, c);
    }

    for(ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if(type == 1) {
            ll l, r;
            cin >> l >> r;
            ll result = query(seg[0], 1, n, 1, l, r) - query(seg[1], 1, n, 1, l, r);
            cout << abs(result) << "\n";
        } else if(type == 2) {
            ll l, x;
            cin >> l >> x;
            update(seg[l & 1], 1, n, 1, l, x);
        }
    }
}