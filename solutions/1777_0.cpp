#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
int arr[MAXN];

int tree[4*MAXN];

void update(int start, int end, int index, int pos, int delta) {
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

int query(int start, int end, int index, int left, int right) {
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) +
           query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];

    for(int i = 0; i < n; i++) update(0, n, 1, i, 1);

    vector<pair<int, int>> v;
    for(int i = n-1; i >= 0; i--) {
        int lo = 0, hi = n;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            int cnt = query(0, n, 1, mid, n);
            if(arr[i] < cnt) lo = mid;
            else hi = mid;
        }
        // cout << format("arr: {} lo: {} cnt: {} hi: {} cnt: {}\n", arr[i], lo, query(0, n, 1, lo, n), hi, query(0, n, 1, hi, n));
        update(0, n, 1, lo, -1);
        v.emplace_back(lo,  i);
    }

    sort(v.begin(), v.end());

    for(auto [idx, val] : v) cout << val + 1 << " ";
}