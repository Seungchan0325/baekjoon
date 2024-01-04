#include <bits/stdc++.h>

using namespace std;

const int INF = INT32_MAX;
const int MAXN = 100005;

int n, m, tree[4*MAXN];

void update(int start, int end, int index, int pos, int value) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] = value;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, value);
    update(mid+1, end, 2*index+1, pos, value);
    tree[index] = min(tree[2*index], tree[2*index+1]);
}

int query(int start, int end, int index, int left, int right) {
    if(end < left || right < start) return INF;
    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return min(query(start, mid, 2*index, left, right),
               query(mid+1, end, 2*index+1, left, right));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int Ai; cin >> Ai;
        update(0, n-1, 1, i, Ai);
    }

    cin >> m;
    for(int k = 0; k < m; k++) {
        int type, i, j;
        cin >> type >> i >> j;
        if(type == 1) {
            update(0, n-1, 1, i-1, j);
        } else {
            int result = query(0, n-1, 1, i-1, j-1);
            cout << result << "\n";
        }
    }
}