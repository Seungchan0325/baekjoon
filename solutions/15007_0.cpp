#include <bits/stdc++.h>

using namespace std;

const int MAXN = 255;

bool vst[MAXN];
int N, B, R, BX[MAXN], BY[MAXN], RX[MAXN], RY[MAXN], owner[MAXN];
vector<tuple<int, int, int>> edges;
vector<int> graph[MAXN];

bool dfs(int u)
{
    for(auto v : graph[u]) {
        if(vst[v]) continue;
        vst[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}

bool check(int L)
{
    for(int i = 1; i <= B; i++) graph[i].clear();
    memset(owner, -1, sizeof(owner));

    for(auto [u, v, w] : edges) {
        if(w < L) {
            graph[u].push_back(v);
        }
    }

    int cover = 0;
    for(int i = 1; i <= B; i++) {
        memset(vst, 0, sizeof(vst));
        cover += dfs(i);
    }

    return B + R - cover >= N;
}

int main()
{
    cin >> N >> B >> R;
    for(int i = 1; i <= B; i++) cin >> BX[i] >> BY[i];
    for(int i = 1; i <= R; i++) cin >> RX[i] >> RY[i];

    for(int i = 1; i <= B; i++) {
        for(int j = 1; j <= R; j++) {
            int d = (BX[i] - RX[j]) * (BX[i] - RX[j]) + (BY[i] - RY[j]) * (BY[i] - RY[j]);
            edges.emplace_back(i, j, d);
        }
    }

    int lo = -1;
    int hi = 800000005;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(check(mid)) lo = mid;
        else hi = mid;
    }

    double ans = sqrt(lo);
    cout << fixed << setprecision(6) << ans;
}