#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n, in_deg[MAXN];

int main() {
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        in_deg[u]++; in_deg[v]++;
    }

    int cnt_leaf = 0;
    for(int i = 0; i < n; i++) {
        if(in_deg[i] == 1) cnt_leaf++;
    }

    cout << (cnt_leaf+1) / 2;
}