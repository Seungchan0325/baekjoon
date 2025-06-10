#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010101;

ll n, a[MAXN];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    ll s = 0;
    ll ans = 0;
    for(int i = n; i >= 1; i--) {
        s += a[i];
        s = max(s, 0LL);
        ans += s;
    }
    cout << ans;
}