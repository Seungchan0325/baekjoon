#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for(auto& [b, a] : v) cin >> a;
    for(auto& [b, a] : v) cin >> b;
    sort(v.begin(), v.end());
    long long ans = v[0].second;
    priority_queue<int> pq;
    for(int i = 2; i+1 < n; i+=2) {
        pq.push(v[i-1].second);
        pq.push(v[i].second);
        ans += pq.top(); pq.pop();
    }
    cout << ans << "\n";
}