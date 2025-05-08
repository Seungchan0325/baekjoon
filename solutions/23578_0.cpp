#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(auto& i : a) cin >> i;

    if(n == 1) {
        cout << "0";
        return 0;
    }
    
    ll ans = 0;
    priority_queue<pair<ll, int>> pq;
    for(int i = 0; i < n; i++) {
        ans += a[i]; b[i]++;
        pq.emplace(-a[i] * (2 * b[i] + 1), i);
    }

    for(int i = 2; i < n; i++) {
        auto [p, j] = pq.top(); pq.pop();
        ans += -p; b[j]++;
        pq.emplace(-a[j] * (2 * b[j] + 1), j);
    }

    cout << ans;
}