#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll pow(ll a, ll b) {
    ll ret = 1;
    for(int i = 1; i <= b; i++) {
        ret *= a;
    }
    return ret;
}

ll get_depth(ll k, ll h, ll q) {
    if(h == 0) return -1;
    ll left = 1;
    ll right = pow((k+1), h)-1;
    if(!(left <= q && q <= right)) {
        return -1;
    }

    ll bino = pow(k+1, h-1) - 1;
    for(ll i = 1; i <= k + 1; i++) {
        ll res = get_depth(k, h-1, q);
        if(0 < res) return res + 1;

        q -= bino + 1;
        if(q == 0) return 1;
    }

    assert(0);
}

ll lca(ll k, ll h, ll q1, ll q2) {
    if(h == 0) return -1;
    ll left = 1;
    ll right = pow((k+1), h)-1;
    if(!(left <= q1 && q2 <= right)) {
        return -1;
    }

    ll bino = pow(k+1, h-1) - 1;
    for(ll i = 1; i <= k + 1; i++) {
        ll res = lca(k, h-1, q1, q2);
        if(0 < res) {
            return res;
        }
        if(q1 - bino - 1 <= 0) break;
        q1 -= bino + 1;
        q2 -= bino + 1;
    }

    ll d1 = get_depth(k, h, q1);
    ll d2 = get_depth(k, h, q2);

    if(q1 == q2) return 0;

    return d1 + d2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll k, h, q;
    cin >> k >> h >> q;
    // (k+1)^h-1
    while(q--) {
        ll u, v; cin >> u >> v;
        if(v < u) swap(u, v);
        ll result = lca(k, h, u, v);
        cout << result << "\n";
    }
}