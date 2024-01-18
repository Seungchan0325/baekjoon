#include <iostream>
#include <vector>

using namespace std;

int n, m, max_size;
vector<bool> visited;
vector<int> sizes;
vector<vector<int>> adjList;

int search(int cur) {
    int cnt = 0;
    visited[cur] = true;
    for(auto& i : adjList[cur]) {
        if(visited[i] == false) {
            cnt++;
            cnt += search(i);
        }
    }
    return cnt;
}

int main() {
    cin >> n >> m;
    adjList.resize(n);
    sizes.resize(n);

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        adjList[b].push_back(a);
    }

    for(int i = 0; i < n; i++) {
        visited = vector<bool>(n, false);
        sizes[i] = search(i);
        if(max_size < sizes[i]) max_size = sizes[i];
    }

    for(int i = 0; i < n; i++)
        if(sizes[i] == max_size)
            cout << i + 1 << " ";
}