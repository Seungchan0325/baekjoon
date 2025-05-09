#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int n, a[55], cache[1'010'101][55];

int dp(int diff, int idx)
{
    if(idx >= n)
    {
        if(diff == 0) return 0;
        else return -INF;
    }
    int& ret = cache[diff + 500'000][idx];
    if(ret != -1) return ret;
    ret = max({dp(diff, idx+1), dp(diff+a[idx], idx+1)+a[idx], dp(diff-a[idx], idx+1)});
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    memset(cache, -1, sizeof(cache));
    int ans = dp(0, 0);
    if(ans == 0) cout << "-1";
    else cout << ans;
}