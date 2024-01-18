#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin>>n;
    vector<ll> v;
    vector<pii> ls(n);
    for(auto& [h, o] : ls) {
        cin>>h>>o;
        if(h > o) swap(h, o);
        v.push_back(h);
    }
    ll d; cin>>d;

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<ll> shifts(v.size() + 1);
    for(ll i = 0; i < n; i++) {
        if(ls[i].second - ls[i].first > d) continue;
        ll start = lower_bound(v.begin(), v.end(), ls[i].second - d) - v.begin();
        ll end = upper_bound(v.begin(), v.end(), ls[i].first) - v.begin();
        shifts[start]++;
        shifts[end]--;
    }

    ll ans = 0;
    ll sum = 0;
    for(ll i = 0; i < v.size(); i++) {
        sum += shifts[i];
        ans = max(sum, ans);
    }
    cout<<ans;
}