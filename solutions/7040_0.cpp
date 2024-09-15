#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;
const int MAXN = 1005;

int N, ML, MD, D[MAXN];
vector<tuple<int, int, int>> edges;

int main()
{
    cin >> N >> ML >> MD;
    for(int i = 1; i <= ML; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }
    for(int i = 1; i <= MD; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(b, a, -c);
    }

    for(int i = 2; i <= N; i++) {
        edges.emplace_back(i, i-1, 0);
    }

    fill(D, D + N + 1, INF);
    D[1] = 0;
    for(int i = 0; i < N; i++) {
        for(auto [u, v, w] : edges) {
            if(D[u] >= INF) continue;
            if(D[u] + w < D[v]) {
                D[v] = D[u] + w;
            }
        }
    }

    for(auto [u, v, w] : edges) {
        if(D[u] >= INF) continue;
        if(D[u] + w < D[v]) {
            cout << "-1";
            return 0;
        }
    }

    if(D[N] >= INF) {
        cout << "-2";
        return 0;
    }

    cout << D[N];
}