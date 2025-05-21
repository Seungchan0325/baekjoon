#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010101;
const ll INF = 3 * 1e18;

ll N, M, K, R, W, p[MAXN], ans;
vector<pair<int, int>> edges;

ll compute(ll u, ll v, ll k)
{
    if(k < 0 || k > K) return -INF;
    return (k+1)/2*p[u] + k/2*p[v] + k/R*W;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K >> R >> W;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
    }
    for(int i = 1; i <= N; i++) cin >> p[i];

    ll r = R;
    ll r2 = 2*R;
    ll b = K/R*R;
    ll b2 = K/R*R-R;

    initializer_list<ll> moves = {
        0, 1,
        K, K-1, K-2,
        r+1, r, r-1, r-2,
        r2+1, r2, r2-1, r2-2,
        b+1, b, b-1, b-2,
        b2+1, b2, b2-1, b2-1,
    };

    for(auto [u, v] : edges) {
        for(ll k : moves) {
            ans = max(ans, compute(u, v, k));
            ans = max(ans, compute(v, u, k));
        }
    }

    cout << ans;
}