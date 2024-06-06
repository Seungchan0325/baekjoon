#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int N, a[MAXN], root[MAXN], sz[MAXN];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    assert(x != y);

    root[y] = x;
    sz[x] += sz[y];
    if(pq[x].size() < pq[y].size()) swap(pq[x], pq[y]);
    while(!pq[y].empty()) {
        pq[x].push(pq[y].top()); pq[y].pop();
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<pair<int, int>> vv;
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> a[i];
    }

    for(int i = 2; i <= N; i++) {
        if(a[i-1] >= a[i]) vv.emplace_back(i-1, i);
        else vv.emplace_back(i, i-1);
    }

    sort(vv.begin(), vv.end(), [](pair<int, int> x, pair<int, int> y) {
        auto xp = make_pair(a[x.first], a[x.second]);
        auto yp = make_pair(a[y.first], a[y.second]);

        return xp < yp;
    });

    iota(root, root + N + 1, 0);
    fill(sz, sz + N + 1, 1);
    for(int i = 1; i <= N; i++) {
        pq[i].emplace(a[i], i);
    }

    for(auto [u, v] : vv) {
        int up = find(u);
        int vp = find(v);
        while(!pq[vp].empty() && pq[vp].top().first + sz[vp] - 1 < a[u]) pq[vp].pop();
        while(!pq[up].empty() && pq[up].top().first + sz[up] - 1 < a[v]) pq[up].pop();
        merge(u, v);
    }

    int u = find(1);

    assert(pq[u].size() != 0);
    assert(sz[u] == N);

    vector<int> ans;
    while(!pq[u].empty()) {
        ans.push_back(pq[u].top().second); pq[u].pop();
    }
    sort(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
}