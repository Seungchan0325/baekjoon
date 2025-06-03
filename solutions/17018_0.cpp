#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;
const int inf = 1e9;

int n, k, s[MAXN], dp[MAXN];
deque<pair<int, int>> dq[MAXN];

struct SegTree {
    int n;
    vector<int> tree;
    void init(int _n) {
        n = _n;
        tree.resize(2*n, inf);
    }
    void update(int x, int v) {
        x += n; tree[x] = v;
        while(x >>= 1) tree[x] = min(tree[x<<1], tree[x<<1|1]);
    }
    int query(int l, int r) {
        int ret = inf;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret = min(ret, tree[l++]);
            if(~r&1) ret = min(ret, tree[r--]);
        }
        return ret;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> k;
    int offset = 0;
    for(int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        s[i] = s[i-1] + (c == 'H' ? 1 : -1);
        offset = min(offset, s[i]);
    }
    offset = -offset;
    SegTree seg; seg.init(n+1);
    seg.update(s[0]+offset, 0);
    dq[s[0]+offset].emplace_back(0, 0);
    for(int i = 1; i <= n; i++) {
        if(i > k) {
            int j = s[i-k-1] + offset;
            while(dq[j].size() && i - dq[j][0].first > k) dq[j].pop_front();
            if(dq[j].empty()) seg.update(j, inf);
            else seg.update(j, dq[j][0].second);
        }
        int j = s[i] + offset;
        dp[i] = min(seg.query(0, j-1), seg.query(j+1, n)+1);
        while(dq[j].size() && dq[j].back().second > dp[i]) dq[j].pop_back();
        dq[j].emplace_back(i, dp[i]);
        seg.update(j, dq[j][0].second);
    }
    cout << dp[n];
}