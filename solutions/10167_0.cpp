#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using Mine = tuple<int, int, ll>;

const int MAXN = 3005;

int n;
vector<Mine> mines;

ll ltree[4*MAXN];
ll rtree[4*MAXN];
ll lrtree[4*MAXN];
ll tree[4*MAXN];

void update(int start, int end, int idx, int pos, ll val) {
    if(end < pos || pos < start) return;

    if(start == end) {
        ltree[idx] = rtree[idx] = lrtree[idx] = tree[idx] = lrtree[idx] + val;
        tree[idx] = max(0LL, tree[idx]);
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*idx, pos, val);
    update(mid+1, end, 2*idx+1, pos, val);

    ltree[idx] = max({ltree[2*idx], lrtree[2*idx] + ltree[2*idx+1]});
    rtree[idx] = max({rtree[2*idx+1], rtree[2*idx] + lrtree[2*idx+1]});
    lrtree[idx] = lrtree[2*idx] + lrtree[2*idx+1];
    tree[idx] = max({0LL,
                     ltree[idx],
                     rtree[idx],
                     lrtree[idx],
                     rtree[2*idx] + ltree[2*idx+1],
                     tree[2*idx],
                     tree[2*idx+1]});
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;

    vector<int> xs, ys;
    for(int i = 0; i < n; i++) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        mines.emplace_back(x, y, w);
        xs.push_back(x);
        ys.push_back(y);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<vector<tuple<int, ll>>> updates(xs.size());
    for(auto [x, y, w] : mines) {
        int nx = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        int ny = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
        updates[nx].emplace_back(ny, w);
    }

    ll ans = 0;
    for(int l = 0; l < xs.size(); l++) {
        for(int r = l; r < xs.size(); r++) {
            for(auto [y, w] : updates[r]) update(0, ys.size()-1, 1, y, w);

            ans = max(tree[1], ans);
        }
        memset(ltree, 0, sizeof(ltree));
        memset(rtree, 0, sizeof(rtree));
        memset(lrtree, 0, sizeof(lrtree));
        memset(tree, 0, sizeof(tree));
    }

    cout << ans;
}