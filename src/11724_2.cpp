#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;

vector<vector<bool>> mat;
vector<bool> visited;

int dfs(int cur) {
    int flag = 0;
    visited[cur] = true;
    
    for(int i=0;i<n;i++) {
        if(mat[cur][i] == true && visited[i] == false) {
            flag = 1;
            dfs(i);
        }
    }
    return flag;
}

int main() {
    int cnt = 0;
    cin >> n >> m;

    mat.resize(n);
    for_each(mat.begin(), mat.end(), [](vector<bool>& i) {
        i.resize(n);
    });
    visited.resize(n);

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        
        mat[a][b] = true;
        mat[b][a] = true;
    }

    for(int i=0;i<n;i++) {
        if(visited[i] == false){
            cnt++;
            dfs(i);
        }
    }
    cout << cnt << endl;
} 