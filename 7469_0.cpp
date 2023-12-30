#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Node {
    int l, r, data;
};

int n, m, last = 1, arr[MAXN], root[MAXN];
Node nd[(int)1e7];

void build(int node, int start, int end) {
    if(start == end) {
        nd[node].data = 0;
        return;
    }

    int mid = (start + end) / 2;
    build(nd[node].l = last++, start, mid);
    build(nd[node].r = last++, mid+1, end);
}

void update(int prv, int node, int start, int end, int pos, int delta) {
    if(start == end) {
        nd[node].data = nd[prv].data + delta;
        return;
    }

    int mid = (start + end) / 2;
    if(pos <= mid) {
        nd[node].l = last++; nd[node].r = nd[prv].r;
        update(nd[prv].l, nd[node].l, start, mid, pos, delta);
    } else {
        nd[node].l = nd[prv].l; nd[node].r = last++;
        update(nd[prv].r, nd[node].r, mid+1, end, pos, delta);
    }

    nd[node].data = nd[nd[node].l].data + nd[nd[node].r].data;
}

int query(int node, int start, int end, int left, int right) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return nd[node].data;

    int mid = (start + end) / 2;
    return query(nd[node].l, start, mid, left, right) + query(nd[node].r, mid+1, end, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> arr[i];

    vector<int> v(arr+1, arr+n+1);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    build(root[0] = 0, 0, v.size()-1);
    for(int i = 1; i <= n; i++) {
        int idx = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
        update(root[i-1], root[i] = last++, 0, v.size()-1, idx, 1);
    }

    while(m--) {
        int i, j, k; cin >> i >> j >> k;

        int lo = -1, hi = v.size();
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            int cnt = query(root[j], 0, v.size()-1, 0, mid) - query(root[i-1], 0, v.size()-1, 0, mid);
            if(cnt < k) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        cout << v[hi] << "\n";
    }
}