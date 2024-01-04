#include <bits/stdc++.h>

using namespace std;

const pair<int, int> dir[] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};

int n, m;

bool in_range(int i, int n) {
    return 0 <= i && i < n;
}

int f(vector<vector<int>> arr) {
    queue<pair<int, int>> que;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(arr[i][j] == 2)
                que.push({i, j});

    while(!que.empty()) {
        auto [i, j] = que.front(); que.pop();
        
        for(int idx = 0; idx < 4; idx++) {
            int ni = i + dir[idx].first;
            int nj = j + dir[idx].second;

            if(!in_range(ni, n) || !in_range(nj, m)) continue;

            if(arr[ni][nj] != 0) continue;

            que.push({ni, nj});
            arr[ni][nj] = 2;
        }
    }

    int cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(arr[i][j] == 0)
                cnt++;
    
    return cnt;
}

int dfs(vector<vector<int>>& arr, int depth) {
    if(depth >= 3) {
        return f(arr);
    }

    int ret = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            if(arr[i][j] != 0) continue;
            arr[i][j] = 1;
            ret = max(dfs(arr, depth + 1), ret);
            arr[i][j] = 0;
        }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<vector<int>> arr(10, vector<int>(10));
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> arr[i][j];
    cout << dfs(arr, 0);
}