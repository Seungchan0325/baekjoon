#include <bits/stdc++.h>
#include <queue>

using namespace std;

using ll = long long;

const int MAXN = 1010101;

ll n, h[MAXN], d[MAXN];

int main()
{
    cin >> n;
    for(int i = 0; i <= n; i++) cin >> h[i];

    if(n&1) {
        cout << "-1\n";
        return 0;
    }

    for(int i = 0; i < n; i++) d[i] = h[i+1] - h[i];
    ll ans = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(int i = 0; i < n; i++) ans += abs(d[i]+1);
    for(int i = 1; i < n; i+=2) {
        pq.push(abs(d[i-1]-1)-abs(d[i-1]+1));
        ans += pq.top(); pq.pop();
        pq.push(abs(d[i]-1)-abs(d[i]+1));
    }
    cout << ans/2 << "\n";
}
