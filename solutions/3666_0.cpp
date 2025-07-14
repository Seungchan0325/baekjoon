#include <bits/stdc++.h>

using namespace std;

const int MAXN = 111;

const int inf = 1e9;

struct MF {
    int n;
    vector<vector<int>> c, f;
    void init(int _n)
    {
        n = _n;
        c = vector<vector<int>>(n, vector<int>(n));
    }
    
    void add_edge(int u, int v, int cap)
    {
        c[u][v] = cap;
    }

    int run(int s, int t)
    {
        f = vector<vector<int>>(n, vector<int>(n));
        int ans = 0;
        while(true) {
            vector<int> par(n, -1);
            queue<int> q;
            par[s] = s;
            q.push(s);
            while(!q.empty()) {
                int u = q.front(); q.pop();
                for(int v = 0; v < n; v++) {
                    if(c[u][v] - f[u][v] > 0 && par[v] == -1) {
                        par[v] = u;
                        q.push(v);
                    }
                }
            }
            if(par[t] == -1) break;

            int flow = inf;
            for(int i = t; i != s; i = par[i]) {
                flow = min(flow, c[par[i]][i] - f[par[i]][i]);
            }

            for(int i = t; i != s; i = par[i]) {
                f[par[i]][i] += flow;
                f[i][par[i]] -= flow;
            }

            ans += flow;
        }

        return ans;
    }
};

int main()
{
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        int s = 2*n;
        int e = 2*n+1;

        int target = 0;

        MF mf; mf.init(2*n+2);
        for(int i = 0; i < n; i++) {
            if(a[i]) {
                mf.add_edge(i, i+n, inf);
                mf.add_edge(s, i, a[i]);
                mf.add_edge(i+n, e, 1);
                target++;
            }
        }

        vector<int> weak;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                char c; cin >> c;
                if(c == 'Y') {
                    if(a[i] && a[j]) {
                        mf.add_edge(i, j+n, inf);
                    } else if(a[i]) {
                        weak.push_back(i);
                    }
                }
            }
        }
        weak.erase(unique(weak.begin(), weak.end()), weak.end());

        int lo = 0;
        int hi = 10101;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            for(auto i : weak) mf.add_edge(i+n, e, mid), target += mid-1;
            if(mf.run(s, e) == target) lo = mid;
            else hi = mid;
            for(auto i : weak) mf.add_edge(i+n, e, mid), target -= mid-1;
        }
        cout << lo << "\n";
    }
}