#include <bits/stdc++.h>

using namespace std;

const int MAXSZ = 20005;

struct T {
    int mn, cnt;
};

int N, ans, lazy[4*MAXSZ];
T tree[4*MAXSZ];

T merge(T a, T b)
{
    if(a.mn == b.mn) return {a.mn, a.cnt + b.cnt};
    if(a.mn > b.mn) swap(a, b);
    return {a.mn, a.cnt};
}

void build(int s = 0, int e = MAXSZ - 1, int idx = 1)
{
    lazy[idx] = 0;
    if(s == e) {
        tree[idx].mn = 0;
        tree[idx].cnt = 1;
        return;
    }

    int m = (s + e) >> 1;
    build(s, m, 2*idx); build(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx] != 0) {
        tree[idx].mn += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int delta, int s = 0, int e = MAXSZ - 1, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy[idx] += delta;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, delta, s, m, 2*idx);
    update(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    cin >> N;
    vector<int> xs, ys;
    vector<tuple<int, int, int, int>> rect(N);
    for(auto& [x1, y1, x2, y2] : rect) {
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        x1 += 10000;
        x2 += 10000;
        y1 += 10000;
        y2 += 10000;
        xs.push_back(x1); xs.push_back(x2);
        ys.push_back(y1); ys.push_back(y2);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<vector<tuple<int, int>>> push(ys.size());
    vector<vector<tuple<int, int>>> pop(ys.size());
    for(auto [x1, y1, x2, y2] : rect) {
        int s = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
        int e = lower_bound(ys.begin(), ys.end(), y2) - ys.begin();
        push[s].emplace_back(x1, x2 - 1);
        pop[e].emplace_back(x1, x2 - 1);
    }

    build();
    int zeros = tree[1].cnt;
    int sum = 0;
    for(int y = 0; y < ys.size(); y++) {
        for(auto [x1, x2] : push[y]) update(x1, x2, 1);
        sum += abs(zeros - tree[1].cnt);
        for(auto [x1, x2] : pop[y]) update(x1, x2, -1);
        zeros = tree[1].cnt;
    }
    ans += 2*sum;

    push = vector<vector<tuple<int, int>>>(xs.size());
    pop = vector<vector<tuple<int, int>>>(xs.size());
    for(auto [x1, y1, x2, y2] : rect) {
        int s = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
        int e = lower_bound(xs.begin(), xs.end(), x2) - xs.begin();
        push[s].emplace_back(y1, y2 - 1);
        pop[e].emplace_back(y1, y2 - 1);
    }

    build();
    zeros = tree[1].cnt;
    sum = 0;
    for(int x = 0; x < xs.size(); x++) {
        for(auto [y1, y2] : push[x]) update(y1, y2, 1);
        sum += abs(zeros - tree[1].cnt);
        for(auto [y1, y2] : pop[x]) update(y1, y2, -1);
        zeros = tree[1].cnt;
    }
    ans += 2*sum;

    cout << ans;
}