#include <bits/stdc++.h>

using namespace std;

using namespace std;

using ll = long long;

const int MAXN = 105;

int N, a;
ll psum[MAXN], cache[MAXN][MAXN][2];


ll f(int s, int e, bool l_r)
{
    if(s == 1 && e == N) return 0;
    ll& ret = cache[s][e][l_r];
    if(ret != -1) return ret;

    ret = 1e18;
    int cur = l_r ? e : s;
    int remain = N - e + s - 1;
    if(1 < s) ret = min(f(s - 1, e, false) + remain * (psum[cur] - psum[s - 1]), ret);
    if(e < N) ret = min(f(s, e + 1, true) + remain * (psum[e + 1] - psum[cur]), ret);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T;
    cin >> T;
    while(T--) {
        cin >> N;
        cin >> a;
        for(int i = 2; i <= N; i++) {
            cin >> psum[i];
            psum[i] += psum[i-1];
        }

        memset(cache, -1, sizeof(cache));
        ll result = min(f(a, a, false), f(a, a, true));
        cout << result << "\n";
    }
}