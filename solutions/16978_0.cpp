#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

ll n, m, tree[4*MAXN];

void update(ll start, ll end, ll index, ll pos, ll value) {
    if(end < pos || pos < start) return;
    
    if(start == end) {
        tree[index] = value;
        return;
    }

    ll mid = (start + end) / 2;
    update(start, mid, 2*index, pos, value);
    update(mid+1, end, 2*index+1, pos, value);
    tree[index] = tree[2*index] + tree[2*index+1];
}

ll query(ll start, ll end, ll index, ll left, ll right) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    ll mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) + query(mid+1, end, 2*index+1, left, right);
}

int main() {
    cin >> n;
    for(ll i = 0; i < n; i++) {
        ll Ai; cin >> Ai;
        update(0, n-1, 1, i, Ai);
    }
    cin >> m;
    vector<tuple<ll, ll>> updates;
    vector<tuple<ll, ll, ll, ll>> queries;
    for(ll i = 0; i < m; i++) {
        ll type; cin >> type;
        if(type == 1) {
            ll idx, v; cin >> idx >> v;
            updates.emplace_back(idx-1, v);
        }
        else {
            ll k, s, e; cin >> k >> s >> e;
            queries.emplace_back(k-1, s-1, e-1, i);
        }
    }
    sort(queries.begin(), queries.end());

    vector<pair<ll, ll>> ans;
    ll last = -1;
    for(auto [k, i, j, idx] : queries) {
        while(last < k) {
            auto [idx, v] = updates[++last];
            update(0, n-1, 1, idx, v);
        }

        ll result = query(0, n-1, 1, i, j);
        ans.emplace_back(idx, result);
    }
    sort(ans.begin(), ans.end());

    for(auto [idx, result] : ans) cout << result << "\n";
}