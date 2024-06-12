#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

bool is_graph[MAXN];
int N, Q, root[MAXN], sz[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);

    if(x == y) return;

    if(x > y) swap(x, y);
    root[y] = x;
    sz[x] += sz[y];
    return;
}

int main()
{
    priority_queue<pair<int, int>> pq, erased;
    cin >> N >> Q;
    iota(root, root + N + 1, 0);
    fill(sz, sz + N + 1, 1);
    for(int i = 1; i <= N; i++) pq.emplace(1, -i);

    while(Q--) {
        int op;
        cin >> op;

        if(op == 1) {
            int u, v;
            cin >> u >> v;

            u = find(u);
            v = find(v);

            if(is_graph[u] || is_graph[v]) {
                if(is_graph[u] && !is_graph[v]) erased.emplace(sz[v], -v);
                else if(is_graph[v] && !is_graph[u]) erased.emplace(sz[u], -u);
                is_graph[u] = is_graph[v] = true;
            } else if(u == v) {
                erased.emplace(sz[u], -u);
                is_graph[u] = true;
            } else {
                erased.emplace(sz[u], -u);
                erased.emplace(sz[v], -v);
                merge(u, v);
                pq.emplace(sz[find(u)], -find(u));
            }
        } else {
            while(erased.size() && pq.top() == erased.top()) {
                pq.pop();
                erased.pop();
            }

            auto [s, u] = pq.top(); pq.pop();
            cout << -u << "\n";
        }
    }
}