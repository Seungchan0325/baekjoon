#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const llint MAXN = 500005;

llint N, Q, arr[MAXN], t[MAXN];

void cnt_update(llint i, llint delta)
{
    while(i<=(N+1)) {
        t[i] += delta;
        i += (i & -i);
    }
}

llint cnt_query(llint i)
{
    llint ret = 0;
    while(i>0) {
        ret += t[i];
        i -= (i & -i);
    }
    return ret;
}

struct T {
    bool is_valid;
    llint mx, mn, mxs[4];
    int sz;
};

T tree[4*MAXN];
llint lazy[4*MAXN];

T merge(const T& a, const T& b)
{
    if(!a.is_valid) return b;
    if(!b.is_valid) return a;
    T ret = {};
    ret.is_valid = true;
    ret.mn = min(a.mn, b.mn);
    ret.mx = max(a.mx, b.mx);
    int n = a.sz;
    int m = b.sz;
    int i, j;
    i = j = 0;
    while(ret.sz <= 3 && (i < n || j < m)) {
        if(j == m || (i < n && a.mxs[i] > b.mxs[j]))
            ret.mxs[ret.sz++] = a.mxs[i++];
        else if(i == n || (j < m && a.mxs[i] < b.mxs[j]))
            ret.mxs[ret.sz++] = b.mxs[j++];
        else {
            ret.mxs[ret.sz++] = a.mxs[i];
            i++, j++;
        }
    }
    return ret;
}

void init(llint s = 1, llint e = N, llint idx = 1)
{
    if(s == e) {
        tree[idx].is_valid = true;
        tree[idx].mn = arr[s];
        tree[idx].mx = arr[s];
        tree[idx].mxs[tree[idx].sz++] = arr[s];
        return;
    }
    llint m = (s + e) >> 1;
    init(s, m, 2*idx); init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void propagate(llint s, llint e, llint idx)
{
    if(lazy[idx]) {
        tree[idx].mn += lazy[idx];
        tree[idx].mx += lazy[idx];
        for(int i = 0; i < tree[idx].sz; i++)
            tree[idx].mxs[i] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void pollint_update(llint pos, llint s = 1, llint e = N, llint idx = 1)
{
    propagate(s, e, idx);
    if(e < pos || pos < s) return;
    if(s == e) {
        tree[idx].is_valid = false;
        return;
    }
    llint m = (s + e) >> 1;
    pollint_update(pos, s, m, 2*idx);
    pollint_update(pos, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update(llint l, llint r, llint delta, llint s = 1, llint e = N, llint idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += delta;
        propagate(s, e, idx);
        return;
    }

    llint m = (s + e) >> 1;
    update(l, r, delta, s, m, 2*idx);
    update(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(llint l, llint r, llint s = 1, llint e = N, llint idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return T{false};
    if(l <= s && e <= r) return tree[idx];
    llint m = (s + e) >> 1;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

llint get_idx(llint k)
{
    llint lo = 0, hi = N;
    while(lo+1 < hi) {
        llint mid = (lo + hi) >> 1;
        if(cnt_query(mid) < k) lo = mid;
        else hi = mid;
    }
    return hi;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);

    cin >> N;
    for(llint i = 1; i <= N; i++) {
        cin >> arr[i];
        cnt_update(i, 1);
    }
    init();
    cin >> Q;
    while(Q--) {
        llint type; cin >> type;
        if(type == 1) {
            llint i; cin >> i;
            llint idx = get_idx(i);
            pollint_update(idx);
            cnt_update(idx, -1);
        } else if(type == 2) {
            llint i, r; cin >> i >> r;
            llint L = get_idx(i - r);
            llint R = get_idx(i + r);
            T t = query(L, R);
            update(L, R, -t.mn);
        } else if(type == 3) {
            llint i, r; cin >> i >> r;
            llint L = get_idx(i - r);
            llint R = get_idx(i + r);
            T t = query(L, R);
            update(L, R, t.mx);
        } else {
            llint l, r; cin >> l >> r;
            l = get_idx(l);
            r = get_idx(r);
            T t = query(l, r);
            if(t.is_valid && 3 <= t.sz) cout << t.mxs[2] << '\n';
            else cout << -1 << "\n";
        }
    }
}