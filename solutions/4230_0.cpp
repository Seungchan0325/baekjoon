#include <bits/stdc++.h>

using namespace std;

struct _2_SAT {
    int n, pv, t;
    vector<bool> inStack, chk;
    vector<int> low, num, scc;
    vector<vector<int>> g;
    stack<int> s;
    _2_SAT(int n) : n(n), g(2*n), inStack(2*n), chk(2*n), low(2*n), num(2*n), scc(2*n), t(0), pv(0)
    {
    }

    int CONV(int x)
    {
        return x<<1;
    }

    int NOT(int x)
    {
        return x^1;
    }

    void add(int nx, int x, int ny, int y)
    {
        x = CONV(x);
        y = CONV(y);
        if(nx) x = NOT(x);
        if(ny) y = NOT(y);
        g[NOT(x)].push_back(y);
        g[NOT(y)].push_back(x);
    }

    void dfs(int u)
    {
        num[u] = low[u] = ++pv;
        inStack[u] = true;
        s.push(u);

        for(auto v : g[u]) {
            if(!num[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if(inStack[v]) {
                low[u] = min(low[u], low[v]);
            }
        }

        if(num[u] == low[u]) {
            t++;
            while(s.top() != u) {
                scc[s.top()] = t;
                inStack[s.top()] = false;
                s.pop();
            }
            scc[u] = t;
            inStack[u] = false;
            s.pop();
        }
    }

    vector<int> run()
    {
        for(int i = 0; i < 2*n; i++) {
            if(!num[i]) dfs(i);
        }

        for(int i = 0; i < n; i++) {
            if(scc[CONV(i)] == scc[NOT(CONV(i))]) {
                return {-1};
            }
        }

        vector<pair<int, int>> v;
        for(int i = 0; i < 2*n; i++) {
            v.emplace_back(-scc[i], i);
        }
        sort(v.begin(), v.end());

        vector<int> ans;
        for(auto [_, i] : v) {
            if(!chk[i/2]) {
                if(i&1) ans.push_back(i/2);
                chk[i/2] = true;
            }
        }

        return ans;
    }
};

int main()
{
    while(true) {
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        _2_SAT tsat(2*n);
        tsat.add(0, n, 0, n);
        for(int i = 0; i < n; i++) {
            tsat.add(0, i, 0, i+n);
            tsat.add(1, i, 1, i+n);
        }
        for(int i = 0; i < m; i++) {
            int a, b;
            char w, h;
            cin >> a >> w >> b >> h;
            if(w == 'w') a += n;
            if(h == 'w') b += n;
            tsat.add(0, a, 0, b);
        }
        auto ans = tsat.run();
        if(ans[0] == -1) {
            cout << "bad luck\n";
            continue;
        }
        sort(ans.begin(), ans.end(), [&](int i, int j){
            if(i >= n) i -= n;
            if(j >= n) j -= n;
            return i < j;
        });
        for(auto i : ans) {
            if(i == 0 || i - n == 0) continue;
            if(i < n) cout << i << "h ";
            else cout << i - n << "w ";
        }
        cout << "\n";
    }
}