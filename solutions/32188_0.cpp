#include <bits/stdc++.h>

using namespace std;

int N, C, D[101010];
vector<pair<int, int>> s[101010];

int main()
{
    cin >> N >> C;
    for(int i = 0; i < N-1; i++) s[i].emplace_back(i+1, 1);
    for(int i = 0; i < C; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 0) {
            s[a].clear();
        }
        s[a].emplace_back(b, 0);
    }

    for(int i = 0; i < N; i++) D[i] = 1e9;

    deque<pair<int, int>> dq;
    D[0] = 0;
    dq.emplace_back(0, 0);
    while(!dq.empty()) {
        auto [now, t] = dq.front(); dq.pop_front();
        if(t > D[now]) continue;
        if(now == N-1) {
            cout << t;
            return 0;
        }
        for(auto [nxt, dt] : s[now]) {
            if(t + dt < D[nxt]) {
                D[nxt] = t + dt;
                if(dt == 0) dq.emplace_front(nxt, t + dt);
                else dq.emplace_back(nxt, t + dt);
            }
        }
    }
    cout << "-1";
}