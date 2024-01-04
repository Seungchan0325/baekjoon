#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;
const int INF = 987654321;

int n, d[MAXN][MAXN], cache[MAXN][1<<MAXN];

int dp(int start, int taken)
{
    if(start == n) return 0;
    int& ret = cache[start][taken];
    if(ret != -1) return ret;

    ret = INF;
    for(int i = 0; i < n; i++)
    {
        if(taken & (1<<i)) continue;

        ret = min(dp(start + 1, taken | (1<<i)) + d[start][i], ret);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> d[i][j];
        }
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0);
    cout << result;
}