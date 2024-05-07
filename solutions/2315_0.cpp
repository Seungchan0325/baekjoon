#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1005;

ll N, M, D[MAXN], W[MAXN], psum[MAXN], cache[MAXN][MAXN][2];

ll f(int s, int e, bool lr)
{
    if(s == 1 && e == N) return 0;
    ll& ret = cache[s][e][lr];
    if(ret != -1) return ret;

    ret = 1e18;
    ll cur = lr ? e : s;
    ll remain = psum[s-1] + psum[N] - psum[e];
    if(1 < s) ret = min(ret, f(s - 1, e, false) + remain * (D[cur] - D[s-1]));
    if(e < N) ret = min(ret, f(s, e + 1, true) + remain * (D[e+1] - D[cur]));
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> D[i] >> W[i];
        psum[i] = psum[i-1] + W[i];
    }

    memset(cache, -1, sizeof(cache));

    ll result = min(f(M, M, false), f(M, M, true));
    cout << result;
}