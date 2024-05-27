#include <bits/stdc++.h>

using namespace std;

bool erased[3005], adjmat[3005][3005];
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adjmat[u][v] = adjmat[v][u] = true;
    }

    for(int u = 1; u <= n; u++) {
        if(erased[u]) continue;
        for(int v = u+1; v <= n; v++) {
            if(!erased[v] && !adjmat[u][v]) {
                erased[u] = erased[v] = true;
                break;
            }
        }
    }

    int cnt = 0;
    for(int u = 1; u <= n; u++) {
        if(!erased[u] && cnt < n/3) cout << u << " ", cnt++;
    }

    assert(cnt == n/3);
}