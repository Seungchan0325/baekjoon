#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int INF = 987654321;

int n, a[MAXN], fenwick[MAXN], seg[4*MAXN], lazy[4*MAXN];

int query(int i) {
    int ret = 0;
    while(i > 0) {
        ret += fenwick[i];
        i -= (i & -i);
    }
    return ret;
}

void update(int i, int v) {
    while(i <= n) {
        fenwick[i] += v;
        i += (i & -i);
    }
}

void propagation(int node, int s, int e) {
    if(lazy[node] != 0) {
        seg[node] += lazy[node];
        if(s != e) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(int s, int e, int node, int l, int r, int v) {
    propagation(node, s, e);
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        seg[node] += v;
        if(s != e) {
            lazy[2*node] += v;
            lazy[2*node+1] += v;
        }
        return;
    }

    int mid = (s + e) / 2;
    update_range(s, mid, 2*node, l, r, v);
    update_range(mid+1, e, 2*node+1, l, r, v);
    seg[node] = min(seg[2*node], seg[2*node+1]);
}

int query_range(int s, int e, int node, int l, int r) {
    propagation(node, s, e);
    if(r < s || e < l) return INF;

    if(l <= s && e <= r) {
        return seg[node];
    }

    int mid = (s + e) / 2;
    return min(query_range(s, mid, 2*node, l, r), query_range(mid+1, e, 2*node+1, l, r));
}

int main() {
    cin>>n;
    vector<int> v;
    for(int i=1; i<=n; i++) {
        cin>>a[i];
        v.push_back(a[i]);
    }
    
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i=1; i<=n; i++) {
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    }

    int sum = 0;
    for(int i=n; i>=1; i--) {
        sum += query(a[i] - 1);
        update(a[i], 1);
    }

    int s = 0;
    int e = n + 1;
    for(int i=1; i<=n; i++) {
        update_range(s, e, 1, a[i] + 1, e, 1);
    }
    for(int i=1; i<=n; i++) {
        update_range(s, e, 1, a[i] + 1, e, -1);
        int pre = query_range(s, e, 1, a[i], a[i]);
        int post = query_range(s, e, 1, s, e);
        cout<<sum - pre + post<<" ";
        update_range(s, e, 1, s, a[i] - 1, 1);
    }
}