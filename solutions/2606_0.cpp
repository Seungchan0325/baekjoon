#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
int n, k;
vector<vector<bool>> mat;
vector<bool> visited;

void dfs(int cur) {
    cnt++;
    visited[cur] = true;
    for(int i = 0; i < n; i++) 
        if(mat[cur][i] == true && visited[i] == false)
            dfs(i);
}

int main() {
    cin >> n >> k;
    mat.resize(n);
    visited.resize(n);
    for(auto& i : mat) 
        i.resize(n);
    
    for(int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        a-=1;b-=1;
        mat[a][b] = true;
        mat[b][a] = true;
    }
    dfs(0);
    cout << cnt-1;
}