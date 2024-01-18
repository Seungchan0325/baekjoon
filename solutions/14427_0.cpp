#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 987654321;
const int MAXN = 100005;

int n;
pii tree[4*MAXN];

void init(int st, int en, int idx) {
    if(st == en) {
        tree[idx].first = INF;
        tree[idx].second = st;
        return;
    }
    int mid = (st + en) / 2;
    init(st, mid, 2*idx);
    init(mid+1, en, 2*idx+1);

    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

void update(int st, int en, int idx, int pos, int v) {
    if(en < pos || pos < st) return;

    if(st == en) {
        tree[idx].first = v;
        return;
    }

    int mid = (st + en) / 2;
    update(st, mid, 2*idx, pos, v);
    update(mid+1, en, 2*idx+1, pos, v);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    init(0, n-1, 1);
    int v;
    for(int i = 0; i < n; i++) {
        cin >> v;
        update(0, n-1, 1, i, v);
    }

    int m; cin >> m;
    while(m--) {
        int t; cin >> t;
        if(t == 1) {
            int i, v; cin >> i >> v; i--;
            update(0, n-1, 1, i, v);
        }
        else if(t == 2) {
            cout << tree[1].second+1 << "\n";
        }
    }
}