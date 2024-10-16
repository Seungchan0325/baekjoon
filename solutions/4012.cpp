// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

const int MAXN = 100005;

struct fenwick
{
    int N;
    vector<int> tree, v;
    void resize(const vector<int>& _v) {
        v = _v;
        N = v.size();
        tree.resize(v.size()+1);
    }

    int idx(int x) { return upper_bound(v.begin(), v.end(), x) - v.begin(); }
    void upd(int x, int d)
    {
        x = idx(x);
        while(x <= N) {
            tree[x] += d;
            x += x & -x;
        }
    }
    int qry(int x)
    {
        x = idx(x);
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

int N, K, A[MAXN], B[MAXN];
fenwick tree[4*MAXN];

vector<int> init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].resize({B[s]});
        return {B[s]};
    }

    int m = (s + e) / 2;
    auto l = init(s, m, 2*idx);
    auto r = init(m+1, e, 2*idx+1);
    vector<int> v(l.size() + r.size());
    merge(l.begin(), l.end(), r.begin(), r.end(), v.begin());
    tree[idx].resize(v);
    return v;
}

void update(int x, int y, int d, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx].upd(y, d);
        return;
    }

    int m = (s + e) / 2;
    update(x, y, 1, s, m, 2*idx);
    update(x, y, 1, m+1, e, 2*idx+1);
    tree[idx].upd(y, d);
}

int query(int l, int r, int x, int y, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;

    if(l <= s && e <= r) return tree[idx].qry(y) - tree[idx].qry(x-1);

    int m = (s + e) / 2;
    return query(l, r, x, y, s, m, 2*idx) + query(l, r, x, y, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        A[a] = i;
    }
    for(int i = 1; i <= N; i++) {
        int b;
        cin >> b;
        B[b] = i;
    }

    vector<tuple<int, int, int>> v;
    for(int i = 1; i <= N; i++) {
        v.emplace_back(A[i], B[i], i);
    }
    sort(v.begin(), v.end());

    init();
    long long ans = 0;
    for(auto [a, b, i] : v) {
        int l = i - K - 1;
        int r = i + K + 1;
        ans += query(1, l, b, N);
        ans += query(r, N, b, N);
        update(i, b, 1);
    }
    cout << ans;
}