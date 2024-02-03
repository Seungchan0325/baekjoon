#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

ll n, q, tree[4*MAXN], a_tree[4*MAXN];

void propagate(ll start, ll end, ll index)
{
    if(a_tree[index]) {
        if(start != end) {
            a_tree[2*index] += a_tree[index];
            a_tree[2*index+1] += a_tree[index];
            a_tree[index] = 0;
        }
    }
}

void update_range(ll left, ll right, ll delta, ll start = 1, ll end = n, ll index = 1)
{
    propagate(start, end, index);
    if(end < left || right < start) return;
    
    if(left <= start && end <= right) {
        a_tree[index] += delta;
        propagate(start, end, index);
        return;
    }

    ll mid = (start + end) / 2;
    update_range(left, right, delta, start, mid, 2*index);
    update_range(left, right, delta, mid+1, end, 2*index+1);
}

ll point_query(ll pos, ll start = 1, ll end = n, ll index = 1)
{
    propagate(start, end, index);
    if(start == end) return a_tree[index];
    ll mid = (start + end) / 2;
    if(pos <= mid) return point_query(pos, start, mid, 2*index);
    else return point_query(pos, mid+1, end, 2*index+1);
}

void update(ll pos, ll v, ll start = 1, ll end = n, ll index = 1)
{
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] = v;
        // tree[index] = abs(tree[index] += v);
        // tree[index] += v;
        return;
    }

    ll mid = (start + end) / 2;
    update(pos, v, start, mid, 2*index);
    update(pos, v, mid+1, end, 2*index+1);
    tree[index] = gcd(tree[2*index], tree[2*index+1]);
}

ll query(ll left, ll right, ll start = 1, ll end = n, ll index = 1)
{
    if(left <= start && end <= right) return tree[index];

    ll mid = (start + end) / 2;
    if(right <= mid) return query(left, right, start, mid, 2*index);
    if(mid < left) return query(left, right, mid+1, end, 2*index+1);
    return gcd(query(left, right, start, mid, 2*index), query(left, right, mid+1, end, 2*index+1));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        update_range(i, i, x);
    }

    ll prev = point_query(1, 1, n, 1);
    for(ll i = 2; i <= n; i++) {
        ll cur = point_query(i, 1, n, 1);
        update(i, abs(prev - cur));
        prev = cur;
    }

    cin >> q;
    while(q--) {
        ll t, a, b;
        cin >> t >> a >> b;
        if(t == 0) {
            if(a == b) {
                cout << abs(point_query(a)) << "\n";
            } else {
                ll first = point_query(a);
                ll other = query(a + 1, b);
                cout << abs(gcd(first, other)) << "\n";
            }
        } else {
            update_range(a, b, t);
            ll delta = point_query(a) - point_query(a - 1);
            update(a, abs(delta));
            delta = point_query(b + 1) - point_query(b);
            update(b + 1, abs(delta));
        }
    }
}