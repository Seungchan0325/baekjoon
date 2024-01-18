#include <bits/stdc++.h>

using namespace std;

const int MAXSZ = 2005;

int n1, n2, c1, c2, tree[4*MAXSZ], ltree[4*MAXSZ], rtree[4*MAXSZ], lrtree[4*MAXSZ];
vector<tuple<int, int, int>> p;

void update(int start, int end, int index, int pos, int v) {
    if(end < pos || pos < start) return;
    
    if(start == end) {
        tree[index] = ltree[index] = rtree[index] = lrtree[index] = v;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, v);
    update(mid+1, end, 2*index+1, pos, v);

    ltree[index] = max(ltree[2*index], lrtree[2*index] + ltree[2*index+1]);
    rtree[index] = max(rtree[2*index+1], rtree[2*index] + lrtree[2*index+1]);
    lrtree[index] = lrtree[2*index] + lrtree[2*index+1];
    tree[index] = max({
        ltree[index],
        rtree[index],
        rtree[2*index] + ltree[2*index+1],
        tree[2*index],
        tree[2*index+1]
    });
}

int main() {
    vector<int> xs, ys;

    cin >> n1;
    for(int i = 0; i < n1; i++) {
        int x, y; cin >> x >> y;
        xs.push_back(x); ys.push_back(y);
        p.emplace_back(x, y, 1);
    }

    cin >> n2;
    for(int i = 0; i < n2; i++) {
        int x, y; cin >> x >> y;
        xs.push_back(x); ys.push_back(y);
        p.emplace_back(x, y, -1);
    }

    cin >> c1 >> c2;

    sort(p.begin(), p.end());

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<pair<int, int>> updates(xs.size());
    for(auto [x, y, t] : p) {
        x = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        y = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
        if(t == 1) t = c1;
        else t = -c2;

        updates[x] = {y, t};
    }

    int ans = 0;
    for(int start = 0; start < xs.size(); start++) {
        memset(tree, 0, sizeof(tree));
        memset(ltree, 0, sizeof(ltree));
        memset(rtree, 0, sizeof(rtree));
        memset(lrtree, 0, sizeof(lrtree));
        for(int end = start; end < xs.size(); end++) {
            auto [y, t] = updates[end];
            update(0, ys.size()-1, 1, y, t);
            ans = max(tree[1], ans);
        }
    }

    cout << ans;
}