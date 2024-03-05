#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;
const ll INF = 1e18;

struct T {
    ll mn, mx;
    ll mx_diff;
};

ll N, M, arr[MAXN], psum[MAXN];
T tree[4*MAXN];

T merge(T l, T r)
{
    T ret;
    ret.mn = min(l.mn, r.mn);
    ret.mx = max(l.mx, r.mx);
    ret.mx_diff = max({l.mx_diff, r.mx_diff, r.mx - l.mn});
    return ret;
}

void init(ll s = 0, ll e = N, ll idx = 1)
{
    if(s == e) {
        tree[idx].mn = tree[idx].mx = psum[s];
        tree[idx].mx_diff = -INF;
        return;
    }
    ll m = (s + e) >> 1;
    init(s, m, 2*idx); init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(ll l, ll r, ll s = 0, ll e = N, ll idx = 1)
{
    if(e < l || r < s) return T{INF, -INF, -INF};
    if(l <= s && e <= r) return tree[idx];
    ll m = (s + e) >> 1;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(ll i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    for(ll i = 1; i <= N; i++) {
        psum[i] = arr[i] + psum[i-1];
    }
    init();
    cin >> M;
    for(ll i = 0; i < M; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ll ans = -INF;
        if(x2 <= y1) {
            T t = query(x2 - 1, y1);
            ans = max(ans, t.mx_diff);

            T l = query(x1 - 1, y1 - 1);
            T r = query(y1, y2);
            ans = max(ans, r.mx - l.mn);

            l = query(x1 - 1, x2 - 1);
            r = query(x2, y2);
            ans = max(ans, r.mx - l.mn);
        } else {
            T l = query(x1 - 1, y1 - 1);
            T r = query(x2, y2);
            ans = max(r.mx - l.mn, ans);
        }
        cout << ans << "\n";
    }
}