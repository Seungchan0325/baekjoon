#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1<<18;

int N, A[MAXN], B[MAXN], p;

void dfs(int i, int dep, int x, int y)
{
    if(2*i <= N) dfs(2*i, dep+1, x, y);
    if(x <= dep && dep <= y) B[p++] = i;
    if(2*i+1 <= N) dfs(2*i+1, dep+1, x, y);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    ll ans = -1e18;
    int h = 32 - countl_zero((unsigned)N);
    for(int x = 0; x <= h; x++) {
        for(int y = x; y <= h; y++) {
            p = 0; dfs(1, 0, x, y);
            ll s = 0;
            for(int i = 0; i < p; i++) {
                s = max<ll>(A[B[i]], A[B[i]] + s);
                ans = max(ans, s);
            }
        }
    }
    cout << ans << "\n";
}