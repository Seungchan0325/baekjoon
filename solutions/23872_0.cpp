#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1010101;

ll T, N, K, x[MAXN], y[MAXN], l[MAXN], dp1[MAXN], dp2[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T >> N >> K;
    for(int i = 1; i <= N; i++) cin >> x[i] >> y[i];
    int j = N;
    for(int i = N; i >= 1; i--) {
        while(j >= 1 && x[i]-x[j] <= K) j--;
        l[i] = j;
    }

    ll C = T == 1 ? 1e18 : -1e18;
    auto M = [&](ll a, ll b) {
        if(T == 1) return min(a, b);
        else return max(a, b);
    };
    for(int i = 1; i <= N; i++) {
        dp1[i] = dp2[i] = C;
        j = l[i];
        if((i-j)&1) dp1[i] = M(dp1[j] + y[i], dp1[i]);
        else dp1[i] = M(dp2[j+1] + y[i], dp1[i]);

        if(i >= 2 && x[i]-x[i-1] <= K) dp2[i] = M(dp1[i-2], dp2[i]);
        if(i >= 3 && x[i]-x[i-2] <= K) {
            j = l[i-1];
            if((i-j)&1) dp2[i] = M(dp1[j] + y[i-1], dp2[i]);
            else dp2[i] = M(dp2[j+1] + y[i-1], dp2[i]);
        }
        dp1[i] = M(dp1[i], dp2[i]);
    }
    cout << M(dp1[N], dp2[N]);
}