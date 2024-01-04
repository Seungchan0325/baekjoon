#include <bits/stdc++.h>

using namespace std;

using Group = tuple<int, int, int>;

const int MAXN = 20005;
const int MAXK = 50005;

int k, n, c;
tuple<int, int, int> groups[MAXK];

int lazy[4*MAXN];
int tree[4*MAXN];

void propagate(int start, int end, int index) {
    if(lazy[index]) {
        tree[index] += lazy[index];
        if(start != end) {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(int start, int end, int index, int left, int right, int delta) {
    propagate(start, end, index);
    if(end < left || right < start) return;

    if(left <= start && end <= right) {
        lazy[index] += delta;
        propagate(start, end, index);
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, delta);
    update(mid+1, end, 2*index+1, left, right, delta);

    tree[index] = max(tree[2*index], tree[2*index+1]);
}

int query(int start, int end, int index, int left, int right) {
    propagate(start, end, index);
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) {
        return tree[index];
    }

    int mid = (start + end) / 2;
    return max(query(start, mid, 2*index, left, right),
               query(mid+1, end, 2*index+1, left, right));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> k >> n >> c;
    for(int i = 0; i < k; i++) {
        auto& [s, e, m] = groups[i];
        cin >> s >> e >> m;
        s--; e--;
    }

    sort(groups, groups + k, [](Group& a, Group& b) {
        auto [sa, ea, ma] = a;
        auto [sb, eb, mb] = b;

        if(ea != eb) return ea < eb;
        return sa < sb;
    });

    int ans = 0;
    for(int i = 0; i < k; i++) {
        auto [s, e, m] = groups[i];
        int cnt = query(0, n-1, 1, s, e-1);
        int add = min(m, c - cnt);
        ans += add;
        update(0, n-1, 1, s, e-1, add);

        // cout << format("start: {}, end: {}, cnt: {}, add: {}\n", s, e, add, );
    }
    cout << ans;
}