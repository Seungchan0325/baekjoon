#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

// 14267 - 회사 문화 1
int n, m;
vector<vector<int>> graph;
vector<int> praise;

void input(){
    cin >> n >> m;
    graph.assign(n + 1, vector<int> (0, 0));
    praise.assign(n + 1, 0);

    for(int i = 1; i <= n; i++){
        int superior;
        cin >> superior;
        if(superior != -1)  graph[superior].emplace_back(i);
    }

    for(int i = 0; i < m; i++){
        int person, credit;
        cin >> person >> credit;
        praise[person] += credit;
    }
}

void DFS(int cur){
    for(int i = 0; i < graph[cur].size(); i++){
        int next = graph[cur][i];
        praise[next] += praise[cur];
        DFS(next);
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    input();

    DFS(1);
    for(int i = 1; i <= n; i++){
        cout << praise[i] << " ";
    }

    return 0;
}