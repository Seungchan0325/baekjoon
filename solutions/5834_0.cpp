#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int n, p[MAXN], cache[MAXN][MAXN][2];

int dp(int i, int j, int lr)
{
    if(i == 0 && j == n) return 0;
    int& ret = cache[i][j][lr];
    if(ret != -1) return ret;
    ret = 1e9;
    int remains = n + i - j;
    if(i > 0) ret = min(ret, dp(i-1, j, 0) + remains * (p[i] - p[i-1] + (lr ? p[j] - p[i] : 0)));
    if(j < n) ret = min(ret, dp(i, j+1, 1) + remains * (p[j+1] - p[j] + (lr ? 0 : p[j] - p[i])));
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i];
    sort(p, p+n+1);
    int start = lower_bound(p, p+n+1, 0) - p;
    memset(cache, -1, sizeof(cache));
    int ans = dp(start, start, 0);
    cout << ans << "\n";
}