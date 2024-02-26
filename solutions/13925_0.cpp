#include <bits/stdc++.h>

using namespace std;

using llint = long long;

const int MAXN = 100005;
const llint MOD = 1e9 + 7;

int N, M, arr[MAXN];
llint tree[4*MAXN], lazy[4*MAXN][2];

llint merge(llint a, llint b)
{
    return (a + b) % MOD;
}

void init(int s = 1, int e = N, int idx = 1)
{
    lazy[idx][0] = 1;
    lazy[idx][1] = 0;
    if(s == e) {
        tree[idx] = arr[s];
        return;
    }
    int m = (s + e) >> 1;
    init(s, m, 2*idx); init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void propagate(int s, int e, int idx)
{
    llint& a1 = lazy[idx][0];
    llint& b1 = lazy[idx][1];
    tree[idx] = ((a1 * tree[idx]) % MOD + ((e - s + 1) * b1) % MOD) % MOD;
    if(s != e) {
        for(auto i : {2*idx, 2*idx+1}) {
            llint& a0 = lazy[i][0];
            llint& b0 = lazy[i][1];
            a0 = (a0 * a1) % MOD;
            b0 = ((a1 * b0) % MOD + b1) % MOD;
        }
    }
    a1 = 1;
    b1 = 0;
}

void update(int l, int r, llint mul, llint sum, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        assert(lazy[idx][0] == 1 && lazy[idx][1] == 0);
        lazy[idx][0] = mul;
        lazy[idx][1] = sum;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, mul, sum, s, m, 2*idx);
    update(l, r, mul, sum, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

llint query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return 0;
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
    cin >> M;
    while(M--) {
        int t, x, y, v;
        cin >> t >> x >> y;
        if(t != 4) cin >> v;
        if(t == 1) update(x, y, 1, v);
        else if(t == 2) update(x, y, v, 0);
        else if(t == 3) update(x, y, 0, v);
        else {
            llint result = query(x, y);
            cout << result << "\n";
        }
    }
}