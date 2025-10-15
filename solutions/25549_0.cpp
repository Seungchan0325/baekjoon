#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int N, P[MAXN], V[MAXN], M[MAXN];
vector<int> G[MAXN];
set<int> S[MAXN];

void dfs(int u)
{
    S[u].insert(V[u]);
    for(auto v : G[u]) {
        dfs(v);
        if(S[u].size() < S[v].size()) swap(S[u], S[v]);
        S[u].insert(S[v].begin(), S[v].end());
        M[u] = max(M[u], M[v]);
    }
    while(S[u].contains(M[u])) M[u]++;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> P[i];
        if(P[i] != -1) G[P[i]].push_back(i);
    }
    for(int i = 1; i <= N; i++) cin >> V[i];
    int root = 1;
    while(P[root] != -1) root = P[root];
    dfs(root);
    for(int i = 1; i <= N; i++) cout << M[i] << "\n";
}