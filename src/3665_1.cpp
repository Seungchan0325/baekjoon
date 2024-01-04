#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

int n, m, ranking[MAXN], reranking[MAXN], inDeg[MAXN];
vector<int> graph[MAXN];

bool visited[MAXN];
bool dfs(int start, int dst) {
    visited[start] = true;

    if(start == dst) return true;

    for(auto next : graph[start]) {
        if(visited[next]) continue;

        if(dfs(next, dst)) return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int tc; cin >> tc;
    while(tc--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> ranking[i];
            reranking[ranking[i]] = i;
        }

        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++) {
                graph[ranking[i]].push_back(ranking[j]);
                inDeg[ranking[j]]++;
            }

        cin >> m;
        for(int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            if(reranking[v] > reranking[u]) swap(u, v);

            graph[u].push_back(v);
            inDeg[v]++;

            auto pos = find(graph[v].begin(), graph[v].end(), u);
            if(pos != graph[v].end()) graph[v].erase(pos);
            inDeg[u]--;
        }

        queue<int> q;
        vector<int> ans;
        for(int i = 1; i <= n; i++)
            if(inDeg[i] == 0) {
                q.push(i);
                ans.push_back(i);
            }
        
        while(q.size() == 1) {
            int cur = q.front(); q.pop();

            for(auto adj : graph[cur]) {
                if(--inDeg[adj] == 0) {
                    q.push(adj);
                    ans.push_back(adj);
                }
            }
        }

        if(q.size() > 0) {
            cout << "?";
        } else if(any_of(inDeg, inDeg + n, [](int i){ return i != 0; })) {
            cout << "IMPOSSIBLE";
        } else {
            for(auto i : ans) cout << i << " ";
        }
        cout << "\n";

        for(int i = 1; i <= n; i++) {
            graph[i].clear();
            inDeg[i] = 0;
        }
    }
}