#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, arr[MAXN];
vector<int> tree[4*MAXN];

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].push_back(arr[s]);
        return;
    }

    int m = (s + e) >> 1;
    init(s, m, 2*idx); init(m+1, e, 2*idx+1);
    tree[idx].resize(e - s + 1);
    merge(tree[2*idx].begin(), tree[2*idx].end(),
        tree[2*idx+1].begin(), tree[2*idx+1].end(),
        tree[idx].begin());
}

int query(int l, int r, int k, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx].end() - upper_bound(tree[idx].begin(), tree[idx].end(), k);
    int m = (s + e) >> 1;
    return query(l, r, k, s, m, 2*idx) + query(l, r, k, m+1, e, 2*idx+1);
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
        int i, j, k;
        cin >> i >> j >> k;
        int result = query(i, j, k);
        cout << result << "\n";
    }
}