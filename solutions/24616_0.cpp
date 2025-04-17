#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll dist(ll x1, ll y1, ll x2, ll y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n;
    cin >> n;
    set<int> ps[11];
    for(int i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        ps[y].insert(x);
    }
    priority_queue<tuple<ll, ll, ll, ll, ll>, vector<tuple<ll, ll, ll, ll, ll>>, greater<>> pq;
    auto near = [&](ll x, ll y) {
        ll d = 1e18;
        ll nx = -1, ny = -1;
        for(int i = 0; i <= 10; i++) {
            auto it = ps[i].lower_bound(x);
            if(it != ps[i].end()) {
                if(dist(*it, i, x, y) < d) {
                    d = dist(*it, i, x, y);
                    nx = *it;
                    ny = i;
                }
            }
            if(it != ps[i].begin()) {
                it--;
                if(dist(*it, i, x, y) < d) {
                    d = dist(*it, i, x, y);
                    nx = *it;
                    ny = i;
                }
            }
        }
        return tuple(d, nx, ny, x, y);
    };
    for(int y = 0; y <= 10; y++) {
        if(ps[y].empty()) continue;
        ll x = *ps[y].begin();
        ps[y].erase(x);
        pq.emplace(near(x, y));
        break;
    }
    
    ll ans = 0;
    for(int cx = 1; cx < n; cx++) {
        while(true) {
            auto [d, nx, ny, x, y] = pq.top();
            if(ps[ny].count(nx)) break;
            pq.pop();
            pq.emplace(near(x, y));
        }
        auto [d, nx, ny, x, y] = pq.top(); pq.pop();
        ans += d;
        ps[ny].erase(nx);
        pq.emplace(near(nx, ny));
        pq.emplace(near(x, y));
    }
    cout << ans;
}