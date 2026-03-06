#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 7070;

int n, m, ih[MAXN][MAXN], iv[MAXN][MAXN];
string S, T;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> S >> T;
    n = S.size();
    m = T.size();

    for(int i = 0; i <= n; i++) iv[i][0] = 0;
    for(int i = 0; i <= m; i++) ih[0][i] = i;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(S[i-1] == T[j-1]) {
                ih[i][j] = iv[i][j-1];
                iv[i][j] = ih[i-1][j];
            } else {
                ih[i][j] = max(ih[i-1][j], iv[i][j-1]);
                iv[i][j] = min(ih[i-1][j], iv[i][j-1]);
            }
        }
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            ll a = j - ih[i][j];
            ll b = m - j + 1;
            ans += a * b;
        }
    }
    cout << ans << "\n";
}