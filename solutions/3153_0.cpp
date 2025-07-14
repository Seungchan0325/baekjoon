#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

struct TWO_SAT {
    int n, pv, t;
    vector<vector<int>> g;
    vector<int> low, num, inStack, scc;
    stack<int> s;
    void init(int _n)
    {
        n = _n;
        g.resize(2*n);
        low.resize(2*n);
        num.resize(2*n);
        inStack.resize(2*n);
        scc.resize(2*n);
    }

    void add(int na, int a, int nb, int b)
    {
        a<<=1; b<<=1;
        a^=na; b^=nb;
        g[a^1].push_back(b);
        g[b^1].push_back(a);
    }

    void dfs(int u)
    {
        low[u] = num[u] = ++pv;
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

        if(low[u] == num[u]) {
            t++;
            while(s.top() != u) {
                scc[s.top()] = t;
                inStack[s.top()] = false;
                s.pop();
            }
            scc[s.top()] = t;
            inStack[s.top()] = false;
            s.pop();
        }
    }

    vector<int> run()
    {
        for(int i = 0; i < 2*n; i++) {
            if(!num[i]) dfs(i);
        }

        for(int i = 0; i < n; i++) {
            if(scc[i<<1] == scc[i<<1|1]) return {};
        }

        vector<pair<int, int>> v;
        for(int i = 0; i < 2*n; i++) {
            v.emplace_back(-scc[i], i);
        }

        vector<int> ans(n, -1);
        sort(v.begin(), v.end());
        for(auto [_, i] : v) {
            if(ans[i/2] != -1) continue;
            ans[i/2] = i&1;
        }

        return ans;
    }
};

int n, m, towers, jaehyeok, tidx[MAXN][MAXN], table[2][2][2][2];
char company[MAXN][MAXN];

int find_tower(int i, int j, int di, int dj)
{
    i += di;
    j += dj;
    while(0 < i && i <= n && 0 < j && j <= m) {
        if(company[i][j] == '#') break;
        if(company[i][j] == 'T') return tidx[i][j];
        i += di;
        j += dj;
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> company[i][j];
            if(company[i][j] == 'T') {
                tidx[i][j] = towers;
                towers++;
            }
        }
    }

    table[0][0][1][1] = 1;
    table[0][1][1][0] = 2;
    table[1][1][0][0] = 3;
    table[1][0][0][1] = 4;

    TWO_SAT sat; sat.init(4*towers);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(company[i][j] == 'T') {
                int up = 4*tidx[i][j];
                int ri = 4*tidx[i][j]+1;
                int dw = 4*tidx[i][j]+2;
                int lf = 4*tidx[i][j]+3;
                sat.add(0, up, 0, dw);
                sat.add(1, up, 1, dw);
                sat.add(0, lf, 0, ri);
                sat.add(1, lf, 1, ri);
                if(find_tower(i, j, -1, 0) != -1) sat.add(1, up, 1, up);
                if(find_tower(i, j, 0, 1) != -1) sat.add(1, ri, 1, ri);
                if(find_tower(i, j, 1, 0) != -1) sat.add(1, dw, 1, dw);
                if(find_tower(i, j, 0, -1) != -1) sat.add(1, lf, 1, lf);
            } else if(company[i][j] == 'n') {
                int up = 4*find_tower(i, j, -1, 0)+2;
                int ri = 4*find_tower(i, j, 0, 1)+3;
                int dw = 4*find_tower(i, j, 1, 0);
                int lf = 4*find_tower(i, j, 0, -1)+1;
                if(up >= 0 && dw >= 0) sat.add(1, up, 1, up), sat.add(1, up, 1, up);
                if(lf >= 0 && ri >= 0) sat.add(1, lf, 1, lf), sat.add(1, ri, 1, ri);

                int ver = max(up, dw);
                int hor = max(lf, ri);
                if(ver >= 0 && hor >= 0) sat.add(0, ver, 0, hor);
                else sat.add(0, max(ver, hor), 0, max(ver, hor));
            }
        }
    }

    auto solution = sat.run();

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(company[i][j] != 'T') {
                cout << company[i][j];
                continue;
            }
            int up = solution[4*tidx[i][j]];
            int ri = solution[4*tidx[i][j]+1];
            int dw = solution[4*tidx[i][j]+2];
            int lf = solution[4*tidx[i][j]+3];
            cout << table[up][ri][dw][lf];
        }
        cout << "\n";
    }
}