#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int n, m, tree[4*MAXN];

void update(int pos, int delta, int start = 0, int end = n-1, int index = 1) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(pos, delta, start, mid, 2*index);
    update(pos, delta, mid+1, end, 2*index+1);
    tree[index] = tree[2*index] + tree[2*index+1];
}

int query(int left, int right, int start = 0, int end = n-1, int index = 1) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return query(left, right, start, mid, 2*index) + query(left, right, mid+1, end, 2*index+1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int v; cin >> v;
        update(i, v);
    }

    cin >> m;
    while(m--) {
        int t; cin >> t;
        if(t == 1) {
            int i, delta; cin >> i >> delta;
            update(i-1, delta);
        } else {
            int i; cin >> i;

            int lo = -1, hi = n;
            while(lo+1 < hi) {
                int mid = (lo + hi) / 2;
                int cnt = query(0, mid);
                if(cnt < i) lo = mid;
                else hi = mid;
            }
            cout << hi + 1 << "\n";
        }
    }
}