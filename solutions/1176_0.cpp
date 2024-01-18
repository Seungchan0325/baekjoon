#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

using ll = long long;

const ll MAXN = 16;

ll n, k, arr[MAXN], cache[MAXN][1<<MAXN];

ll dp(ll prev, ll taken)
{
    if(taken == (1<<n) - 1) return 1;
    ll& ret = cache[prev][taken];
    if(ret != -1) return ret;

    ret = 0;
    for(ll i = 0; i < n; i++)
    {
        if(taken & (1<<i)) continue;

        if(abs(arr[prev] - arr[i]) > k)
            ret += dp(i, taken | (1<<i));
    }

    return ret;
}

int main()
{
    cin >> n >> k;
    for(ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    memset(cache, -1, sizeof(cache));
    ll result = 0;
    for(ll i = 0; i < n; i++)
    {
        result += dp(i, (1<<i));
    }
    cout << result;
}