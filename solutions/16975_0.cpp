#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

ll n, m, tree[4*MAXN], lazy[4*MAXN];

void propagate(ll start, ll end, ll index) {
    if(lazy[index]) {
        tree[index] += (end - start + 1) * lazy[index];
        if(start != end) {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(ll start, ll end, ll index, ll left, ll right, ll delta) {
    propagate(start, end, index);
    if(end < left || right < start) return;

    if(left <= start && end <= right) {
        tree[index] += (end - start + 1) * delta;
        if(start != end) {
            lazy[2*index] += delta;
            lazy[2*index+1] += delta;
        }
        return;
    }

    ll mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, delta);
    update(mid+1, end, 2*index+1, left, right, delta);
    tree[index] = tree[2*index] + tree[2*index+1];
}

ll query(ll start, ll end, ll index, ll left, ll right) {
    propagate(start, end, index);
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    ll mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) + query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(ll i = 0; i < n; i++) {
        ll Ai; cin >> Ai;
        update(0, n-1, 1, i, i, Ai);
    }
    cin >> m;

    for(ll q = 0; q < m; q++) {
        ll type; cin >> type;
        if(type == 1) {
            ll i, j, k; cin >> i >> j >> k;
            update(0, n-1, 1, i-1, j-1, k);
        } else {
            ll x; cin >> x;
            ll result = query(0, n-1, 1, x-1, x-1);
            cout << result << "\n";
        }
    }
}