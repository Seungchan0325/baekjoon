#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const int inf = 1e9;

struct Seg {
    int n;
    vector<int> tree;
    void init(int _n) {
        n = _n;
        fill(tree.begin(), tree.end(), -inf);
        tree.resize(2*n, -inf);
    }
    void set(int x, int v)
    {
        tree[x+=n] = v;
        while(x>>=1) tree[x] = max(tree[x<<1], tree[x<<1|1]);
    }
    void update(int x, int v)
    {
        x+=n;
        tree[x] = max(v, tree[x]);
        while(x>>=1) tree[x] = max(tree[x<<1], tree[x<<1|1]);
    }
    int query(int l, int r)
    {
        int res = -inf;
        for(l+=n,r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) res = max(res, tree[l++]);
            if(~r&1) res = max(res, tree[r--]);
        }
        return res;
    }
};

int N, K, A[MAXN], dp[MAXN];
vector<int> v;
Seg seg;

bool check(int x)
{
    seg.init(v.size());
    dp[0] = A[0] <= x;
    for(int i = 1; i < N; i++) {
        int j = lower_bound(v.begin(), v.end(), A[i-1]) - v.begin();
        seg.update(j, dp[i-1]);
        j = upper_bound(v.begin(), v.end(), x - A[i]) - v.begin() - 1;
        dp[i] = seg.query(0, j) + 1;
        if(A[0] + A[i] <= x && dp[i] >= K) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for(int i = 0; i < N; i++) cin >> A[i];
    rotate(A, min_element(A, A+N), A+N);

    for(int i = 0; i < N; i++) v.push_back(A[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    ll lo = -1;
    ll hi = 2e9;
    while(lo+1 < hi) {
        ll mid = (lo + hi) / 2;
        if(check(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << "\n";
}