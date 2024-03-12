#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXR = 250005;
const int MAXSZ = 500005;

int N, K, R, tree[4*MAXSZ], lazy[4*MAXSZ];
vector<int> xs;
vector<vector<tuple<int, int>>> yk;
vector<multiset<int>> s;
vector<tuple<int, int, int>> point;

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int delta, int s = 1, int e = MAXSZ, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += delta;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, delta, s, m, 2*idx);
    update(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

pair<int, int> clamp(int y, int k)
{
    auto it = s[k].lower_bound(y);
    int py = -INF;
    int ny = INF;
    if(it != s[k].end()) ny = *it;
    if(it != s[k].begin()) py = *(--it);

    return {max(y, py + R + 1), min(y + R, ny - 1)};
}

bool check()
{
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));
    s.clear();
    s.resize(K + 1);
    int p = 0;
    for(int i = 0; i < xs.size(); i++) {
        while(xs[p] < xs[i] - R) {
            for(auto [y, k] : yk[p]) {
                s[k].erase(s[k].find(y));
                auto [l, r] = clamp(y, k);
                if(l <= r) update(l, r, -1);
            }
            p++;
        }
        for(auto [y, k] : yk[i]) {
            auto [l, r] = clamp(y, k);
            if(l <= r) update(l, r, 1);
            s[k].insert(y);
        }
        assert(tree[1] <= K);
        if(tree[1] == K) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for(int i = 0; i < N; i++) {
        int x, y, k;
        cin >> x >> y >> k;
        xs.push_back(x);
        point.emplace_back(x, y, k);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    yk.resize(xs.size());
    for(auto [x, y, k] : point) {
        x = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        yk[x].emplace_back(y, k);
    }
    
    int lo = -1, hi = MAXR;
    while(lo + 1 < hi) {
        R = (lo + hi) >> 1;
        if(check()) hi = R;
        else lo = R;
    }
    cout << hi;
}