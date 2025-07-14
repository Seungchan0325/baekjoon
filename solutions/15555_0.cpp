#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3030;

int n, m;
char grid[MAXN][MAXN];

int solve(int i, int j)
{
    int ans = 0;
    int pdp0 = 0;
    int pdp1 = 0;
    int dp0 = 0;
    int dp1 = 0;
    while(i >= 1 && j <= m) {
        dp0 = dp1 = max(pdp0, pdp1);
        if(grid[i][j] == 'G') {
            if(grid[i][j-1] == 'R' && grid[i][j+1] == 'W') dp1 = max(dp1, pdp1+1);
            if(grid[i-1][j] == 'R' && grid[i+1][j] == 'W') dp0 = max(dp0, pdp0+1);
        }
        i--;
        j++;
        pdp0 = dp0;
        pdp1 = dp1;
    }
    return max(dp0, dp1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
  
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += solve(i, 1);
    }
    for(int j = 2; j <= m; j++) {
        ans += solve(n, j);
    }

    cout << ans;
}