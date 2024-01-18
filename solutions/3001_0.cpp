#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXD = 15;
const int MAXS = 135;

ll cache[MAXS+1][MAXD+2][2];

ll dp(int s, int digit, bool is_boundary, ll max_v)
{
    if(s < 0)
    {
        return 0;
    }
    if(digit == -1)
    {
        if(s == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    ll& ret = cache[s][digit][is_boundary];
    if(ret != -1) return ret;

    int max_i = is_boundary ? ((max_v / (ll)pow(10, max(digit, 0))) % 10) : 10;

    ret = 0;
    for(int i = 0; i < max_i; i++)
    {
        ret += dp(s - i, digit - 1, false, max_v);
    }

    if(is_boundary)
    {
        ret += dp(s - max_i, digit - 1, true, max_v);
    }

    return ret;
}

ll Count(int s, ll min_v, ll max_v)
{
    memset(cache, -1, sizeof(cache));
    ll top = dp(s, 16, true, max_v);

    memset(cache, -1, sizeof(cache));
    ll bottom = dp(s, 16, true, min_v - 1);

    return top - bottom;
}

int main()
{
    ll a, b, s;
    cin >> a >> b >> s;

    cout << Count(s, a, b) << "\n";

    ll lo = a - 1, hi = b;
    while(lo + 1 < hi)
    {
        ll mid = (lo + hi) / 2;
        ll cnt = Count(s, a, mid);
        if(cnt < 1)
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    }

    cout << hi;
}