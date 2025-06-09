#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using pii = pair<ll, ll>;

const ll inf = 1e18;

int get_depth(ll x)
{
    return 63 - countl_zero((unsigned long long)x);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int k;
        cin >> k;
        vector<ll> v(k);
        for(auto& i : v) cin >> i;
        priority_queue<pair<pii, ll>> pq;
        for(auto& i : v) pq.emplace(pair(get_depth(i), i), 0LL);
        ll mx = 0;
        ll ans = 0;
        while(pq.size() > 1) {
            auto top = pq.top(); pq.pop();
            ll mx1 = top.second;
            ll mx2 = 0;
            while(pq.size() && top.first == pq.top().first) {
                if(pq.top().second > mx1) {
                    mx2 = mx1;
                    mx1 = pq.top().second;
                } else if(pq.top().second > mx2) {
                    mx2 = pq.top().second;
                }
                pq.pop();
            }
            if(pq.size())
                ans += 2;
            top.first.first--;
            top.first.second /= 2;
            mx = max(mx, mx1+mx2);
            top.second = mx1 + 1;
            pq.push(top);
        }
        ans -= mx;
        cout << ans << "\n";
    }
}