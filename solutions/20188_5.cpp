#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

constexpr int INF = 987654321;

int N;

vector<vector<bool>> graph;

void MergeVisited(vector<bool>& visited1, vector<bool>& visited2) {
    for(int i = 0; i < visited1.size(); i++)
        if(visited2[i])
            visited1[i] = true;
}

void GetShortPathes(int cur, int depth, int& min_distance, vector<bool>& visited, vector<bool>& short_pathes) {
    visited[cur] = true;

    if(cur == 0) {
        if(depth < min_distance) {
            fill(short_pathes.begin(), short_pathes.end(), 0);
            MergeVisited(short_pathes, visited);
        }
        if(depth == min_distance) {
            MergeVisited(short_pathes, visited);
        }
        return;
    }

    if(depth > min_distance) return;

    for(int i = 0; i < N; i++)
        if(graph[cur][i] && !visited[i])
            GetShortPathes(i, depth + 1, min_distance, visited, short_pathes);

    visited[cur] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    graph.resize(N, vector<bool>(N));

    for(int i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a][b] = true; 
        graph[b][a] = true;
    }

    int cnt = 0;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            int min_distance1 = INF, min_distance2 = INF;
            vector<bool> visited1(N), visited2(N), short_pathes1(N), short_pathes2(N);
            GetShortPathes(i, 0, min_distance1, visited1, short_pathes1);
            GetShortPathes(j, 0, min_distance2, visited2, short_pathes2);

            for(int i = 0; i < N; i++)
                if(short_pathes1[i] || short_pathes2[i])
                    ++cnt;
            cnt--;
        }
    }

    cout << cnt << endl;
}