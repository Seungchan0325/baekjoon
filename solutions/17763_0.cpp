#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<pair<int, int>> fish(n);
    for(auto& [len, color] : fish) {
        char c;
        cin >> len >> c;
        if(c == 'R') color = 0;
        if(c == 'G') color = 1;
        if(c == 'B') color = 2;
    }
    sort(fish.begin(), fish.end());
    
    int j = 0;
    array<int, 3> cnt = {};
    vector<array<int, 3>> rects;
    for(int i = 0; i < n; i++) {
        while(j < n && fish[j].first < 2*fish[i].first) {
            cnt[fish[j].second]++;
            j++;
        }
        rects.push_back({cnt[0]+1, cnt[1]+1, cnt[2]+1});
        cnt[fish[i].second]--;
    }

    ll ans = 0;
    ll area = 0;
    ll px = 1e18;
    sort(rects.begin(), rects.end(), [](array<int, 3> a, array<int, 3> b){
        if(a[0] != b[0]) return a[0] > b[0];
        if(a[1] != b[1]) return a[1] < b[1];
        return a[2] < b[2];
    });
    rects.erase(unique(rects.begin(), rects.end()), rects.end());
    set<pair<ll, ll>> s;
    s.insert(pair(0, 1e18));
    s.insert(pair(1e18, 0));
    for(auto [x, y, z] : rects) {
        ans += area * (px - x);
        px = x;
        auto nxt = s.lower_bound(pair(y, z));
        auto prv = --s.lower_bound(pair(y, z));
        if(nxt->second >= z) continue;
        while(prv->second <= z) {
            auto p = *prv;
            auto l = prv; --l;
            auto r = prv; ++r;
            s.erase(prv);
            ll w = p.first - l->first;
            ll h = p.second - r->second;
            area -= w*h;
            prv = l;
        }
        ll w = y - prv->first;
        ll h = z - nxt->second;
        s.insert(pair(y, z));
        area += w*h;
    }

    ans += area * px;

    cout << ans-1 << "\n";
}