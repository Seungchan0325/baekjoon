#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, K, T, A[MAXN], dp[MAXN], in[MAXN], q[2*MAXN], l, r;
vector<int> g[MAXN];

void push(int x)
{
    q[r++] = x;
}

int pop()
{
    return q[l++];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> T;
    vector<pair<int, int>> edges(K);
    for(auto& [u, v] : edges) cin >> u >> v;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(auto [u, v] : edges) {
        if(A[u] > A[v]) swap(u, v);
        g[u].push_back(v);
        in[v]++;
    }
    for(int i = 1; i <= N; i++) sort(g[i].begin(), g[i].end());
    for(int i = 1; i <= N; i++) {
        int s;
        cin >> s;
        if(s == -1) continue;
        auto it = lower_bound(g[i].begin(), g[i].end(), s);
        rotate(g[i].begin(), it, g[i].end());
    }

    int top = -1;
    for(int i = 1; i <= N; i++) {
        if(A[i] == 1) {
            top = i;
        }
        if(in[i] == 0) {
            push(i);
        }
    }
    dp[top] = T - 1;
    
    while(l != r) {
        int now = pop();
        int m = g[now].size();
        for(int i = 0; i < m; i++) {
            int nxt = g[now][i];
            dp[nxt] += dp[now] / m + (i < dp[now] % m);
            if(--in[nxt] == 0) {
                push(nxt);
            }
        }
    }

    int u = top;
    while(!g[u].empty()) {
        int m = g[u].size();
        u = g[u][dp[u]%m];
    }
    cout << u;
}