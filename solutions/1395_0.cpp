#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
int m;
int tree[4 * MAXN], lazy[4 * MAXN];

void propagate(int s, int e, int idx) {
    if(lazy[idx] % 2 == 1) {
        tree[idx] = (e - s + 1) - tree[idx];

        if(s != e) {
            lazy[2 * idx] += lazy[idx];
            lazy[2 * idx + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update_range(int s, int e, int idx, int qs, int qe) {
    propagate(s, e, idx);
    if(qe < s || e < qs) return;

    if(qs <= s && e <= qe) {
        tree[idx] = (e - s + 1) - tree[idx];
        if(s != e) {
            lazy[2 * idx]++;
            lazy[2 * idx + 1]++;
        }
        return;
    }

    int mid = (s + e) / 2;
    update_range(s, mid, 2 * idx, qs, qe);
    update_range(mid + 1, e, 2 * idx + 1, qs, qe);
    tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

int query_range(int s, int e, int idx, int qs, int qe) {
    propagate(s, e, idx);
    if(qe < s || e < qs) return 0;

    if(qs <= s && e <= qe) {
        return tree[idx];
    }

    int mid = (s + e) / 2;
    int lsum = query_range(s, mid, 2 * idx, qs, qe);
    int rsum = query_range(mid + 1, e, 2 * idx + 1, qs, qe);

    return lsum + rsum;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m;
    for(int i=0; i<m; i++) {
        int o, s, e; cin>>o>>s>>e; s--; e--;

        if(o == 0) {
            update_range(0, n-1, 1, s, e);
        } else if(o == 1) {
            int q = query_range(0, n-1, 1, s, e);
            cout<<q<<"\n";
        }
    }
}