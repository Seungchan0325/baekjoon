#include <algorithm>
#include <iostream>

#include <vector>
#include <tuple>

using namespace std;

#define all(x) x.begin(), x.end()

const int MAX = 30002;

vector<int> cnt(4 * MAX);
vector<int> tree(4 * MAX);

void update(int st, int en, int idx, int l, int r, int d) {
    if(r < st || en < l) return;

    if(l <= st && en <= r) {
        cnt[idx] += d;
    } else {
        int mid = (st + en) / 2;
        update(st, mid, idx * 2, l, r, d);
        update(mid + 1, en, idx * 2 + 1, l, r, d);
    }

    if(cnt[idx]) tree[idx] = en - st + 1;
    else tree[idx] = (st == en) ? 0 : tree[idx * 2] + tree[idx * 2 + 1];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    vector<tuple<int, int, int, int>> rects(n);
    for(auto& [x1, y1, x2, y2] : rects) cin>>x1>>y1>>x2>>y2;

    vector<int> xs;
    for(auto& [x1, y1, x2, y2] : rects) { xs.push_back(x1); xs.push_back(x2); }
    sort(all(xs));
    xs.erase(unique(all(xs)), xs.end());

    vector<vector<tuple<int, int, int>>> shifts(xs.size() + 1);
    for(auto& [x1, y1, x2, y2] : rects) {
        int lx = lower_bound(all(xs), x1) - xs.begin();
        int rx = lower_bound(all(xs), x2) - xs.begin();

        shifts[lx + 1].push_back({y1 + 1, y2, 1});
        shifts[rx + 1].push_back({y1 + 1, y2, -1});
    }

    int ans = 0;
    for(int i=1; i<shifts.size(); i++) {
        for(auto& [ly, ry, d] : shifts[i]) update(1, MAX, 1, ly, ry, d);
        ans += (xs[i] - xs[i-1]) * tree[1];
    }

    cout<<ans;
}