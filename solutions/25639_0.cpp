#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;
const int MAXN = 100005;

struct T {
    int mn;
    int mx;
    int mx_inc;
    T() = default;
    T(int _mn, int _mx, int _mx_inc) : mn(_mn), mx(_mx), mx_inc(_mx_inc) {}
    T(int v) : mn(v), mx(v), mx_inc(0) {}
};

int N, Q, arr[MAXN];
T tree[4*MAXN];

T merge(T l, T r)
{
    return {min(l.mn, r.mn), max(l.mx, r.mx), max({l.mx_inc, r.mx_inc, r.mx - l.mn})};
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx] = arr[s];
        return;
    }

    int m = (s + e) >> 1;
    init(s, m, 2*idx); init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update(int pos, int value, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx] = value;
        return;
    }

    int m = (s + e) >> 1;
    update(pos, value, s, m, 2*idx);
    update(pos, value, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return {INF, -INF, 0};
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) >> 1;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    init();
    cin >> Q;
    while(Q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int k, x;
            cin >> k >> x;
            update(k, x);
        } else {
            int l, r;
            cin >> l >> r;
            T result = query(l, r);
            cout << result.mx_inc << "\n";
        }
    }
}