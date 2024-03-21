#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

bool visited[MAXN];
int N, edges;
vector<int> g[MAXN];

int dfs(int u)
{
    visited[u] = true;
    int ret = 1;
    for(auto v : g[u]) {
        if(visited[v]) continue;
        ret += dfs(v);
    }
    return ret;
}

int main()
{
    cin >> N;
    if(N <= 1) {
        cout << 0;
        return 0;
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char c; cin >> c;
            if(c == 'Y') {
                edges++;
                g[i].push_back(j);
            }
        }
    }
    edges >>= 1;
    
    int szsum = 0;
    vector<int> sz;
    for(int i = 0; i < N; i++) {
        if(visited[i]) continue;;
        sz.push_back(dfs(i));
        if(sz.back() == 1) goto FAILED;
        szsum += sz.back();
    }

    if(edges < szsum - 1) goto FAILED;
    cout << sz.size() - 1;
    return 0;
FAILED:
    cout << "-1";
    return 0;
}