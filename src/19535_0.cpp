#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int n;
vector<int> tree[MAXN];
int degree[MAXN];

int cnt_z = 0;
int cnt_y = 0;

void dfs(int u, int p) {
    if(1 < degree[p] && 1 < degree[u])
        cnt_z += (degree[p] - 1) * (degree[u] - 1);
    for(auto c : tree[u]) {
        if(c == p) continue;

        dfs(c, u);
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    dfs(0, -1);

    for(int i = 0; i < n; i++) {
        if(degree[i] < 3) continue;

        cnt_y += degree[i] * (degree[i] - 1) * (degree[i] - 2) / 6;
    }

    string output;
    if(cnt_z == 3*cnt_y) output = "DUDUDUNGA";
    else if(cnt_z > 3*cnt_y) output = "D";
    else output = "G";
    // cout << format("{} {}\n", cnt_z, cnt_y);
    cout << output;
}