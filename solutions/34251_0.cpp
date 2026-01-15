#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;
const int inf = 1e9;

struct Node {
    int dp[3][3], width, count;
};

int N, Q, A[MAXN], lazy[4*MAXN];
Node tree[4*MAXN];

Node merge(Node a, Node b)
{
    Node res = {};
    res.count = 0;
    res.width = a.width + b.width;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            res.dp[i][j] = max({
                a.dp[i][0] + b.dp[2][j],
                a.dp[i][1] + b.dp[1][j],
                a.dp[i][2] + b.dp[0][j],
                a.dp[i][2] + b.dp[2][j],
                -inf
            });
        }
    }
    if(b.width%2) {
        for(int i = 0; i < 3; i++) {
            res.dp[i][1] = max(res.dp[i][1], a.dp[i][0]);
            res.dp[i][2] = max(res.dp[i][2], a.dp[i][1]);
            res.dp[i][1] = max(res.dp[i][1], a.dp[i][2]);
        }
    } else {
        for(int i = 0; i < 3; i++) {
            res.dp[i][2] = max(res.dp[i][2], a.dp[i][0]);
            res.dp[i][1] = max(res.dp[i][1], a.dp[i][1]);
            res.dp[i][2] = max(res.dp[i][2], a.dp[i][2]);
        }
    }
    if(a.width%2) {
        for(int j = 0; j < 3; j++) {
            res.dp[1][j] = max(res.dp[1][j], b.dp[0][j]);
            res.dp[2][j] = max(res.dp[2][j], b.dp[1][j]);
            res.dp[1][j] = max(res.dp[1][j], b.dp[2][j]);
        }
    } else {
        for(int j = 0; j < 3; j++) {
            res.dp[2][j] = max(res.dp[2][j], b.dp[0][j]);
            res.dp[1][j] = max(res.dp[1][j], b.dp[1][j]);
            res.dp[2][j] = max(res.dp[2][j], b.dp[2][j]);
        }
    }
    return res;
}

void init(int s, int e, int idx)
{
    tree[idx].width = e-s+1;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            tree[idx].dp[i][j] = -inf;
}

void build(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        init(s, e, idx);
        tree[idx].dp[0][0] = 1;
        return;
    }
    int m = (s + e) / 2;
    build(s, m, 2*idx);
    build(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        tree[idx].count += v;
        if(tree[idx].count) {
            init(s, e, idx);
        } else if(s != e) {
            tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
        } else {
            init(s, e, idx);
            tree[idx].dp[0][0] = 1;
        }
        return;
    }

    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    if(tree[idx].count == 0) tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
    return;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    build();
    for(int i = 0; i <= N; i++) {
        cin >> A[i];
        update(i-A[i]+1, i+A[i], 1);
    }

    int ans = (N-max(0, tree[1].dp[2][2])+1)/2;
    cout << ans << "\n";
    
    while(Q--) {
        int x, y;
        cin >> x >> y;
        update(x-A[x]+1, x+A[x], -1);
        A[x] = y;
        update(x-A[x]+1, x+A[x], 1);
        int ans = (N-max(0, tree[1].dp[2][2])+1)/2;
        cout << ans << "\n";
    }
}