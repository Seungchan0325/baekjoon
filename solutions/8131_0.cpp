#include <bits/stdc++.h>

using namespace std;

int compute(int k, int n, int m, vector<vector<int>> t)
{
    vector<vector<int>> s1(m+1, vector<int>(n+1)), s2(m+1, vector<int>(n+1));
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            s1[i][j] += s1[i][j-1] + t[i][j];
        }
    }
    for(int j = 1; j <= n; j++) {
        for(int i = 1; i <= m; i++) {
            s2[i][j] += s2[i-1][j] + t[i][j];
        }
    }

    auto check = [&](int l, int r) -> bool
    {
        int up = 1;
        int down = m;
        int left = 1;
        int right = n;
        while(up <= down) {
            if(s1[up][right] - s1[up][left-1] <= k) up++;
            else if(s1[down][right] - s1[down][left-1] <= k) down--;
            else if(left < l && s2[down][left] - s2[up-1][left] <= k) left++;
            else if(r < right && s2[down][right] - s2[up-1][right] <= k) right--;
            else break;
        }
        return up > down;
    };

    int ans = 1e9;
    int r = 1;
    for(int l = 1; l <= n; l++) {
        r = max(l, r);
        while(r <= n && check(l, r)) r++;
        if(l <= r) ans = min(ans, m + n - r + l);
    }

    return ans;
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int k, n, m;
    cin >> k >> n >> m;
    vector<vector<int>> t1(m+1, vector<int>(n+1));
    vector<vector<int>> t2(n+1, vector<int>(m+1));
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> t1[i][j];
            t2[j][i] = t1[i][j];
        }
    }

    int ans = compute(k, n, m, t1);
    ans = min(ans, compute(k, m, n, t2));
    cout << ans;
}