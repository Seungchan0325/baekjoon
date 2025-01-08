#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

struct DSU {
    vector<int> root;
    DSU(int n) : root(n)
    {
        iota(root.begin(), root.end(), 0);
    }
    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }
    void merge(int x, int y)
    {
        if(x > y) swap(x, y);
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

set<int> graph[101010];

int main()
{
    int n, c;
    cin >> n >> c;
    vector<int> pi(n, 0);
    for(int i = 1; i < n; i++) cin >> pi[i];

    DSU dsu(n);

    for (int i = 1; i < n; i++) {
        if(pi[i]-1 >= 0)
            dsu.merge(pi[i]-1, i);
    }

    ll ans = c;
    for (int i = 1; i < n; i++) {
        if (pi[i] > 0) continue;
        set<int> s;
        for (int j = pi[i - 1]; ; j = pi[j - 1]) {
            s.insert(dsu.find(j));
            if (j == 0) break;
        }
        ans *= c - (ll)s.size();
        ans %= MOD;
    }
    cout << ans << "\n";
}