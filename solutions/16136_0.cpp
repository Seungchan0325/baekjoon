#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

struct T {
    ll mn;
    ll mx;
    ll sum;
};

ll n, q, arr[MAXN], lazy[4*MAXN];
T tree[4*MAXN];

ll next(ll v)
{
    ll ret = 1;
    for(ll i = 2; i * i <= v; i++) {
        ll cnt = 0;
        while(v % i == 0) {
            cnt++;
            v /= i;
        }
        if(cnt > 0) ret *= cnt + 1;
    }
    if(v != 1) ret *= 2;
    return ret;
}

T merge(T a, T b)
{
    T ret;
    ret.mn = min(a.mn, b.mn);
    ret.mx = max(a.mx, b.mx);
    ret.sum = a.sum + b.sum;
    return ret;
}

void init(ll start = 1, ll end = n, ll index = 1)
{
    if(start == end) {
        tree[index].mn = tree[index].mx = tree[index].sum = arr[start];
        return;
    }
    ll mid = (start + end) / 2;
    init(start, mid, 2*index);
    init(mid+1, end, 2*index+1);
    tree[index] = merge(tree[2*index], tree[2*index+1]);
}

void propagate(ll start, ll end, ll index)
{
    if(lazy[index]) {
        tree[index].mn = lazy[index];
        tree[index].mx = lazy[index];
        tree[index].sum = (end - start + 1) * lazy[index];
        if(start != end) {
            lazy[2*index] = lazy[index];
            lazy[2*index+1] = lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(ll left, ll right, ll start = 1, ll end = n, ll index = 1)
{
    propagate(start, end, index);
    if(end < left || right < start) return;

    if(left <= start && end <= right && tree[index].mn == tree[index].mx) {
        ll nxt = next(tree[index].mn);
        lazy[index] = nxt;
        propagate(start, end, index);
        return;
    }

    ll mid = (start + end) / 2;
    update(left, right, start, mid, 2*index);
    update(left, right, mid+1, end, 2*index+1);
    tree[index] = merge(tree[2*index], tree[2*index+1]);
}

ll query(ll left, ll right, ll start = 1, ll end = n, ll index = 1)
{
    propagate(start, end, index);
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return tree[index].sum;

    ll mid = (start + end) / 2;
    return query(left, right, start, mid, 2*index) + query(left, right, mid+1, end, 2*index+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> q;
    for(ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    init();
    while(q--) {
        ll t, s, e;
        cin >> t >> s >> e;
        if(t == 1) {
            update(s, e);
        } else {
            ll result = query(s, e);
            cout << result << "\n";
        }
    }
}