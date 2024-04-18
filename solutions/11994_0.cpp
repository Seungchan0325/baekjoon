#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const int MAXN = 105;
const int MAXK = 10;

int n, K, r[2*MAXN];
ll cache[2*MAXN][MAXK];

ll dp(int start, int end, int k)
{
    if(start == end && k == 0) return 0;
    if(k == 0) return INF;
    ll& ret = cache[start][k];
    if(ret != -1) return ret;

    ret = INF;
    ll sum = 0;
    for(int next = start + 1; next <= end; next++) {
        ret = min(dp(next, end, k - 1) + sum, ret);
        sum += (ll)(next - start) * r[next];
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> K;
    for(int i = 0; i < n; i++) {
        cin >> r[i];
        r[i+n] = r[i];
    }

    ll ans = INF;
    for(int i = 0; i < n - 1; i++) {
        memset(cache, -1, sizeof(cache));
        ans = min(dp(i, i + n, K), ans);
    }

    cout << ans;
}