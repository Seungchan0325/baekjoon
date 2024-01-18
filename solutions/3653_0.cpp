#include <bits/stdc++.h>

using namespace std;

int where[100005], tree[4*200005];

void update(int s, int e, int idx, int pos, int delta) {
    if(pos < s || e < pos) return;
    
    if(s == e) {
        tree[idx] += delta;
        return;
    }

    int mid = (s + e) / 2;
    update(s, mid, 2*idx, pos, delta);
    update(mid+1, e, 2*idx+1, pos, delta);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(int s, int e, int idx, int l, int r) {
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) return tree[idx];
    
    int mid = (s + e) / 2;
    return query(s, mid, 2*idx, l, r) + query(mid+1, e, 2*idx+1, l, r);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t; cin>>t;

    while(t--) {
        int n, m, nm;
        cin>>n>>m;
        nm = n + m;

        memset(tree, 0, sizeof(tree));
        for(int i=1; i<=n; i++) {
            where[i] = n-i+1;
            update(1, nm, 1, where[i], 1);
        }

        for(int i=1; i<=m; i++) {
            int a; cin>>a;

            int q = query(1, nm, 1, where[a]+1, nm);
            update(1, nm, 1, where[a], -1);
            where[a] = n + i;
            update(1, nm, 1, where[a], 1);

            cout<<q<<" ";
        }
        cout<<"\n";
    }
}