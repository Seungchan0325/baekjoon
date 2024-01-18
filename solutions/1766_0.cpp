#include <iostream>
#include <algorithm>   
#include <vector>
#include <queue>

using namespace std;

constexpr std::size_t MAX_N = 32e3;

int N, M;
int in_degree[MAX_N+1] = {0};
vector<int> graph[MAX_N+1];

void solve() {
    priority_queue<int, vector<int>, greater<int>> que;

    for(int i = 1; i <= N; i++)
        if(in_degree[i] == 0)
            que.push(i);
    
    while(!que.empty()) {
        int cur = que.top(); que.pop();
        cout<<cur<<" ";

        for(auto& i : graph[cur]) {
            in_degree[i]--;

            if(in_degree[i] == 0)
                que.push(i);
        }
    }
}

int main() {
    cin>>N>>M;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin>>a>>b;
        in_degree[b]++;
        graph[a].push_back(b);
    }

    solve();
}