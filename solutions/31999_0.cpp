#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const int MAXN = 200005;

ll N, M, K, X, Y, A[MAXN], B[MAXN], sum, tree[4*MAXN], lazy[4*MAXN];
int nxt[MAXN];

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, ll delta, int s = 1, int e = M, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy[idx] += delta;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, delta, s, m, 2*idx);
    update(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

ll query(int l, int r, int s = 1, int e = M, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return INF;
    
    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) >> 1;
    return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    cin >> N >> M >> K >> X >> Y;
    for(int i = 1; i <= M; i++) {
        cin >> A[i];
    }

    for(int i = 1; i <= N; i++) {
        cin >> B[i];
        sum += B[i];
    }

    vector<int> table(N+1, M+1);
    for(int i = M; i >= 1; i--) {
        nxt[i] = table[A[i]];
        table[A[i]] = i;
    }

    vector<bool> isfirst(N+1, true);
    for(int i = 1; i <= M; i++) {
        if(isfirst[A[i]]) {
            update(i, M, (X - Y) * B[A[i]]);
            isfirst[A[i]] = false;
        }
    }

    for(int i = 1; i <= M; i++) {
        update(i, M, K);
    }

    // for(int j = 1; j <= M; j++) {
    //     cout << query(j, j) << " ";
    // }
    // cout << "\n";

    ll ans = Y * sum;
    for(int i = 1; i <= M; i++) {
        ll cand = query(i, M) + Y * sum;
        ans = min(ans, cand);
        update(1, M, -K);
        update(i, nxt[i] - 1, -(X - Y) * B[A[i]]);
        // for(int j = 1; j <= M; j++) {
        //     cout << query(j, j) << " ";
        // }
        // cout << "\n";
    }

    cout << ans;
}