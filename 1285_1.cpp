#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int coins[n] = {};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            char c;
            cin >> c;
            if(c == 'T') coins[i] |= (1<<j);
        }
    }

    int ans = 987654321;
    for(int bit = 0; bit < (1<<n); bit++)
    {
        int cnt = 0;
        for(int i = 0; i < n; i++)
        {
            cnt += min(
                __builtin_popcount(coins[i] ^ bit),
                __builtin_popcount(coins[i] ^ bit ^ ((1<<n)-1))
            );
        }
        ans = min(cnt, ans);
    }

    cout << ans;
}