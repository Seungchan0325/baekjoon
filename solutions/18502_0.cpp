#include <bits/stdc++.h>

using namespace std;
namespace r = std::ranges;

using ll = long long;

ll ans;
vector<ll> neg;

void compute(vector<tuple<ll, ll, ll>> v, ll cost)
{
    vector<ll> xs;
    xs.push_back(-1e9);
    xs.push_back(1e9);
    for(auto [l, r, i] : v) {
        xs.push_back(l);
        xs.push_back(r);
        xs.push_back(r+1);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    vector<ll> sum(xs.size()), cnt(xs.size());
    for(auto [l, r, i] : v) {
        l = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        r = upper_bound(xs.begin(), xs.end(), r) - xs.begin();
        sum[l]++;
        sum[r]--;
    }
    for(int i = 1; i < xs.size(); i++) sum[i] += sum[i-1];
    for(int i = 1; i + 1 < xs.size(); i++) {
        if(sum[i] == 1) cnt[i] += xs[i+1] - xs[i];
        cnt[i] += cnt[i-1];
    }
    int n = v.size();
    auto vv = v;
    r::sort(v, [](tuple<ll, ll, ll> a, tuple<ll, ll, ll> b){
        auto [la, ra, ia] = a;
        auto [lb, rb, ib] = b;
        return la < lb;
    });
    ll p = 0;
    for(auto [l, r, i] : v) {
        ans += cost * max(min(r - p, r - l + 1), 0LL);
        p = max(p, r);
        l = lower_bound(xs.begin(), xs.end(), l) - xs.begin() - 1;
        r = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        neg[i] += cost * (cnt[r] - cnt[l]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<ll> c(m);
    for(int i = 0; i < m; i++) cin >> c[i];
    vector<vector<tuple<ll, ll, ll>>> prescription(m);
    for(int i = 0; i < n; i++) {
        ll l, r, k;
        cin >> l >> r >> k;
        for(int j = 0; j < k; j++) {
            int a;
            cin >> a;
            prescription[a-1].emplace_back(l, r, i);
        }
    }

    neg.resize(n);
    for(int i = 0; i < m; i++)
        compute(prescription[i], c[i]);

    for(int i = 0; i < n; i++) {
        cout << ans - neg[i] << " ";
    }
}