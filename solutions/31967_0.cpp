#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 250505;

struct T {
    ll mn;
    ll sum;
};

struct Query {
    ll l, r, idx;
};

ll N, Q, A[MAXN], D[MAXN], ans[MAXN], lazy[4*MAXN];
Query q[MAXN];
T tree[4*MAXN];

T merge(T a, T b)
{
    return {min(a.mn, b.mn), a.sum + b.sum};
}

void push(ll s, ll e, ll idx)
{
    if(lazy[idx]) {
        tree[idx].sum += (e - s + 1) * lazy[idx];
        tree[idx].mn += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(ll l, ll r, ll delta, ll s = 1, ll e = N, ll idx = 1) {
    push(s, e, idx);
    if(r < s || e < l) return;
    if(l <= s && e <= r) {
        lazy[idx] += delta;
        push(s, e, idx);
        return;
    }
    ll m = (s + e) / 2;
    update(l, r, delta, s, m, 2*idx);
    update(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(ll l, ll r, ll s = 1, ll e = N, ll idx = 1) {
    push(s, e, idx);
    if(l <= s && e <= r) return tree[idx];
    ll m = (s + e) / 2;
    if(r <= m) return query(l, r, s, m, 2*idx);
    if(m+1 <= l) return query(l, r, m+1, e, 2*idx+1);
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

pair<ll, ll> query_idx(ll s = 1, ll e = N, ll idx = 1)
{
    push(s, e, idx);
    if(s == e) return {s, tree[idx].sum};
    if(tree[idx].mn >= 0) return {-1, -1};
    ll m = (s + e) / 2;
    push(s, m, 2*idx);
    push(m+1, e, 2*idx+1);
    if(tree[2*idx].mn < 0) return query_idx(s, m, 2*idx);
    else return query_idx(m+1, e, 2*idx+1);
}

void debug()
{
    for(ll i = 1; i <= N; i++) {
        cout << query(i, i).sum << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(ll i = 1; i <= N; i++) cin >> A[i];
    for(ll i = 1; i <= Q; i++) cin >> q[i].l >> q[i].r, q[i].idx = i;
    for(ll i = 2; i <= N; i++) {
        ll num = A[i-1];
        while(2*num <= A[i]) num *= 2, D[i]--;
        num = A[i];
        while(num < A[i-1]) num *= 2, D[i]++;
        update(i, N, D[i]);
    }

    sort(q+1, q+Q+1, [](Query i, Query j) {
        return i.l < j.l;
    });

    ll j = 1;
    set<ll> s;
    s.insert(N+1);
    for(ll i = 1; i <= N; i++) {
        ll r = *s.lower_bound(i) - 1;
        update(i, r, -query(i, i).sum);
        while(tree[1].mn < 0) {
            auto [idx, delta] = query_idx();
            ll r = *s.lower_bound(idx) - 1;
            update(idx, r, -delta);
            s.insert(idx);
        }

        while(j <= Q && q[j].l <= i) {
            if(q[j].l == q[j].r) ans[q[j].idx] = 0;
            else ans[q[j].idx] = query(q[j].l + 1, q[j].r).sum;
            j++;
        }
    }

    for(ll i = 1; i <= Q; i++) {
        cout << ans[i] << "\n";
    }
}