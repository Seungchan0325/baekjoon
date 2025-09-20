#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int N, A[MAXN], B[MAXN], C[MAXN];
bool vis[2*MAXN];
vector<int> g[2*MAXN];
int owner[MAXN];

bool dfs(int u)
{
    vis[u] = true;
    for(auto v : g[u]) {
        if(owner[v] == -1 || (!vis[owner[v]] && dfs(owner[v]))) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(tie(A[i], B[i], C[i]) < tie(A[j], B[j], C[j])) swap(A[i], A[j]), swap(B[i], B[j]), swap(C[i], C[j]);
        }
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j < i; j++) {
            if(A[i] >= A[j] && B[i] >= B[j] && C[i] >= C[j]) {
                g[i<<1].push_back(j);
                g[i<<1|1].push_back(j);
            }
        }
    }
    int ans = 0;
    memset(owner, -1, sizeof(owner));
    for(int i = 2; i <= (N<<1|1); i++) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)) {
            ans++;
        }
    }
    cout << N - ans << "\n";
}