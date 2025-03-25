#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, x1[MAXN], _y1[MAXN], x2[MAXN], y2[MAXN], tree[4*MAXN];
int sz;

void update(int x, int v, int s = 0, int e = sz-1, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = max(tree[idx], v);
        return;
    }
    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 0, int e = sz-1, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    cin >> N;
    vector<int> v;
    for(int i = 1; i <= N; i++) cin >> x1[i] >> _y1[i] >> x2[i] >> y2[i], v.push_back(_y1[i]), v.push_back(y2[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    sz = v.size();

    vector<tuple<int, int, int>> start;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> end;
    for(int i = 1; i <= N; i++) {
        int idx = lower_bound(v.begin(), v.end(), _y1[i]) - v.begin();
        start.emplace_back(x1[i], idx, i);
    }
    sort(start.begin(), start.end());

    int ans = 0;
    for(auto [x, y, i] : start) {
        while(end.size() && get<0>(end.top()) < x) {
            update(get<1>(end.top()), get<2>(end.top()));
            end.pop();
        }
        int idx = lower_bound(v.begin(), v.end(), y2[i]) - v.begin();
        int c = query(0, y - 1) + 1;
        ans = max(ans, c);
        end.emplace(x2[i], idx, c);
    }
    cout << ans;
}