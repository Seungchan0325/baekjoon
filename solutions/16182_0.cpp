#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int N, M, L[MAXN], R[MAXN], inDeg[MAXN], ans[MAXN];
vector<pair<int, int>> edges;
vector<int> graph[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> L[i] >> R[i];
    }
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
    }

    for(auto [u, v] : edges) {
        graph[u].push_back(v);
        inDeg[v]++;
    }
    queue<int> q;
    for(int i = 1; i <= N; i++) {
        if(inDeg[i] == 0) q.push(i);
    }

    for(int i = 1; i <= N; i++) {
        if(q.empty()) {
            cout << "-1\n";
            return 0;
        }

        auto u = q.front(); q.pop();
        for(auto v : graph[u]) {
            L[v] = max(L[v], L[u]+1);
            if(--inDeg[v] == 0) q.push(v);
        }
    }

    for(int i = 1; i <= N; i++) {
        graph[i].clear();
        inDeg[i] = 0;
    }

    for(auto [u, v] : edges) {
        graph[v].push_back(u);
        inDeg[u]++;
    }

    for(int i = 1; i <= N; i++) {
        if(inDeg[i] == 0) q.push(i);
    }

    for(int i = 1; i <= N; i++) {
        if(q.empty()) {
            cout << "-1\n";
            return 0;
        }

        auto u = q.front(); q.pop();
        for(auto v : graph[u]) {
            R[v] = min(R[v], R[u]-1);
            if(--inDeg[v] == 0) q.push(v);
        }
    }

    vector<tuple<int, int, int>> v;
    for(int i = 1; i <= N; i++) {
        v.emplace_back(L[i], R[i], i);
    }
    sort(v.begin(), v.end());

    priority_queue<pair<int, int>> pq;
    int idx = 0;
    for(int i = 1; i <= N; i++) {
        while(get<0>(v[idx]) <= i && idx < v.size()) {
            pq.emplace(-get<1>(v[idx]), get<2>(v[idx]));
            idx++;
        }

        if(pq.empty() || -pq.top().first < i) {
            cout << "-1\n";
            return 0;
        }

        ans[i] = pq.top().second;
        pq.pop();
    }

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}