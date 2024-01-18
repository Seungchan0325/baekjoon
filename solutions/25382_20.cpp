#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 250005;

struct Base {
    int idx;
    int x, y;
    int a, b;

    bool operator<(const Base& other) {
        return x < other.x;
    }
};

int n, days[MAXN], roots[MAXN], seg[4*MAXN];
Base bases[MAXN];

int find(int x) {
    if(roots[x] == x) return x;
    return roots[x] = find(roots[x]);
}

void Union(int x, int y) {
    x = find(x);
    y = find(y);

    roots[y] = x;
}

void update(int s, int e, int node, int i, int v) {
    if(i < s || e < i) return;

    if(s == e) {
        seg[node] = v;
        return;
    }

    int mid = (s + e) / 2;
    update(s, mid, 2*node, i, v);
    update(mid+1, e, 2*node+1, i, v);
    seg[node] = max(seg[2*node], seg[2*node+1]);
}

int query(int s, int e, int node, int l, int r) {
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) {
        return seg[node];
    }

    int mid = (s + e) / 2;
    return max(query(s, mid, 2*node, l, r), query(mid+1, e, 2*node+1, l, r));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) {
        cin>>bases[i].x>>bases[i].y>>bases[i].a>>bases[i].b;
        bases[i].idx = i;
    }

    for(int i=0; i<=n+1; i++) {
        roots[i] = i;
    }

    Union(1, 0);

    sort(bases, bases + n);
    for(int i=0; i<n; i++) {
        int last_day = query(0, n-1, 1, 0, bases[i].y);
        int my_day = find(last_day);
        my_day = max(find(bases[i].a), my_day);

        if(bases[i].b < my_day)
            goto impossible;
        
        days[bases[i].idx] = my_day;
        update(0, n-1, 1, bases[i].y, my_day);
        Union(my_day + 1, my_day);
    }

    cout<<"YES\n";
    for(int i=0; i<n; i++) cout<<days[i]<<" ";

    return 0;
impossible:
    cout<<"NO\n";
}