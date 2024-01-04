#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001;

int n, k, ans = 0;
vector<int> adj[MAXN];

int dfs(int u, int p) {
    int ret = 0;
    priority_queue<int> pq;
    for(int c : adj[u]) {
        if(c == p) continue;
        int result = dfs(c, u) + 1;
        ret = max(result, ret);
        pq.push(result);
    }
    
    int sum = 0;
    for(int i=0; i<2; i++) {
        if(pq.empty()) break;
        sum += pq.top(); pq.pop();
    }

    if(ret >= k || sum >= k) {
        //cout<<u<<"\n";
        ans++;
        ret = -1;
    }

    return ret;
}

int main() {
    cin>>n>>k;
    for(int i=1; i<n; i++) {
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int result = dfs(1, -1);
    //if(result >= k) ans++;

    cout<<ans;
}