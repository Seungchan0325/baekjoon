#include <iostream>
#include <memory.h>
#include <vector>

using namespace std;

int n, m, visited[101], cache[101][101];
vector<int> adj[101];

bool IsBigger(int src, int dst) {
    if(src == dst) return true;

    int& ret = cache[src][dst];
    if(ret != -1) return ret;

    ret = false;
    visited[src] = true;

    for(int i:adj[src])
        if(!visited[i])
            if(IsBigger(i, dst)) {
                ret = true;
                break;
            }
    
    visited[src] = false;
    return ret;
}

int main() {
    cin>>n>>m;
    for(int i=0; i<m; i++) {
        int a, b;
        cin>>a>>b;
        adj[a].push_back(b);
    }

    memset(cache, -1, sizeof(cache));

    for(int i=1; i<=n; i++) {
        int cnt=0;
        for(int j=1; j<=n; j++)
            if(!IsBigger(i, j) && !IsBigger(j, i))
                cnt++;
        cout<<cnt<<endl;
    }
}