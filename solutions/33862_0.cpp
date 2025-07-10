    #include <bits/stdc++.h>

    using namespace std;

    using ll = long long;

    const int MAXN = 1010101;
    const ll inf = 1e18;

    int n, m, k, p, c, a[MAXN], cnt[MAXN], cover[MAXN], s[MAXN], usage[MAXN];
    ll dp[MAXN][2];

    struct SegTree {
        int n;
        vector<ll> t;
        void init(int _n) {
            n = _n;
            t.clear();
            t.resize(2*n, inf);
        }
        void update(int x, ll v) {
            x += n;
            t[x] = min(t[x], v);
            while(x>>=1) {
                t[x] = min(t[x<<1], t[x<<1|1]);
            }
        }
        ll query(int l, int r) {
            ll ret = inf;
            for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
                if(l&1) ret = min(ret, t[l++]);
                if(~r&1) ret = min(ret, t[r--]);
            }
            return ret;
        }
    };

    int main()
    {
        cin >> n >> m >> k >> p;
        cin >> c;
        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= n; i++) {
            s[i] = s[i-1];
            usage[i] = usage[i-1] - cover[a[i]];
            if(cnt[a[i]]++%p == 0) s[i]++;
            cover[a[i]] = (bool)(cnt[a[i]]%p);
            usage[i] += cover[a[i]];
        }

        for(int i = 1; i <= n; i++) s[i] -= usage[i];

        if(c == 1) {
            SegTree seg; seg.init(n+1);
            seg.update(0, 2*n);
            for(int i = 1; i <= n; i++) {
                int j = lower_bound(s, s+i, s[i]+usage[i]-m) - s;
                dp[i][0] = seg.query(j, n);
                seg.update(i, dp[i][0] + 2*(n+1-(i+1)));
            }
            cout << dp[n][0] - n + 1;
        }
        else if(c == 2) {
            for(int i = 1; i <= n; i++) {
                int j = lower_bound(s, s+i, s[i]+usage[i]-m) - s;
                dp[i][1] = dp[j][1] + 2*i;
            }
            cout << dp[n][1] - n + 1;
        }
        else {
            for(int i = 1; i <= n; i++) {
                int j = lower_bound(s, s+i, s[i]+usage[i]-m) - s;
                dp[i][1] = dp[j][1] + 2*i;
            }
            SegTree seg; seg.init(n+1);
            seg.update(0, 2*n);
            for(int i = 1; i <= n; i++) {
                int j = lower_bound(s, s+i, s[i]+usage[i]-m) - s;
                dp[i][0] = min(seg.query(j, n), dp[j][1] + n+1);
                seg.update(i, dp[i][0] + 2*(n+1-(i+1)));
            }
            cout << dp[n][0];
        }
    }