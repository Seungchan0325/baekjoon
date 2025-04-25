#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ll n;
    cin >> n;
    ll c0, c1;
    c0 = c1 = 0;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        if(a == 0) c0++;
        if(a == 1) c1++;
    }

    ll ans = (n - c0 - c1) * c0;
    ans += (c0 - 1) * c0 / 2;
    ans += c0 * c1 * 2;
    cout << ans;
}