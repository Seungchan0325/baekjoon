#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;
const int MAXM = 1010101;
const ll inf = 1e18;

ll N, M, K, cnt[MAXN], pos[MAXN], op[MAXM], t[MAXM], l[MAXM], r[MAXM], x[MAXM], h[MAXM];
ll tree[4*MAXM], F[MAXM];

void U(int x, int v, int sz)
{
    while(x <= sz) {
        F[x] += v;
        x += x & -x;
    }
}

int Q(int x)
{
    int res = 0;
    while(x > 0) {
        res += F[x];
        x -= x & -x;
    }
    return res;
}

void init(int s, int e, int idx)
{
    tree[idx] = -inf;
    if(s == e) {
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
}

void update(int x, ll v, int s, int e, int idx)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = v;
        return;
    }
    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, ll x, int s, int e, int idx)
{
    if(e < l || r < s) return -1;
    if(l <= s && e <= r && tree[idx] <= x) return -1;
    if(s == e) return s;
    int m = (s + e) / 2;
    int lef = query(l, r, x, s, m, 2*idx);
    if(lef >= 0) return lef;
    return query(l, r, x, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    for(int i = 0; i < M; i++) {
        cin >> op[i] >> t[i];
        if(op[i] == 1) cin >> x[i] >> h[i];
        else if(op[i] == 2) cin >> l[i] >> r[i] >> h[i];
        else if(op[i] == 3) cin >> l[i] >> r[i];
        else assert(0);
    }
    for(int i = 0; i < M; i++) {
        if(op[i] == 1) cnt[x[i]]++;
    }
    for(int i = 1; i <= N; i++) {
        cnt[i] += cnt[i-1];
        pos[i] = cnt[i];
    }
    int sz = cnt[N];
    if(sz == 0) {
        for(int i = 0; i < M; i++) {
            if(op[i] == 3) cout << "0\n";
        }
        return 0;
    }
    init(0, sz-1, 1);
    for(int i = 0; i < M; i++) {
        if(op[i] == 1) {
            int j = --pos[x[i]];
            ll v = h[i] - K * t[i];
            U(j+1, 1, sz);
            update(j, v, 0, sz-1, 1);
        } else if(op[i] == 2) {
            while(true) {
                int j = query(cnt[l[i]-1], cnt[r[i]]-1, h[i]-K*t[i], 0, sz-1, 1);
                if(j < 0) break;
                update(j, -inf, 0, sz-1, 1);
                U(j+1, -1, sz);
            }
        } else if(op[i] == 3) {
            int ans = Q(cnt[r[i]]) - Q(cnt[l[i]-1]);
            cout << ans << "\n";
        }
    }
}