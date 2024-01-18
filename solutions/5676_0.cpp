#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, k, tree[4*MAXN];

void update(int start, int end, int index, int pos, int value) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] = value;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, value);
    update(mid+1, end, 2*index+1, pos, value);
    int lr = tree[2*index] * tree[2*index+1];
    if(lr < 0) tree[index] = -1;
    else if(lr == 0) tree[index] = 0;
    else tree[index] = 1;
}

int query(int start, int end, int index, int left, int right) {
    if(end < left || right < start) return 1;
    if(left <= start && end <= right) return tree[index];
    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) * query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    while(cin >> n >> k) {
        memset(tree, 0, sizeof(tree));
        for(int i = 0; i < n; i++) {
            int v; cin >> v;
            update(0, n-1, 1, i, v);
        }

        while(k--) {
            char type; cin >> type;
            if(type == 'C') {
                int i, v; cin >> i >> v;
                update(0, n-1, 1, i-1, v);
            } else {
                int i, j; cin >> i >> j;
                int result = query(0, n-1, 1, i-1, j-1);
                if(result < 0) cout << '-';
                else if(result == 0) cout << '0';
                else cout << '+';
            }
        }
        cout << "\n";
    }
}