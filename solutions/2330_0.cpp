#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;

int N, tree[4*MAXN], root[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    root[y] = x;
}

void update(int x, int v, int s = 0, int e = MAXN, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] += v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int qry(int l, int r, int s = 0, int e = MAXN, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return qry(l, r, s, m, 2*idx) + qry(l, r, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    vector<array<int, 3>> v(N);
    for(auto& [a, b, c] : v) cin >> a >> b >> c;
    sort(v.begin(), v.end(), [](array<int, 3> a, array<int, 3> b)
    {
        return a[1] < b[1];
    });

    iota(root, root + MAXN, 0);

    for(auto [a, b, c] : v) {
        while(qry(a, b) < c) {
            int idx = find(b);
            update(idx, 1);
            merge(idx-1, idx);
        }
    }

    cout << qry(0, MAXN) << "\n";
}