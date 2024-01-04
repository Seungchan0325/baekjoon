#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 300005;

ll tree[4*MAXN];

void update(int start, int end, int index, int pos, ll delta) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, delta);
    update(mid+1, end, 2*index+1, pos, delta);
    tree[index] = max(tree[2*index], tree[2*index+1]);
}

ll query(int start, int end, int index, int left, int right) {
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return max(query(start, mid, 2*index, left, right), query(mid+1, end, 2*index+1, left, right));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<pair<ll, int>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end(), [](pair<ll, int> a, pair<ll, int> b) {
        if(a.first == b.first) return b.second < a.second;
        return a.first < b.first;
    });

    for(int i = 0; i < n; i++) {
        ll prv = query(0, n-1, 1, 0, v[i].second);
        update(0, n-1, 1, v[i].second, prv + v[i].first);
    }

    cout << tree[1];
}