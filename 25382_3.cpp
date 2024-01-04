#include <iostream>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cassert>


using namespace std;

using pii = pair<int, int>;

const int MAXN = 250055;
//const int MAXN = 9;
const int INF = 987654321;

struct Base {
    int idx;
    int x, y;
    int a, b;
};

int n, days[MAXN], min_seg[4*MAXN], max_seg[4*MAXN];
Base bases[MAXN];

void min_update(int s, int e, int node, int i, int v) {
    if(i < s || e < i) return;

    if(s == e) {
        min_seg[node] = v;
        return;
    }

    int mid = (s + e) / 2;
    min_update(s, mid, 2*node, i, v);
    min_update(mid+1, e, 2*node+1, i, v);
    min_seg[node] = min(min_seg[2*node], min_seg[2*node+1]);
}

int min_query(int s, int e, int node, int l, int r) {
    if(r < s || e < l) return INF;

    if(l <= s && e <= r) {
        return min_seg[node];
    }

    int mid = (s + e) / 2;
    return min(min_query(s, mid, 2*node, l, r), min_query(mid+1, e, 2*node+1, l, r));
}

void max_update(int s, int e, int node, int i, int v) {
    if(i < s || e < i) return;

    if(s == e) {
        max_seg[node] = v;
        return;
    }

    int mid = (s + e) / 2;
    max_update(s, mid, 2*node, i, v);
    max_update(mid+1, e, 2*node+1, i, v);
    max_seg[node] = max(max_seg[2*node], max_seg[2*node+1]);
}

int max_query(int s, int e, int node, int l, int r) {
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) {
        return max_seg[node];
    }

    int mid = (s + e) / 2;
    return max(max_query(s, mid, 2*node, l, r), max_query(mid+1, e, 2*node+1, l, r));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) {
        cin>>bases[i].x>>bases[i].y>>bases[i].a>>bases[i].b;
        bases[i].idx = i;
    }

    //fill(min_seg, min_seg + 4*n, INF);
    sort(bases, bases + n, [](Base a, Base b){ return a.x < b.x; });

    for(int i=0; i<n; i++) {
        int max_a = max_query(1, n, 1, 1, bases[i].y) + 1;
        max_a = max(bases[i].a, max_a);
        max_update(1, n, 1, bases[i].y, max_a);
        bases[i].a = max_a;
    }

    for(int i=1; i<=n; i++) min_update(1, n, 1, i, n+1);
    for(int i=n-1; i>=0; i--) {
        int min_b = min_query(1, n, 1, bases[i].y, n) - 1;
        min_b = min(bases[i].b, min_b);
        min_update(1, n, 1, bases[i].y, min_b);
        bases[i].b = min_b;
    }

    sort(bases, bases + n, [](Base a, Base b) {
        if(a.a == b.a) {
            return a.b < b.b;
        }
        return a.a < b.a;
    });

    for(int i=0; i<n; i++) {
        int t = i+1;
        if((t < bases[i].a) || (bases[i].b < t)) goto impossible;
        days[bases[i].idx] = t;
    }

    cout<<"YES\n";
    for(int i=0; i<n; i++) {
        cout<<days[i]<<" ";
    }

    return 0;
impossible:
    cout<<"NO\n";
}