#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 100;

ll N, A[MAXN], cache[MAXN][MAXN];

ll dp(int l, int r)
{
    if(l == r) return 0;
    ll& ret = cache[l][r];
    if(ret != 1) return ret;
    ret = 0;
    for(int m = l; m < r; m++) {
        ll cand = dp(l, m) + dp(m+1, r) + min<ll>((A[m]-A[l-1])*(A[r]-A[m]), 0);
        ret = min(ret, cand);
    }
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) A[i] += A[i-1];
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j++) {
            cache[i][j] = 1;
        }
    }
    cout << dp(1, N) << "\n";
}