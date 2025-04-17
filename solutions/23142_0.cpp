#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303;

int n, m, a[MAXN][MAXN], mn[MAXN][MAXN][MAXN];
ll ans[MAXN*MAXN];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for(int l = 1; l <= n; l++) for(int r = l; r <= n; r++) mn[0][l][r] = 0, mn[m+1][l][r] = 0;
    for(int i = 1; i <= m; i++) {
        for(int l = 1; l <= n; l++) {
            mn[i][l][l] = a[l][i];
            for(int r = l+1; r <= n; r++) {
                mn[i][l][r] = min(mn[i][l][r-1], a[r][i]);
            }
        }
    }
    for(int l = 1; l <= n; l++) {
        for(int r = l; r <= n; r++) {
            stack<int> s;
            for(int i = 0; i <= m+1; i++) {
                while(s.size() && mn[s.top()][l][r] > mn[i][l][r]) {
                    int j = s.top(); s.pop();
                    int left = j - s.top();
                    int right = i - j;
                    ans[mn[j][l][r]] += left * right;
                }
                s.push(i);
            }
        }
    }
    for(int i = 1; i <= n*m; i++) cout << ans[i] << "\n";
}