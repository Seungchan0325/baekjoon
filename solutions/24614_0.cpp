#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool G[20][20];
int N, Q, P[20][20];
ll cache[20][1<<20];

ll dp(int u, unsigned vst)
{
    if(vst == (1<<N)-1) return u == N;
    ll& ret = cache[u][vst];
    if(ret != -1) return ret;
    ret = 0;
    int s = countr_one(vst);
    if(G[u][s]) ret += dp(countr_one(vst|(1<<s)), vst|(1<<s));
    for(int v = s+1; v < N; v++) {
        if(vst&(1<<v) || !G[u][v]) continue;
        ret += dp(v, vst|(1<<v));
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(cache, -1, sizeof(cache));
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int k; cin >> k;
            P[i][k-1] = j;
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(P[j][i] <= P[j][j]) G[i][j] = true;
        }
    }

    cin >> Q;
    while(Q--) {
        unsigned G, H;
        G = H = 0;
        for(int i = 0; i < N; i++) {
            char c; cin >> c;
            if(c == 'H') H |= 1<<i;
            else G |= 1<<i;
        }
        ll ans = dp(countr_one(G), G) * dp(countr_one(H), H);
        cout << ans << "\n";
    }
}