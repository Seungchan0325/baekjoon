#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 20;
const int mod = 100000;

int m, n, dp[2][1<<MAXN], ndp[2][1<<MAXN], question;
int flag[MAXN][MAXN];

bool is_valid(int now, int down, int right)
{
    return !(now && down && right);
}

int pw(int x, int n)
{
    if(n == 0) return 1;
    if(n&1) return (ll)x * pw(x, n-1) % mod;
    ll half = pw(x, n/2);
    return half * half % mod;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> m >> n;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            char c; cin >> c;
            flag[i][j] = string("JOI?").find(c);
            if(c == '?') question++;
        }
    }

    dp[0][0] = 1;
    for(int j = n-1; j >= 0; j--) {
        for(int i = m-1; i >= 0; i--) {
            memset(ndp, 0, sizeof(ndp));
            for(int k = 0; k < 2; k++) {
                for(int bit = 0; bit < (1<<m); bit++) {
                    if(flag[i][j] != 3) {
                        if(is_valid(flag[i][j]==0, k, bit&1) || i == m-1) {
                            int nbit = bit>>1;
                            if(flag[i][j] == 1) nbit |= 1<<(m-1);
                            ndp[flag[i][j]==2][nbit] += dp[k][bit];
                            ndp[flag[i][j]==2][nbit] %= mod;
                        }
                    } else {
                        for(int nk = 0; nk < 3; nk++) {
                            if(is_valid(nk==0, k, bit&1) || i == m-1) {
                                int nbit = bit>>1;
                                if(nk == 1) nbit |= 1<<(m-1);
                                ndp[nk==2][nbit] += dp[k][bit];
                                ndp[nk==2][nbit] %= mod;
                            }
                        }
                    }
                }
            }
            memcpy(dp, ndp, sizeof(dp));
        }
    }

    int ans = 0;
    for(int k = 0; k < 2; k++) {
        for(int bit = 0; bit < (1<<m); bit++) {
            ans += dp[k][bit];
            ans %= mod;
        }
    }

    ans = (pw(3, question) - ans + mod) % mod;
    cout << ans << "\n";
}