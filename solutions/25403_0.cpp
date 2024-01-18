#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <ranges>

using namespace std;

using pii = pair<int, int>;

vector<int> lazy;
//value, index
vector<pii> min_tree;
vector<pii> max_tree;

void tree_init(int s, int e, int idx) {
    if(s == e) {
        min_tree[idx].second = s;
        max_tree[idx].second = s;
        return;
    }

    int mid = (s + e) / 2;
    tree_init(s, mid, idx * 2);
    tree_init(mid + 1, e, idx * 2 + 1);
    min_tree[idx] = min_tree[idx * 2];
    max_tree[idx] = max_tree[idx * 2 + 1];
}

void d(int idx, int delta) {
    min_tree[idx].first += delta;
    max_tree[idx].first += delta;
    lazy[idx] += delta;
}

void tree_update(int s, int e, int idx, int us, int ue, int delta) {
    if(e < us || ue < s) return;

    if(us <= s && e <= ue) {
        d(idx, delta);
        return;
    }
    
    d(idx * 2, lazy[idx]);
    d(idx * 2 + 1, lazy[idx]);
    lazy[idx] = 0;

    int mid = (s + e) / 2;
    tree_update(s, mid, idx * 2, us, ue, delta);
    tree_update(mid + 1, e, idx * 2 + 1, us, ue, delta);
    min_tree[idx] = min(min_tree[idx * 2], min_tree[idx * 2 + 1]);
    max_tree[idx] = max(max_tree[idx * 2], max_tree[idx * 2 + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, w, h;
    cin>>n>>m>>w>>h;
    vector<int> xs, ys;
    vector<pii> rb(n + m);
    for(auto& [x, y] : rb) {
        cin>>x>>y;
        xs.push_back(x + 1);
        xs.push_back(x - w);
        ys.push_back(y + 1);
        ys.push_back(y - h);
    }

    ranges::sort(xs);
    ranges::sort(ys);
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int xn = xs.size();
    int yn = ys.size();

    vector<vector<tuple<int, int, int>>> updates(xn + 1);

    for(int i = 0; i < n + m; i++) {
        int sx = ranges::lower_bound(xs, rb[i].first - w) - xs.begin();
        int ex = ranges::upper_bound(xs, rb[i].first) - xs.begin() - 1;
        int sy = ranges::lower_bound(ys, rb[i].second - h) - ys.begin();
        int ey = ranges::upper_bound(ys, rb[i].second) - ys.begin() - 1;

        updates[sx].push_back({sy, ey, i < n ? -1 : 1});
        updates[ex + 1].push_back({sy, ey, i < n ? 1 : -1});
    }

    lazy.resize(4 * yn + 1);
    min_tree.resize(4 * yn + 1);
    max_tree.resize(4 * yn + 1);

    tree_init(0, yn, 1);

    int ans = -1, ans_x, ans_y;

    for(int i = 0; i < xn; i++) {
        for(auto& [s, e, d]: updates[i]) tree_update(0, yn, 1, s, e, d);
        auto [diff, yidx] = abs(min_tree[1].first) > abs(max_tree[1].first) ? min_tree[1] : max_tree[1];
        if(abs(diff) > ans) {
            ans = abs(diff);
            ans_x = xs[i];
            ans_y = ys[yidx];
        }
    }

    cout<<ans<<"\n"<<ans_x<<" "<<ans_y;
}