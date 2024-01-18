#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 500005;

int n, a[MAXN], tree[4*MAXN];
pair<int, int> b[MAXN];

void init(int s, int e, int node) {
    if(s == e) {
        tree[node] = 1;
        return;
    }

    int mid = (s + e) / 2;
    init(s, mid, 2*node);
    init(mid+1, e, 2*node+1);
    tree[node] = tree[2*node] + tree[2*node+1];
}

void update(int s, int e, int node, int i, int v) {
    if(i < s || e < i) return;

    if(s == e) {
        tree[node] = v;
        return;
    }

    int mid = (s + e) / 2;
    update(s, mid, 2*node, i, v);
    update(mid+1, e, 2*node+1, i, v);
    tree[node] = tree[2*node] + tree[2*node+1];
}

int query(int s, int e, int node, int l, int r) {
    if(r < s || e < l) return 0;
    
    if(l <= s && e <= r) {
        return tree[node];
    }
    
    int mid = (s + e) / 2;
    return query(s, mid, 2*node, l, r) + query(mid+1, e, 2*node+1, l, r);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) cin>>a[i];
    for(int i=0; i<n; i++) { 
        cin>>b[i].first;
        b[i].second = i;
    }

    sort(b, b + n);

    init(0, n-1, 1);
    ll sum = 0;
    for(int i=0; i<n; i++) {
        int r = lower_bound(b, b + n, make_pair(a[i], 0))->second;
        update(0, n-1, 1, r, 0);
        sum += query(0, n-1, 1, 0, r);
    }

    cout<<sum;
}