#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100'005;

int N, Q, par[MAXN], c[MAXN], removed[MAXN], group[MAXN];
set<int> g[MAXN];
vector<map<int, int>> col;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> Q;
    for(int i = 2; i <= N; i++) {
        cin >> par[i];
        g[i].insert(par[i]);
        g[par[i]].insert(i);
    }
    col.push_back({});
    for(int i = 1; i <= N; i++) {
        cin >> c[i];
        col.back()[c[i]]++;
    }

    int lst = 0;
    Q += N - 1;
    while(Q--) {
        int x, k;
        cin >> x >> k;
        int a = lst ^ k;

        if(x == 1) {
            g[par[a]].erase(a);
            g[a].erase(par[a]);

            vector<int> v[2];
            queue<tuple<int, int, int>> q[2];
            q[0].emplace(a, 0, -1);
            q[1].emplace(par[a], 0, -1);

            while(!q[0].empty() && !q[1].empty()) {
                for(int i = 0; i < 2; i++) {
                    auto [u, p, pp] = q[i].front(); q[i].pop();
                    if(p == 0) v[i].push_back(u);
                    auto it = g[u].upper_bound(p);
                    if(it != g[u].end()) {
                        q[i].emplace(u, (*it), pp);
                        if(*it != pp) q[i].emplace(*it, 0, u);
                    }
                }
            }

            int i = 0;
            if(q[1].empty()) i = 1;

            int other = group[a];

            col.push_back({});

            for(auto u : v[i]) {
                if(--col[other][c[u]] == 0) col[other].erase(c[u]);

                group[u] = col.size() - 1;

                col[group[u]][c[u]]++;
            }
        } else {
            int result = col[group[a]].size();
            cout << result << "\n";
            lst = result;
        }
    }
}