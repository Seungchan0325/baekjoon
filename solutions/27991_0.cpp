#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1e6 + 5;

ll N, M, x[MAXN];

vector<ll> tree[4*MAXN];

void build(ll s = 0, ll e = N-1, ll idx = 1)
{
    if(s == e) {
        tree[idx].push_back(x[s]);
        return;
    }

    ll m = (s + e) >> 1;
    build(s, m, 2*idx); build(m+1, e, 2*idx+1);

    tree[idx].resize(tree[2*idx].size() + tree[2*idx+1].size());
    merge(tree[2*idx].begin(), tree[2*idx].end(),
          tree[2*idx+1].begin(), tree[2*idx+1].end(),
          tree[idx].begin());
}

int query(ll l, ll r, ll k, ll s = 0, ll e = N-1, ll idx = 1)
{
    if(e < l || r < s) return 0;

    if(l <= s && e <= r) {
        return upper_bound(tree[idx].begin(), tree[idx].end(), k) - tree[idx].begin();
    }

    ll m = (s + e) >> 1;
    return query(l, r, k, s, m, 2*idx) + query(l, r, k, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(ll i = 0; i < N; i++) cin >> x[i];

    build();

    pair<ll, ll> mx = {0, 0};
    for(ll i = 0; i < N; i++) {
        ll k = x[i];
        ll q = M / k;
        int cnt = query(0, q-1, k);
        if(q < N && x[q] <= M % k) {
            cnt++;
        }
        mx = max(mx, {cnt, -k});
    }

    cout << -mx.second;
}