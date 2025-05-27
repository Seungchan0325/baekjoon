#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct T {
    int ans = 1e9;
    vector<pair<bitset<55>, int>> lef, rig;
};

bitset<55> full;
int N, K, M;
T tree[4*MAXN];

T merge(T a, T b)
{
    if(a.lef.empty()) return b;
    if(b.lef.empty()) return a;
    T ret;
    ret.ans = min(a.ans, b.ans);
    vector<pair<bitset<55>, int>> lef = a.lef, rig = b.rig;
    for(auto [i, k] : b.lef) {
        const auto& j = lef.back().first;
        if((i|j) != j) {
            lef.emplace_back(i|j, k);
        }
    }
    for(auto [i, k] : a.rig) {
        const auto& j = rig.back().first;
        if((i|j) != j) {
            rig.emplace_back(i|j, k);
        }
    }

    ret.lef = lef;
    ret.rig = rig;
    int idx = 0;
    for(auto [i, k] : views::reverse(a.rig)) {
        while(idx < b.lef.size() && (i|b.lef[idx].first) != full) idx++;
        if(idx < b.lef.size()) {
            ret.ans = min(ret.ans, b.lef[idx].second - k + 1);
        }
    }

    return ret;
}

void update(int x, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        T t;
        t.lef.emplace_back(1LL<<v, x);
        t.rig.emplace_back(1LL<<v, x);
        if((1LL<<v) == full) t.ans = 1;
        tree[idx] = t;
        return;
    }
    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> M;
    for(int i = 1; i <= K; i++) full.set(i);
    for(int i = 1; i <= N; i++) {
        int x; cin >> x;
        update(i, x);
    }
    while(M--) {
        int op;
        cin >> op;
        if(op == 1) {
            int p, v;
            cin >> p >> v;
            update(p, v);
        } else {
            int ans = tree[1].ans;
            if(ans >= 1e9) cout << "-1\n";
            else cout << ans << "\n";
        }
    }
}