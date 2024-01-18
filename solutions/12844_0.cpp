#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int n, m, arr[MAXN], lazy[4*MAXN], tree[4*MAXN];

void init(int start, int end, int index) {
    if(start == end) {
        tree[index] = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    init(start, mid, 2*index);
    init(mid+1, end, 2*index+1);
    tree[index] = tree[2*index] ^ tree[2*index+1];
}

void propagate(int start, int end, int index) {
    if(lazy[index]) {
        if((end - start + 1) % 2 == 1)
            tree[index] ^= lazy[index];
        if(start != end) {
            lazy[2*index] ^= lazy[index];
            lazy[2*index+1] ^= lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(int start, int end, int index, int left, int right, int delta) {
    propagate(start, end, index);
    if(end < left || right < start) return;

    if(left <= start && end <= right) {
        if((end - start + 1) % 2 == 1)
            tree[index] ^= delta;
        if(start != end) {
            lazy[2*index] ^= delta;
            lazy[2*index+1] ^= delta;
        }
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, delta);
    update(mid+1, end, 2*index+1, left, right, delta);
    tree[index] = tree[2*index] ^ tree[2*index+1];
}

int query(int start, int end, int index, int left, int right) {
    propagate(start, end, index);
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) ^ query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];
    cin >> m;

    init(0, n-1, 1);
    while(m--) {
        int type; cin >> type;
        if(type == 1) {
            int i, j, k; cin >> i >> j >> k;
            update(0, n-1, 1, i, j, k);
        } else {
            int i, j; cin >> i >> j;
            int result = query(0, n-1, 1, i, j);
            cout << result << "\n";
        }
    }
}