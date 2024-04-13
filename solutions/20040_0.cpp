#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int ans, n, m, root[MAXN];

int find(int u)
{
    if(u == root[u]) return u;
    return root[u] = find(root[u]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    iota(root, root + n + 1, 0);

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u = find(u);
        v = find(v);

        if(u == v) {
            ans = i;
            break;
        }

        root[v] = u;
    }

    cout << ans;
}