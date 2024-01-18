#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, marbles[5], cache[6][6][11][11][11][11][11];

ll dp(ll pp, ll p, ll a, ll b, ll c, ll d, ll e) {
    if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0) return 1;
    ll& ret = cache[pp][p][a][b][c][d][e];
    if(ret != -1) return ret;

    ret = 0;
    if(a > 0 && pp != 1 && p != 1)
        ret += dp(p, 1, a-1, b, c, d, e);
    if(b > 0 && pp != 2 && p != 2)
        ret += dp(p, 2, a, b-1, c, d, e);
    if(c > 0 && pp != 3 && p != 3)
        ret += dp(p, 3, a, b, c-1, d, e);
    if(d > 0 && pp != 4 && p != 4)
        ret += dp(p, 4, a, b, c, d-1, e);
    if(e > 0 && pp != 5 && p != 5)
        ret += dp(p, 5, a, b, c, d, e-1);

    return ret;
}

int main() {
    cin >> n;
    ll sum = 0;
    for(ll i = 0; i < n; i++) {
        cin >> marbles[i];
        sum += marbles[i];
    }

    memset(cache, -1, sizeof(cache));
    ll result = dp(0, 0, marbles[0], marbles[1], marbles[2], marbles[3], marbles[4]);
    cout << result;
}