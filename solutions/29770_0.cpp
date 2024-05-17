#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;
const int MAXQ = 500005;

int N, Q, A[MAXN], E[MAXN], ans[MAXQ], tree[4*MAXN];
vector<pair<int, int>> queries[MAXQ];

void update(int pos, int delta, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx] += delta;
        return;
    }

    int m = (s + e) >> 1;
    update(pos, delta, s, m, 2*idx);
    update(pos, delta, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) >> 1;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        queries[r].emplace_back(l, i);
    }

    set<int> s;
    int hi = 0;
    for(int i = 1; i <= N; i++) {
        while(hi < N && s.count(A[hi+1]) == 0) s.insert(A[++hi]);
        s.erase(A[i]);
        update(i, hi - i + 1);
        E[i] = hi;
    }

    hi = N;
    for(int i = N; i >= 1; i--) {
        while(i < E[hi]) hi--;
        for(auto [l, idx] : queries[i]) {
            ans[idx] = max(query(l, hi), min(i - hi, i - l + 1));
        }
    }

    for(int i = 0; i < Q; i++) {
        cout << ans[i] << "\n";
    }
}