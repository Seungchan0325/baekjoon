#include <bits/stdc++.h>

using namespace std;

const int MAXN = 201;

bool done[MAXN];
int n, m, owner[MAXN];
vector<int> graph[MAXN];

bool dfs(int node) {
    for(auto next : graph[node]) {
        if(done[next]) continue;

        done[next] = true;
        if(!owner[next] || dfs(owner[next])) {
            owner[next] = node;
            return true;
        }
    }
    return false;
}

int main() {
    cin>>n>>m;
    for(int from = 1; from <= n; from++) {
        int t; cin>>t;
        int to;
        while(t--) {
            cin>>to; graph[from].push_back(to);
        }
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        memset(done, 0, sizeof(done));
        if(dfs(i)) cnt++;
    }

    cout<<cnt;
}