#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

bool visited[MAXN];
int n, v[MAXN], dp1[MAXN], dp2[MAXN];
vector<int> childs[MAXN];

void dfs(int node) {
    visited[node] = true;

    dp1[node] = v[node];
    for(auto child : childs[node]) {
        if(visited[child]) continue;
        dfs(child);

        dp1[node] += dp2[child];
        dp2[node] += max(dp1[child], dp2[child]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=1; i<=n; i++) cin>>v[i];
    for(int i=2; i<=n; i++) {
        int a, b; cin>>a>>b;
        childs[a].push_back(b);
        childs[b].push_back(a);
    }

    dfs(1);
    cout<<max(dp1[1], dp2[1]);
}