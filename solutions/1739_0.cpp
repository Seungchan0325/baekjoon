#include <bits/stdc++.h>

using namespace std;

int n, m, k, pv, t;

stack<int> s;
set<int> chk;
map<int, vector<int>> g;
map<int, int> num, low, scc, inStack;

void add(int a, int na, int b, int nb)
{
    a<<=1;
    b<<=1;
    a^=na;
    b^=nb;
    g[a^1].push_back(b);
    g[b^1].push_back(a);
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

void solve()
{
    pv = 0;
    t = 0;
    while(s.size()) s.pop();
    low.clear(); num.clear(); scc.clear(); inStack.clear();
    g.clear();
    chk.clear();

    cin >> n >> m >> k;
    
    for(int i = 0; i < k; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2; x1--; y1--; x2--; y2--;
        if(x1 == x2 && y1 == y2) continue;
        chk.insert(4*n*m+x1);
        chk.insert(4*n*m+x2);
        chk.insert(4*n*m+n+y1);
        chk.insert(4*n*m+n+y2);
        if(x1 == x2) {
            int x0 = 4*n*m+x1;
            if(y1 < y2) add(x0, 1, x0, 1);
            if(y1 > y2) add(x0, 0, x0, 0);
        } else if(y1 == y2) {
            int y0 = 4*n*m+n+y1;
            if(x1 < x2) add(y0, 1, y0, 1);
            if(x1 > x2) add(y0, 0, y0, 0);
        } else {
            int a = 4*(m*x1+y2);
            int b = 4*(m*x2+y1);
            if(y1 > y2) a+=2, b+=2;
            if(x1 > x2) a+=1, b+=1;
            chk.insert(a);
            chk.insert(b);
            add(a, 0, b, 0);
        }
    }
    for(int x = 0; x < n; x++) {
        for(int y = 0; y < m; y++) {
            int base = 4*(m*x+y);

            int x0 = 4*n*m+x;
            int y0 = 4*n*m+n+y;

            if(chk.contains(base)) {
                add(base, 1, x0, 1);
                add(base, 1, y0, 1);
            }

            if(chk.contains(base+1)) {
                add(base+1, 1, x0, 1);
                add(base+1, 1, y0, 0);
            }
            
            if(chk.contains(base+2)) {
                add(base+2, 1, x0, 0);
                add(base+2, 1, y0, 1);
            }
        
            if(chk.contains(base+3)) {
                add(base+3, 1, x0, 0);
                add(base+3, 1, y0, 0);
            }
        }
    }

    for(auto i : chk) {
        if(!num[i<<1]) dfs(i<<1);
        if(!num[i<<1|1]) dfs(i<<1|1);
    }
    
    for(auto i : chk) {
        if(scc[i<<1] == scc[i<<1|1]) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while(t--) solve();
}