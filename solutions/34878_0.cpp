#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;

bool isLeaf[MAXN], inQ[MAXN];
int n, m, deg[MAXN], leaves, preLeaf[MAXN];
vector<int> g[MAXN], gp[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        leaves = 0;
        for(int i = 0; i <= n; i++) {
            inQ[i] = false;
            isLeaf[i] = false;
            preLeaf[i] = 0;
            deg[i] = 0;
            g[i].clear();
            gp[i].clear();
        }
        for(int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            g[u].push_back(v); deg[v]++;
            gp[v].push_back(u);
        }
        for(int i = 1; i <= n; i++) {
            g[0].push_back(i); deg[i]++;
            gp[i].push_back(0);
        }

        multiset<int> s;
        queue<int> q;
        q.push(0);
        inQ[0] = true;
        s.insert(preLeaf[0]);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            inQ[u] = false;
            s.erase(s.find(preLeaf[u]));
            isLeaf[u] = true;
            leaves++;
            for(auto v : g[u]) {
                preLeaf[v]++;
                if(--deg[v] == 0) {
                    q.push(v);
                    inQ[v] = true;
                    s.insert(preLeaf[v]);
                }
            }
            for(auto v : gp[u]) {
                if(isLeaf[v]) {
                    leaves--;
                    isLeaf[v] = false;
                    for(auto k : g[v]) {
                        preLeaf[k]--;
                        if(inQ[k]) {
                            s.erase(s.find(preLeaf[k]+1));
                            s.insert(preLeaf[k]);
                        }
                    }
                }
            }

            if(u == 0) continue;

            if(s.empty() || *s.begin() >= leaves) cout << "1";
            else cout << "0";
        }
        cout << "\n";
    }
}