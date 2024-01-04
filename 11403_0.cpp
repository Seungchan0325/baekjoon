#include <iostream>
#include <vector>

using namespace std;

int n, current;
vector<vector<int>> mat, ans;  //ans = visited겸 답

void dfs(int cur) {
    ans[current][cur] = 1;

    for(int i = 0; i < n; i++)
        if(mat[cur][i] == 1 && ans[current][i] == 0)
            dfs(i);
}

int main() {
    cin >> n;
    mat.resize(n, vector<int>(n));
    ans.resize(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> mat[i][j];

    for(int i = 0; i < n; i++) {
        current = i;
        for(int i = 0; i < n; i++)
            if(mat[current][i] == 1)
                dfs(i);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}