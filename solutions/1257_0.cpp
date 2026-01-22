#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010;
const int MAXL = 10101;
const ll inf = 1e18;

ll M, N, L, A[MAXN], D[MAXL];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M;
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    sort(A, A+N);
    L = A[N-1];
    for(int i = 1; i < L; i++) D[i] = inf;
    deque<pair<ll, ll>> pq;
    pq.push_back({0, 0});
    while(!pq.empty()) {
        auto [d, u] = pq.front(); pq.pop_front();
        d = -d;
        if(d > D[u]) continue;
        for(int i = 0; i < N-1; i++) {
            ll v = (u + A[i]) % L;
            ll w = (u + A[i]) < L;
            if(d+w < D[v]) {
                D[v] = d+w;
                if(w) pq.push_back({-D[v], v});
                else pq.push_back({-D[v], v});
            }
        }
    }
    cout << D[M%L] + M/L << "\n";
}