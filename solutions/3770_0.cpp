#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int MAXNM = 1005;

int n, m, k;
ll tree[4*MAXNM];
vector<pii> v;

void update(int start, int end, int index, int pos, ll delta) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, delta);
    update(mid+1, end, 2*index+1, pos, delta);
    tree[index] = tree[2*index] + tree[2*index+1];
}

ll query(int start, int end, int index, int left, int right) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];
    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) +
           query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for(int i = 1; i <= t; i++) {
        cin >> n >> m >> k;
        v = vector<pii>(k);
        for(auto& [s, e] : v) cin >> s >> e;
        sort(v.begin(), v.end());

        memset(tree, 0, sizeof(tree));
        ll sum = 0;
        for(auto [s, e] : v) {
            sum += query(0, m+1, 1, e+1, m+1);
            update(0, m+1, 1, e, 1);
        }

        cout << "Test case " << i << ": " << sum << "\n";
    }
}