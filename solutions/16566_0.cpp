#include <bits/stdc++.h>

using namespace std;

int n, m, k, xs[4000000], roots[4000000];

int find(int x) {
    if(x == roots[x]) return x;
    else return roots[x] = find(roots[x]);
}

void Union(int x, int y) {
    x = find(x);
    y = find(y);

    if(x < y) swap(x, y);
    roots[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m>>k;
    for(int i = 0; i < m; i++) cin>>xs[i];

    sort(xs, xs + m);
    for(int i = 0; i < m; i++) roots[i] = i;

    for(int i = 0; i < k; i++) {
        int ys; cin>>ys;

        int idx = upper_bound(xs, xs + m, ys) - xs;
        idx = find(idx);

        cout<<xs[idx]<<"\n";
        Union(idx, idx + 1);
    }
}