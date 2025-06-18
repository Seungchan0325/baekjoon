#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, a[MAXN], b[MAXN];

int main()
{
    cin >> n;
    priority_queue<pair<int, int>> pq;
    for(int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y;
        a[i] = max(x, y);
        b[i] = -min(x, y);
        pq.emplace(a[i]-b[i], i);
    }
    int ans = 0;
    for(int i = 0; i < (n+1)/2; i++) {
        auto [_, j] = pq.top(); pq.pop();
        ans += a[j];
    }
    while(pq.size()) {
        auto [_, j] = pq.top(); pq.pop();
        ans += b[j];
    }
    cout << -ans;
}