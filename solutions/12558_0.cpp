#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101;
const ll inf = 2e18;

ll L, N, B[MAXN], D[101010];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> L >> N;
        for(int i = 0; i < N; i++) cin >> B[i];
        sort(B, B+N);
        int M = B[N-1];
        for(int i = 0; i < M; i++) D[i] = inf;

        priority_queue<pair<ll, ll>> pq;
        D[0] = 0;
        pq.push({0, 0});
        while(!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            d = -d;
            if(d > D[u]) continue;
            for(int i = 0; i < N-1; i++) {
                ll v = (u + B[i]) % M;
                ll w = (u + B[i]) < M;
                if(D[u]+w < D[v]) {
                    D[v] = D[u]+w;
                    pq.push({-D[v], v});
                }
            }
        }
        ll ans = D[L%M] + L/M;
        if(ans >= inf) cout << "Case #" << t << ": IMPOSSIBLE\n";
        else cout << "Case #" << t << ": " << ans << "\n";
    }
}