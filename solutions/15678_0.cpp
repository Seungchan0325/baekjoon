#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, d;
    cin >> n >> d;

    ll ans = -INF;
    deque<pair<ll, int>> dq;
    for(int i = 0; i < n; i++) {
        ll x;
        cin >> x;

        while(!dq.empty() && dq.front().second < i - d) dq.pop_front();
        if(!dq.empty() && 0 < dq.front().first) x += dq.front().first;
        ans = max(x, ans);
        while(!dq.empty() && dq.back().first <= x) dq.pop_back();
        dq.emplace_back(x, i);
    }

    cout << ans;
}