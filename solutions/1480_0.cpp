#include <bits/stdc++.h>

using namespace std;

int n, m, c, w[13], cache[1<<13][20][20];

int dp(int taken, int usage, int bag)
{
    if(bag == m || taken == (1<<n) - 1) return 0;
    int& ret = cache[taken][usage][bag];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i < n; i++)
    {
        if(taken & (1<<i)) continue;

        if(usage + w[i] <= c) {
            if(usage + w[i] == c) ret = max(dp(taken | (1<<i), 0, bag + 1) + 1, ret);
            else ret = max(dp(taken | (1<<i), usage + w[i], bag) + 1, ret);
        }
        else if(bag + 1 < m && w[i] < c) ret = max(dp(taken | (1<<i), w[i], bag + 1) + 1, ret);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m >> c;
    for(int i = 0; i < n; i++) cin >> w[i];

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 0);
    cout << result;
}