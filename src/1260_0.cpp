#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<bool>> mat;
vector<bool> visited;
int n, m, v;

void dfs(int cur) {
    cout << cur + 1 << " ";
    visited[cur] = true;

    for(int i = 0; i < n; i++)
        if(mat[cur][i] == true && visited[i] == false)
            dfs(i);
}

void bfs(int root) {
    queue<int> que;
    que.push(root);
    visited[root] = true;

    while(!que.empty()) {
        int cur = que.front();
        que.pop();
        cout << cur + 1 << " ";
        for(int i = 0; i < n; i++) {
            if(visited[i] == false && mat[cur][i] == true) {
                que.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    cin >> n >> m >> v;
    mat.resize(n);
    for(auto& i : mat)
        i.resize(n);
    visited.resize(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        mat[a][b] = true;
        mat[b][a] = true;
    }
    dfs(v-1);
    cout << "\n";
    fill(visited.begin(), visited.end(), 0);
    bfs(v-1);
}