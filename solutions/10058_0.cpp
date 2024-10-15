#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

bool vst[MAXN], coverB[MAXN];
int N, d, X[MAXN], Y[MAXN], owner[MAXN], rowner[MAXN];
vector<int> graph[MAXN];

int ccw(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
}

int dist(int x1, int y1, int x2, int y2)
{
    int x = x1 - x2;
    int y = y1 - y2;
    return x * x + y * y;
}

bool dfs(int u)
{
    for(auto v : graph[u]) {
        if(vst[v]) continue;
        vst[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[v] = u;
            rowner[u] = v;
            return true;
        }
    }
    return false;
}

void dfs2(int u)
{
    vst[u] = true;
    for(auto v : graph[u]) {
        coverB[v] = true;
        if(!vst[owner[v]]) dfs2(owner[v]);
    }
}

vector<int> solve(int i, int j)
{
    vector<int> up, dw;
    int r = dist(X[i], Y[i], X[j], Y[j]);
    for(int k = 1; k <= N; k++) {
        if(dist(X[i], Y[i], X[k], Y[k]) <= r && dist(X[j], Y[j], X[k], Y[k]) <= r) {
            if(ccw(X[i], Y[i], X[j], Y[j], X[k], Y[k]) >= 0)
                up.push_back(k);
            else
                dw.push_back(k);
        }
    }

    memset(owner, -1, sizeof(owner));
    memset(rowner, -1, sizeof(rowner));
    for(int k = 1; k <= N; k++) {
        graph[k].clear();
    }

    for(auto u : up) {
        for(auto d : dw) {
            if(dist(X[u], Y[u], X[d], Y[d]) > r) {
                graph[u].push_back(d);
            }
        }
    }

    for(auto u : up) {
        memset(vst, 0, sizeof(vst));
        dfs(u);
    }

    vector<int> ans;
    memset(vst, 0, sizeof(vst));
    memset(coverB, 0, sizeof(coverB));
    for(auto u : up) {
        if(rowner[u] == -1) dfs2(u);
    }

    for(auto u : up) {
        if(rowner[u] == -1 || vst[u]) ans.push_back(u);
    }
    for(auto d : dw) {
        if(!coverB[d]) ans.push_back(d);
    }

    sort(ans.begin(), ans.end());

    return ans;
}

signed main()
{
    cin >> N >> d;
    d = d * d;
    for(int i = 1; i <= N; i++) {
        cin >> X[i] >> Y[i];
    }

    vector<int> ans = {1};
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j < i; j++) {
            if(dist(X[i], Y[i], X[j], Y[j]) <= d) {
                auto cand = solve(i, j);
                if(cand.size() > ans.size()) {
                    ans = cand;
                }
            }
        }
    }

    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << " ";
}