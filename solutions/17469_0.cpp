#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 100005;
const int MAXQ = 1000005;

int n, q, par[MAXN], root[MAXN], ans[MAXQ], ans_sz;
set<int> colors[MAXN];
pii queries[MAXQ+MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

bool Union(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return false;

    if(colors[x].size() < colors[y].size()) swap(x, y);

    root[y] = x;
    for(auto i : colors[y]) {
        colors[x].insert(i);
    }
    colors[y].clear();

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> q;
    for(int i = 2; i <= n; i++) {
        cin >> par[i];
    }
    for(int i = 1; i <= n; i++) {
        int color;
        cin >> color;
        colors[i].insert(color);
    }
    q += n - 1;
    for(int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    iota(root, root + n + 1, 0);
    for(int i = q-1; i >= 0; i--) {
        auto [type, a] = queries[i];
        if(type == 1) {
            Union(a, par[a]);
        } else {
            int result = colors[find(a)].size();
            ans[ans_sz++] = result;
        }
    }
    for(int i = ans_sz - 1; i >=0; i--) {
        cout << ans[i] << "\n";
    }
}