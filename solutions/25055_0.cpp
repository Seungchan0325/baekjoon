#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const int inf = 1e9;

struct SegTree {
    int n;
    vector<int> t;
    void init(int _n) {
        n = _n;
        t.clear();
        t.resize(2*n, -inf);
    }
    void update(int x, int v) {
        x += n;
        t[x] = max(t[x], v);
        while(x>>=1) {
            t[x] = max(t[x<<1], t[x<<1|1]);
        }
    }
    int query(int l, int r) {
        int ret = -inf;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret = max(ret, t[l++]);
            if(~r&1) ret = max(ret, t[r--]);
        }
        return ret;
    }
};

int n, v, t[MAXN], a[MAXN];
int dp[MAXN];

void dnc(int s, int e)
{
    if(e <= s) return;
    int m = (s + e) / 2;
    dnc(s, m);
    
    vector<ll> xs, ys;
    for(int i = s; i <= e; i++) {
        xs.push_back(a[i] - v * t[i]);
        ys.push_back(a[i] + v * t[i]);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<int> order(e-s+1); iota(order.begin(), order.end(), s);
    sort(order.begin(), order.end(), [](int i, int j){
        if(a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });

    SegTree seg; seg.init(e-s+1);
    for(int i : order) {
        int j = lower_bound(xs.begin(), xs.end(), a[i] - v * t[i]) - xs.begin();
        if(i <= m) {
            seg.update(j, dp[i]);
        } else {
            dp[i] = max(dp[i], seg.query(j, e-s) + 1);
        }
    }

    sort(order.begin(), order.end(), [](int i, int j){
        if(a[i] != a[j]) return a[i] > a[j];
        return i < j;
    });

    seg.init(e-s+1);
    for(int i : order) {
        int j = lower_bound(ys.begin(), ys.end(), a[i] + v * t[i]) - ys.begin();
        if(i <= m) {
            seg.update(j, dp[i]);
        } else {
            dp[i] = max(dp[i], seg.query(0, j) + 1);
        }
    }

    dnc(m+1, e);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> v;
    for(int i = 1; i <= n; i++) {
        cin >> t[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    t[0] = a[0] = dp[0] = 0;
    for(int i = 1; i <= n; i++) dp[i] = -inf;
    dnc(0, n);
    int ans = 0;
    for(int i = 0; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans;
}