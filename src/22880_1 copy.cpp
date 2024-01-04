#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;
const int MOD = 1000000007;

int n, h[MAXN], dp[MAXN];

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    int sum = 1;
    int max_h = 0;
    dp[0] = 1;
    for(int i = 1; i < n; i++)
    {
        if(h[max_h] < h[i])
        {
            dp[i] = sum + 1;
            dp[i] %= MOD;
            max_h = i;
        }
        else
        {
            dp[i] = dp[i-1];
        }

        sum += dp[i];
        sum %= MOD;
    }

    cout << dp[n-1];
}