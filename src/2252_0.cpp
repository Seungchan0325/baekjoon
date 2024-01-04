#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m; cin>>n>>m;
    vector<int> degree(n);
    vector<vector<int>> adjlist(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin>>a>>b; a--; b--;
        adjlist[a].push_back(b);
        degree[b]++;
    }


    queue<int> q;
    for(int i = 0; i < n; i++)
        if(degree[i] == 0)
            q.push(i);

    vector<int> ans;
    for(int i = 0; i < n; i++) {
        int cur = q.front(); q.pop();
        ans.push_back(cur);
        for(int j : adjlist[cur]) {
            if(--degree[j] == 0) q.push(j);
        }
    }
    
    for(int i : ans) cout<<i+1<<" ";
}