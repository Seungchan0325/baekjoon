#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, arr[MAXN], tree[4*MAXN];

void build(int start = 0, int end = n-1, int index = 1) {
    if(start == end) {
        tree[index] += arr[start] % 2;
        return;
    }

    int mid = (start + end) / 2;
    build(start, mid, 2*index);
    build(mid+1, end, 2*index+1);

    tree[index] = tree[2*index] + tree[2*index+1];
}

void update(int pos, int value, int start = 0, int end = n-1, int index = 1) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] -= arr[start] % 2;
        tree[index] += value % 2;
        arr[start] = value;
        return;
    }

    int mid = (start + end) / 2;
    update(pos, value, start, mid, 2*index);
    update(pos, value, mid+1, end, 2*index+1);
    tree[index] = tree[2*index] + tree[2*index+1];
}

int query(int left, int right, int start = 0, int end = n-1, int index = 1) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return query(left, right, start, mid, 2*index) + query(left, right, mid+1, end, 2*index+1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];
    build();

    cin >> m;
    while(m--) {
        int type; cin >> type;

        if(type == 1) {
            int i, x; cin >> i >> x;
            update(i-1, x);
        } else if(type == 2) {
            int l, r; cin >> l >> r;
            int result = query(l-1, r-1);
            cout << (r - l + 1) - result << "\n";
        } else if(type == 3) {
            int l, r; cin >> l >> r;
            int result = query(l-1, r-1);
            cout << result << "\n";
        } else {
            assert(0);
        }
    }
}