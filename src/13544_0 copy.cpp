#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, last_ans, arr[MAXN];
vector<int> tree[4*MAXN];

void build(int start, int end, int index) {
    if(start == end) {
        tree[index].push_back(arr[start]);
        return;
    }

    int mid = (start + end) / 2;
    build(start, mid, 2*index);
    build(mid+1, end, 2*index+1);

    tree[index].resize(tree[2*index].size() + tree[2*index+1].size());
    merge(tree[2*index].begin(), tree[2*index].end(), tree[2*index+1].begin(), tree[2*index+1].end(), tree[index].begin());
}

int query(int start, int end, int index, int left, int right, int k) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index].size() - (upper_bound(tree[index].begin(), tree[index].end(), k) - tree[index].begin());

    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right, k) + query(mid+1, end, 2*index+1, left, right, k);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];
    cin >> m;
    build(0, n-1, 1);
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        int i = a ^ last_ans;
        int j = b ^ last_ans;
        int k = c ^ last_ans;

        last_ans = query(0, n-1, 1, i-1, j-1, k);
        cout << last_ans << "\n";
    }
}