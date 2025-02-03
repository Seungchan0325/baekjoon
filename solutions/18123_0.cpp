#include <bits/stdc++.h>

using namespace std;

using u64 = unsigned long long;

struct Tree {
    int n, sz[33];
    vector<int> g[33];
    vector<int> cent;
    void add_edge(int u, int v)
    {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int p)
    {
        sz[u] = 1;
        for(auto v : g[u]) {
            if(v == p) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }

    void get_cent(int u, int p)
    {
        bool is_cent = true;
        for(auto v : g[u]) {
            if(v == p) continue;
            if(2*sz[v] >= n) get_cent(v, u);
            if(2*sz[v] > n) is_cent = false;
        }
        if(2*(n-sz[u]) > n) is_cent = false;
        if(is_cent) {
            cent.push_back(u);
        }
    }

    pair<u64, int> compute_key(int u, int p)
    {
        vector<pair<u64, int>> keys;
        for(auto v : g[u]) {
            if(v == p) continue;
            keys.emplace_back(compute_key(v, u));
        }
        sort(keys.begin(), keys.end());
        u64 ret = 0;
        int s = 0;
        for(auto [k, len] : keys) {
            ret |= k<<s;
            s += len;
        }
        ret <<= 1;
        ret |= 1;
        s += 2;
        return {ret, s};
    }

    pair<u64, int> get_key()
    {
        dfs(0, -1);
        get_cent(0, -1);

        vector<pair<u64, int>> keys;
        for(auto c : cent) {
            keys.push_back(compute_key(c, -1));
        }
        sort(keys.begin(), keys.end());
        return keys.front();
    }

    bool operator < (Tree& rhs) {
        if(n != rhs.n) return n < rhs.n;
        return get_key() < rhs.get_key();
    }
    
    bool operator == (Tree& rhs) {
        return n == rhs.n && get_key() == rhs.get_key();
    }
};

const int MAXN = 1010101;

int n;

int main()
{
    cin >> n;
    vector<pair<u64, int>> keys;
    for(int i = 0; i < n; i++) {
        Tree t;
        cin >> t.n;
        for(int j = 1; j < t.n; j++) {
            int u, v;
            cin >> u >> v;
            t.add_edge(u, v);
        }
        keys.push_back(t.get_key());
    }
    sort(keys.begin(), keys.end());
    keys.erase(unique(keys.begin(), keys.end()), keys.end());
    cout << keys.size();
}