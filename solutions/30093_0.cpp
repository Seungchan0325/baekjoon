#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const int MAXN = 100005;

bool chk[MAXN];
ll dist[MAXN];
int N, M, K, tree[2*MAXN], mn[MAXN];
vector<pair<int, int>> graph[MAXN];

void update(int pos, int delta)
{
    for(tree[pos+=N] += delta; pos > 1; pos>>=1) {
        tree[pos>>1] = tree[pos] + tree[pos^1];
    }
}

int query(int l, int r)
{
    if(r < l) return 0;
    int ret = 0;
    for(l+=N, r+=N; l <= r; l>>=1, r>>=1) {
        if(l&1) ret += tree[l++];
        if(~r&1) ret += tree[r--];
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    vector<int> cent(M);
    for(auto& i : cent) cin >> i;
    for(auto i = 0; i < K; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    for(int i = 0; i <= N; i++) {
        dist[i] = INF;
    }

    priority_queue<pair<ll, int>> pq;
    for(int i = 0; i < M; i++) {
        pq.emplace(0, cent[i]);
        dist[cent[i]] = 0;
    }

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[u]) continue;
        for(auto [v, w] : graph[u]) {
            ll nd = d + w;
            if(nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(-nd, v);
            }
        }
    }

    vector<tuple<ll, int, int>> v;
    vector<ll> x;
    for(int u = 1; u <= N; u++) {
        mn[u] = 1e9 + 5;
        for(auto [v, w] : graph[u]) {
            mn[u] = min(mn[u], w);
        }
        v.emplace_back(dist[u], mn[u], u);
        x.push_back(dist[u]);
    }
    sort(v.begin(), v.end(), [](tuple<ll, int, int> a, tuple<ll, int, int> b) {
        auto [du, mu, u] = a;
        auto [dv, mv, v] = b;
        if(mu != mv) return mu > mv;
        if(du != dv) return du < dv;
        return u < v;
    });

    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());

    ll ans = 0;
    for(auto [d, m, u] : v) {
        int l = lower_bound(x.begin(), x.end(), d - m) - x.begin();
        int r = upper_bound(x.begin(), x.end(), d + m) - x.begin();
        ans += query(l, r - 1);

        int idx = lower_bound(x.begin(), x.end(), d) - x.begin();
        update(idx, 1);

        for(auto [v, w] : graph[u]) {
            if(chk[v] && dist[u] - m <= dist[v] && dist[v] <= dist[u] + m) ans--;
        }
        chk[u] = true;
    }

    cout << ans;
}