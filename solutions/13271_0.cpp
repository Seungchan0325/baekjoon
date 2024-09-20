#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 1005;

int N, K, S[MAXN];
vector<tuple<int, int, int>> edges;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        edges.emplace_back(0, i, 100);
        edges.emplace_back(i, 0, 0);
    }
    for(int i = 1; i <= K; i++) {
        int op, a, b, c;
        cin >> op >> a >> b >> c;
        if(op == 1) {
            edges.emplace_back(a, b, -c);
        } else if(op == 2) {
            edges.emplace_back(b, a, c);
        } else if(op == 3) {
            edges.emplace_back(a, b, -c);
            edges.emplace_back(b, a, c);
        }
    }

    fill(S, S + N + 1, INF);
    S[0] = 0;
    for(int i = 0; i <= N; i++) {
        for(auto [u, v, w] : edges) {
            if(S[u] >= INF) continue;
            if(S[u] + w < S[v]) {
                S[v] = S[u] + w;
            }
        }
    }

    for(auto [u, v, w] : edges) {
        if(S[u] >= INF) continue;
        if(S[u] + w < S[v]) {
            cout << "-1";
            return 0;
        }
    }

    int mn = 100;
    for(int i = 1; i <= N; i++) {
        mn = min(mn, S[i]);
    }
    cout << 100 - mn;
}