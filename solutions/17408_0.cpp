#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 100005;

int N, M;
pii tree[4*MAXN];

pii merge(pii a, pii b)
{
    vector<int> v = {a.first, a.second, b.first, b.second};
    sort(v.begin(), v.end());

    return make_pair(v[3], v[2]);
}

void update(int pos, int value, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx].first = value;
        return;
    }

    int m = (s + e) / 2;
    update(pos, value, s, m, 2*idx);
    update(pos, value, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

pii query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return {0, 0};

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        update(i, x);
    }

    cin >> M;
    while(M--) {
        int t;
        cin >> t;
        if(t == 1) {
            int i, v;
            cin >> i >> v;
            update(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            auto [fi, se] = query(l, r);
            cout << fi + se << "\n";
        }
    }
}