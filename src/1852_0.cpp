#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100001;
const ll INF = 1e18;

ll n, arr[MAXN][3], min_cache[MAXN][1<<3], max_cache[MAXN][1<<3];

void build_cands(ll idx, ll i, ll left, ll state, ll sum, vector<pair<ll, ll>>& cands) {
    if(i >= 3) {
        if(i == 3) cands.push_back({state, sum});
        return;
    }

    if(left & (1<<i)) build_cands(idx, i+1, left, state, sum, cands);
    else {
        if(!(left & (1<<(i+1))))
            build_cands(idx, i+2, left, state, sum + abs(arr[idx][i] - arr[idx][i+1]), cands);
        build_cands(idx, i+1, left, state | (1<<i), sum + abs(arr[idx][i] - arr[idx+1][i]), cands);
    }
}

pair<ll, ll> dp(ll idx, ll left) {
    if(idx == n) return left ? make_pair(INF, -INF) : make_pair(0LL, 0LL);

    ll& min_ret = min_cache[idx][left];
    ll& max_ret = max_cache[idx][left];
    if(max_ret != -1) return {min_ret, max_ret};

    min_ret = INF;
    max_ret = -INF;

    vector<pair<ll, ll>> cands;
    build_cands(idx, 0, left, 0, 0, cands);
    for(auto [state, sum] : cands) {
        auto [min_, max_] = dp(idx+1, state);
        min_ret = min(min_ + sum, min_ret);
        max_ret = max(max_ + sum, max_ret);
    }

    return {min_ret, max_ret};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(ll i = 0; i < n; i++)
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];

    memset(min_cache, -1, sizeof(min_cache));
    memset(max_cache, -1, sizeof(max_cache));
    auto [min_, max_] = dp(0, 0);
    cout << max_ << "\n";
    cout << min_ << "\n";
}