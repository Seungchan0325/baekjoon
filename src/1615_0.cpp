#include <bits/stdc++.h>

using namespace std;

const int MAXM = 2005;

int n, m, tree[4*MAXM];

void update(int pos, int delta, int start = 0, int end = n, int index = 1)
{
    if(end < pos || pos < start) return;
    if(start == end) {
        tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(pos, delta, start, mid, 2*index);
    update(pos, delta, mid+1, end, 2*index+1);
    tree[index] = tree[2*index] + tree[2*index+1];
}

int query(int left, int right, int start = 0, int end = n, int index = 1)
{
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return query(left, right, start, mid, 2*index) + query(left, right, mid+1, end, 2*index+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for(auto& [i, j] : edges) {
        cin >> i >> j;
    }
    sort(edges.begin(), edges.end());

    long long ans = 0;
    for(auto [i, j] : edges) {
        ans += query(j + 1, m);
        update(j, 1);
    }
    cout << ans;
}