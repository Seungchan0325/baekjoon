#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 1e5 + 1;
const int MAXM = 2e5 + 1;

bool is_leaf[MAXN], visited[MAXN];
int n, m;
pii edges[MAXM];
vector<int> roots, tEdges[MAXN], tNodes[MAXN];
vector<pii> adjlist[MAXN];

void dfs(int node, int root) {
    visited[node] = true;

    is_leaf[node] = true;
    tNodes[root].push_back(node);
    for(auto [next, idx] : adjlist[node])
        if(!visited[next]) {
            dfs(next, root);
            is_leaf[node] = false;
            tEdges[root].push_back(idx);
        }
}

void print(int usize, int vsize, vector<int> uNodes, vector<int> uEdges, vector<int> vNodes, vector<int> vEdges) {
    cout<<usize<<" "<<vsize<<"\n";
    sort(uNodes.begin(), uNodes.end());
    sort(uEdges.begin(), uEdges.end());
    sort(vNodes.begin(), vNodes.end());
    sort(vEdges.begin(), vEdges.end());

    for(int node : uNodes) cout<<node<<" ";
    cout<<"\n";
    for(int edge : uEdges) cout<<edge<<" ";
    cout<<"\n";
    for(int node : vNodes) cout<<node<<" ";
    cout<<"\n";
    for(int edge : vEdges) cout<<edge<<" ";
    cout<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n>>m;
    for(int i=1; i<=m; i++) {
        int a, b; cin>>a>>b;
        adjlist[a].push_back({b, i});
        adjlist[b].push_back({a, i});
        edges[i] = {a, b};
    }

    for(int u = 1; u <= n; u++)
        if(!visited[u]) {
            roots.push_back(u);
            dfs(u, u);
        }
    
    int cnt = roots.size();
    if(n == 1) goto nothing;
    if(cnt == 1) {
        int v = find(is_leaf + 1, is_leaf + n + 1, true) - is_leaf;
        if(v == n + 1) goto nothing;

        //remove v
        auto it = find(tNodes[roots[0]].begin(), tNodes[roots[0]].end(), v);
        //if(it != tNodes[roots[0]].end())
            tNodes[roots[0]].erase(it);
        it = find_if(tEdges[roots[0]].begin(), tEdges[roots[0]].end(), [&](int i) { return edges[i].first == v || edges[i].second == v; });
        //if(it != tEdges[roots[0]].end())
            tEdges[roots[0]].erase(it);
        if(tNodes[roots[0]].size() == 1) goto nothing;
        print(tNodes[roots[0]].size(), 1, tNodes[roots[0]], tEdges[roots[0]], {v}, {});
    } else if(cnt == 2) {
        if(tNodes[roots[0]].size() == tNodes[roots[1]].size()) goto nothing;

        print(tNodes[roots[0]].size(), tNodes[roots[1]].size(), tNodes[roots[0]], tEdges[roots[0]], tNodes[roots[1]], tEdges[roots[1]]);
    } else if(cnt > 2) {
        goto nothing;
    }

    return 0;

nothing:
    cout<<-1;
}