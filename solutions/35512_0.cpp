#include <bits/stdc++.h>

using namespace std;

template<int MXL>
struct TWO_SAT
{
    int l, n, pv, t;
    vector<int> low, num, where;
    vector<vector<int>> g, scc;
    vector<char> inStack;
    stack<int> s;
    vector<bitset<2*MXL>> dp;
    void init(int _l, int _n)
    {
        l = _l;
        n = _n;
        pv = t = 0;
        low.resize(n<<1);
        num.resize(n<<1);
        where.resize(n<<1);
        g.resize(n<<1);
        inStack.resize(n<<1);
        dp.resize(n<<1);
    }
    void add(int a, int b)
    {
        g[a^1].push_back(b);
        g[b^1].push_back(a);
    }
    void add(int na, int a, int nb, int b)
    {
        // if(na) cout << "!";
        // cout << a << " or ";
        // if(nb) cout << "!";
        // cout << b << "\n";
        add(a<<1|na, b<<1|nb);
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
                low[u] = min(low[u], num[v]);
            }
        }

        if(low[u] == num[u]) {
            vector<int> comp;
            while(true) {
                auto v = s.top(); s.pop();
                inStack[v] = false;
                where[v] = t;
                comp.push_back(v);
                if(v == u) break;
            }
            scc.push_back(comp);
            t++;
        }
    }
    bool preprocess()
    {
        for(int i = 0; i < (n<<1); i++) {
            if(!num[i]) dfs(i);
        }
        for(int i = 0; i < n; i++) {
            if(where[i<<1] == where[i<<1|1]) {
                return false;
            }
        }
        return true;
    }
    vector<int> solve()
    {
        if(!preprocess()) return {};

        for(int i = t-1; i >= 0; i--) {
            for(int j : scc[i]) if(j < (l<<1)) dp[i].set(j);
            vector<int> nxt;
            for(int j : scc[i])
                for(int k : g[j])
                    nxt.push_back(where[k]);
            sort(nxt.begin(), nxt.end());
            nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
            for(auto j : nxt) {
                dp[j] |= dp[i];
            }
        }

        vector<int> res(n, -1);
        for(int i = 0; i < l; i++) {
            if(dp[where[i<<1|1]].test(i<<1)) res[i] = 0;
            else if(dp[where[i<<1]].test(i<<1|1)) res[i] = 1;
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int l, n;
    cin >> l >> n;
    vector<set<char>> sz(l);
    string when_true(l, '.');
    string when_false(l, '.');
    TWO_SAT<100> sat; sat.init(l, l+n);
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < l; j++) {
            if(s[j] == '.') continue;
            int k = l-j-1;
            if(when_true[j] == '.') when_true[j] = s[j];
            else if(when_true[j] != s[j] && when_false[j] == '.') when_false[j] = s[j];
            if(when_true[k] == '.') when_true[k] = s[j];
            else if(when_true[k] != s[j] && when_false[k] == '.') when_false[k] = s[j];

            if(when_true[j] == s[j]) sat.add(1, i+l, 0, j);
            else sat.add(1, j, 1, i+l);
            if(when_true[k] == s[j]) sat.add(0, i+l, 0, k);
            else sat.add(1, k, 0, i+l);
            sz[j].insert(s[j]);
            sz[k].insert(s[j]);
        }
        if((s[0] != '.' && isupper(s[0])) || (s[l-1] != '.' && islower(s[l-1]))) {
            sat.add(0, i+l, 0, i+l);
        } else if((s[0] != '.' && islower(s[0])) || (s[l-1] != '.' && isupper(s[l-1]))) {
            sat.add(1, i+l, 1, i+l);
        }
    }

    bool ok = true;
    for(int i = 0; i < l; i++) {
        if(i == l-i-1) {
            if(sz[i].size() >= 2) ok = false;
        }
        else {
            if(sz[i].size() >= 3) ok = false;
        }
    }

    if(!ok) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    auto val = sat.solve();
    if(val.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    string ans(l, '.');
    for(int i = 0; i < l; i++) {
        if(val[i] == -1) continue;
        if(val[i] == 1) ans[i] = when_true[i];
        else ans[i] = when_false[i];
    }
    cout << ans << "\n";
}
