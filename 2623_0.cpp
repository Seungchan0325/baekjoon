#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<bool> visited;
vector<int> in_degree;
vector<vector<int>> graph;

void input() {
    cin >> N >> M;

    visited.resize(N);
    graph.resize(N);
    in_degree.resize(N);

    for(int i = 0; i < M; i++) {
        size_t size;
        int input1, input2;
        cin >> size;
        if(size == 0) continue;

        cin >> input1;
        input1--;
        if(size == 1) continue;
        for(int j = 0; j < size - 1; j++) {
            cin >> input2;
            input2--;
            graph[input1].push_back(input2);
            in_degree[input2]++;
            input1 = input2;
        }
    }
}

void solve() {
    vector<int> ans;
    queue<int> que;
    for(int i = 0; i < N; i++) {
        if(in_degree[i] == 0) {
            que.push(i);
        }
    }

    while(!que.empty()) {
        auto front = que.front(); que.pop();
        ans.push_back(front);

        for(auto& i : graph[front]) {
            in_degree[i]--;
            if(in_degree[i] == 0) {
                que.push(i);
            }
        }
    }

    if(ans.size() != N) {
        cout << "0\n";
        return;
    } else {
        for(int i = 0; i < N; i++) {
            cout << ans[i] + 1 << "\n";
        }
    }
}

int main() {    
    input();
    solve();
}