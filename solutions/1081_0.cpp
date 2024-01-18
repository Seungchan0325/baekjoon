#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXD = 10;

ll dp1[MAXD+1][2], dp2[MAXD+1][2];

pair<ll, ll> dp(int digit, bool is_boundary, int r)
{
    if(r < 0)
    {
        return {0, 0};
    }
    if(digit < 0)
    {
        return {0, 1};
    }

    ll& sum = dp1[digit][is_boundary];
    ll& cnt = dp2[digit][is_boundary];

    if(sum != -1)
    {
        return {sum, cnt};
    }

    sum = cnt = 0;

    int i = 10;
    if(is_boundary)
    {
        i = (r / (int)pow(10, digit)) % 10;
        auto [_sum, _cnt] = dp(digit - 1, true, r);
        sum += i * _cnt + _sum;
        cnt += _cnt;
    }

    i--;
    for(; i >= 0; i--)
    {
        auto [_sum, _cnt] = dp(digit - 1, false, r);
        sum += i * _cnt + _sum;
        cnt += _cnt;
    }

    return {sum, cnt};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int L, U;
    cin >> L >> U;

    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    ll ans = dp(10, true, U).first;

    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    ans -= dp(10, true, L - 1).first;

    cout << ans << "\n";
}