#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using llll = __int128_t;

const int MAXN = 1010;
const llll INF = 1e18 + 1;

int n;
llll pw[MAXN], dp[MAXN][MAXN];
string s;

void find(int l, ll k)
{
    if(l == 0) return;
    for(char c = 'a'; c <= 'z'; c++) {
        llll cnt = 0;
        for(int i = 0; i+l-1 < n; i++) {
            cnt += ((i<n && s[i]==c) + (i+l-1>=0 && s[i+l-1]==c)) * dp[i][i+l-1] * pw[l-1];
            cnt = min(INF, cnt);
        }
        if(k <= cnt) {
            for(int i = 0; i+l-1 < n; i++) {
                if(i+1<n && s[i] == c) dp[i+1][i+l-1] += dp[i][i+l-1], dp[i+1][i+l-1] = min(INF, dp[i+1][i+l-1]);
                if(i+l-2>=0 && s[i+l-1] == c) dp[i][i+l-2] += dp[i][i+l-1], dp[i][i+l-2] = min(INF, dp[i][i+l-2]);
            }
            cout << c;
            find(l-1, k);
            return;
        }
        k -= cnt;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    pw[0] = 1;
    for(int i = 1; i < MAXN; i++) pw[i] = min(2 * pw[i-1], INF);
    int t; cin >> t;
    while(t--) {
        ll k;
        cin >> n >> k;
        cin >> s;
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) dp[i][j] = 0;
        dp[0][n-1] = 1;
        find(n, k);
        cout << "\n";
    }
}