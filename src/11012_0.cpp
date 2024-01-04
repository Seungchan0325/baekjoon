#include <bits/stdc++.h>

using namespace std;

struct Node {
    int l, r, data;
};

const int MAXN = 10005;
const int MAXXY = 1e5 + 5;

int last = 1, root[MAXN];
Node nd[(int)1e7];

void build(int node, int start, int end) {
    nd[node].data = 0;
    if(start == end) return;
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
    int tc; cin >> tc;
    while(tc--) {
        last = 1;
        int n, m; cin >> n >> m;
        vector<pair<int, int>> vs(n);
        vector<int> xs; xs.reserve(n);
        for(auto& [x, y] : vs) {
            cin >> x >> y;
            xs.push_back(x);
        }

        sort(vs.begin(), vs.end());

        xs.push_back(0);
        sort(xs.begin(), xs.end());

        root[0] = 0;
        build(root[0], 0, MAXXY);
        for(int i = 0; i < n; i++) {
            root[i+1] = last++;
            nd[root[i+1]] = nd[root[i]];
            nd[root[i+1]].data += 1;
            update(root[i], root[i+1], 0, MAXXY, vs[i].second, 1);
        }
        
        long long sum = 0;
        for(int i = 0; i < m; i++) {
            int l, r, b, t; cin >> l >> r >> b >> t;
            r = upper_bound(xs.begin(), xs.end(), r) - xs.begin() - 1;
            l = lower_bound(xs.begin(), xs.end(), l) - xs.begin() - 1;
            sum += query(root[r], 0, MAXXY, b, t) - query(root[l], 0, MAXXY, b, t);
        }
        cout << sum << "\n";
    }
}