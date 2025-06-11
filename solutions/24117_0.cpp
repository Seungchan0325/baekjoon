#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50505;
const int MAXX = 101010;

int n, m, a[MAXN], lo[MAXN], hi[MAXN], ans[MAXN], tree[4*MAXX], lazy[4*MAXX];

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

void update(int l, int r, int v, int s = 1, int e = MAXX, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += v;
        propagate(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int x, int s = 1, int e = MAXX, int idx = 1)
{
    propagate(s, e, idx);
    if(s == e) return s;
    int m = (s + e) / 2;

    propagate(s, m, 2*idx);
    propagate(m+1, e, 2*idx+1);
    if(tree[2*idx] >= x) return query(x, s, m, 2*idx);
    else return query(x, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<tuple<int, int, int>> obj(n);
    for(auto& [y, x, w] : obj) cin >> x >> y >> w;
    sort(obj.begin(), obj.end());

    for(int i = 1; i <= m; i++) {
        cin >> a[i];
        lo[i] = 0;
        hi[i] = 1e9+1;
    }

    while(true) {
        bool isdone = true;
        vector<pair<int, int>> qs; qs.reserve(m);
        for(int i = 1; i <= m; i++) {
            if(lo[i] + 1 < hi[i]) {
                isdone = false;
                qs.emplace_back((lo[i] + hi[i]) / 2, i);
            }
        }
        if(isdone) break;
        sort(qs.begin(), qs.end());
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));
        int idx = 0;
        for(auto [y, i] : qs) {
            while(idx < n && get<0>(obj[idx]) <= y) {
                auto [y, x, w] = obj[idx++];
                update(x, x + w - 1, 1);
            }
            if(tree[1] <= a[i]) {
                lo[i] = y;
            } else {
                hi[i] = y;
            }
        }
    }
    
    vector<pair<int, int>> qs; qs.reserve(m);
    for(int i = 1; i <= m; i++) {
        qs.emplace_back(hi[i], i);
    }
    sort(qs.begin(), qs.end());
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));
    int idx = 0;
    for(auto [y, i] : qs) {
        while(idx < n && get<0>(obj[idx]) <= y) {
            auto [y, x, w] = obj[idx++];
            update(x, x + w - 1, 1);
        }
        ans[i] = query(a[i]+1);
    }

    for(int i = 1; i <= m; i++) {
        if(hi[i] >= 1e9) cout << "-1 -1\n";
        else cout << ans[i] << " " << hi[i] << "\n";
    }
}