#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;
const int MAXM = 100005;

struct Q {
    char c;
    int a, b, w;
};

bool visited[MAXN];
int n, m, root[MAXN];
ll weight[MAXN];
Q queries[MAXM];
vector<pair<int, int>> graph[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

bool Union(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return false;
    root[y] = x;
    return true;
}

void dfs(int u)
{
    visited[u] = true;

    for(auto [v, w] : graph[u]) {
        if(visited[v]) continue;
        weight[v] = weight[u] + w;
        dfs(v);
    }
}

int main()
{
    // ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        for(int i = 0; i <= n; i++) graph[i].clear();

        for(int i = 0; i < m; i++) {
            cin >> queries[i].c >> queries[i].a >> queries[i].b;
            if(queries[i].c == '!') {
                cin >> queries[i].w;

                int u = queries[i].a;
                int v = queries[i].b;
                int w = queries[i].w;

                graph[u].emplace_back(v, -w);
                graph[v].emplace_back(u, w);
            }
        }

        memset(visited, 0, sizeof(visited));
        for(int i = 1; i <= n; i++) {
            if(!visited[i]) {
                weight[i] = 0;
                dfs(i);
            }
        }

        iota(root, root + n + 1, 0);
        for(int i = 0; i < m; i++) {
            auto [c, a, b, w] = queries[i];
            if(c == '!') {
                Union(a, b);
            } else {
                if(find(a) != find(b)) {
                    cout << "UNKNOWN\n";
                } else {
                    ll result = weight[a] - weight[b];
                    cout << result << "\n";
                }
            }
        }
    }
}