#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 3005;
 
int DP[MAXN][MAXN];
 
int LCS(string a, string b)
{
    int n = a.size();
    int m = b.size();
    memset(DP, 0, sizeof(DP));
    a = '?' + a;
    b = '#' + b;
 
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i] == b[j]) DP[i][j] = DP[i-1][j-1] + 1;
            else DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
        }
    }
 
    return DP[n][m];
}
 
int main()
{
    string s;
    cin >> s;
 
    int half = s.size()/2;
    
    int ans = 0;
    string a = s.substr(0, half);
    string b = s.substr(half);
    ans = (int)min(a.length(), b.length()) - LCS(a, b);
    if(s.size()%2 == 1) {
        half = (s.size()+1)/2;
        a = s.substr(0, half);
        b = s.substr(half);
        ans = max((int)min(a.length(), b.length()) - LCS(a, b), ans);
    }
 
    cout << ans;
}