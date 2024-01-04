#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int N;
ll ans = 0;
vector<ll> v;
vector<vector<int>> graph;

inline ll f(ll n) { return n*(n-1)/2; }

ll dfs(int cur) {
    v[cur] = 1;
    for(auto i : graph[cur]) {
        if(!v[i]) {
            v[cur] += dfs(i);
        }
    }
    ans += f(N) - f(N - v[cur]);
    return v[cur];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    v.resize(N);
    graph.resize(N);
    for(int i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(0);
    cout << ans - f(N) << "\n";
}