#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

bool visited[2][MAXN];
bool DP[MAXN];
int N, K, X[MAXN], dep[MAXN], root[MAXN], sz[MAXN];
vector<int> mn, mx;

int find(int u)
{
    if(root[u] == u) return u;
    return root[u] = find(root[u]);
}

void merge(int u, int v)
{
    u = find(u);
    v = find(v);
    if(u == v) return;
    root[v] = u;
    sz[u] += sz[v];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    iota(root, root + N + 1, 0);
    fill(sz, sz + N + 1, 1);
    for(int i = 1; i <= N; i++) {
        cin >> X[i];
        merge(i, X[i]);
    }

    for(int i = 1; i <= N; i++) {
        if(!visited[0][find(i)]) {
            visited[0][find(i)] = true;
            visited[1][i] = true;

            int u = i;
            dep[u] = 0;
            while(!visited[1][X[u]]) {
                dep[X[u]] = dep[u] + 1;
                u = X[u];
                visited[1][u] = true;
            }
            mn.push_back(dep[u] - dep[X[u]] + 1);
            mx.push_back(sz[find(i)]);
        }
    }

    DP[0] = true;
    for(int i = 0; i < mn.size(); i++) {
        int l = N - mx[i] + 1, r = N - mn[i] + 1, cnt = 0;
        for(int j = l; j <= r; j++) {
            if(DP[j]) cnt++;
        }
        for(int j = N; j >= mn[i]; j--) {
            if(0 < l && DP[--l]) cnt++; 
            if(DP[r--]) cnt--;

            if(cnt) DP[j] = true;
        }
    }

    for(int i = K; i >= 0; i--) {
        if(DP[i]) {
            cout << i;
            break;
        }
    }
}