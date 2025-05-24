#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        ll n, k;
        cin >> n >> k;
        ll ans = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(1, k-1);
        pq.emplace(n-k+1, 1);
        while(true) {
            auto [a1, c1] = pq.top(); pq.pop();
            if(pq.empty() && c1 == 1) break;
            if(c1 > 1) {
                pq.emplace(2*a1, c1/2);
                ans += a1 * (c1&~1);
                if(c1&1) pq.emplace(a1, 1);
            } else {
                auto [a2, c2] = pq.top(); pq.pop();
                if(c2 > 1) pq.emplace(a2, c2 - 1);
                pq.emplace(a1 + a2, 1);
                ans += a1 + a2;
            }
        }
        cout << ans << "\n";
    }
}