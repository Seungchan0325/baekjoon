#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
int n, arr[MAXN], tree[4*MAXN];

void update(int start, int end, int index, int pos, int v) {
    if(end < pos || pos < start) return;
    
    if(start == end) {
        tree[index] = v;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, v);
    update(mid+1, end, 2*index+1, pos, v);

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
    for(int i = 1; i <= n; i++) cin >> arr[i];
    for(int i = 1; i <= n; i++) update(0, n, 1, i, 1);

    vector<pair<int, int>> ans;
    for(int i = 1; i <= n; i++) {
        int lo = 0, hi = n;
        while(lo+1 < hi) {
            int mid = (lo + hi) / 2;
            int cnt = query(0, n, 1, 0, mid);
            if(cnt <= arr[i]) lo = mid;
            else hi = mid;
        }

        ans.emplace_back(hi, i);
        update(0, n, 1, hi, 0);
    }

    sort(ans.begin(), ans.end());
    for(auto [_a, i] : ans) cout << i << "\n";
}