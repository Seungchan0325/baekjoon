#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, X;
vector<bool> visited;
vector<vector<int>> better_than_me, worse_than_me;

int search(int n) {
    int cnt = 0;
    visited[n] = true;
    for(int i = 0; i < better_than_me[n].size(); i++) {
        if(visited[better_than_me[n][i]] == false) {
            cnt++;
            cnt += search(better_than_me[n][i]);
        }
    }
    return cnt;
}

int search1(int n) {
    int cnt = 0;
    visited[n] = true;
    for(int i = 0; i < worse_than_me[n].size(); i++) {
        if(visited[worse_than_me[n][i]] == false) {
            cnt++;
            cnt += search1(worse_than_me[n][i]);
        }
    }
    return cnt;
}

int main() {
    cin >> N >> M >> X;
    better_than_me.resize(N);
    worse_than_me.resize(N);
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        better_than_me[b].push_back(a);
        worse_than_me[a].push_back(b);
    }
    visited = vector<bool>(N);
    cout << search(X-1) + 1 << " ";
    visited = vector<bool>(N);
    cout << N - search1(X-1) << endl;
}