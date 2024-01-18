#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<vector<int>> tree;

void solve() {
    vector<int> parent(N);
    vector<bool> visited(N);
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));

    while(!q.empty()) {
        auto front = q.front(); q.pop();

        parent[front.first] = front.second;
        
        for(auto& i : tree[front.first]) {
            if(!visited[i]) {
                q.push(make_pair(i, front.first));
                visited[i] = true;
            }
        }
    }

    for(int i = 1; i < N; i++) {
        cout << parent[i] + 1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    tree.resize(N);
    for(int i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        --a;--b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    solve();
}