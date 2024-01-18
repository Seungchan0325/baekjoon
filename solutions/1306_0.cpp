#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1000005;

ll tree[4*MAXN];

void update(int start, int end, int index, int pos, ll v) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] = v;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, v);
    update(mid+1, end, 2*index+1, pos, v);

    tree[index] = max(tree[2*index], tree[2*index+1]);
}

ll query(int start, int end, int index, int left, int right) {
    if(end < left || right < start) return 0;

    if(left <= start && end <= right)
        return tree[index];

    int mid = (start + end) / 2;
    return max(query(start, mid, 2*index, left, right),
               query(mid+1, end, 2*index+1, left, right));
}

int n, m;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int brightness; cin >> brightness;
        update(0, n-1, 1, i, brightness);
    }

    for(int i = m - 1; i < n - m + 1; i++) {
        int left = i - m + 1;
        int right = i + m  - 1;
        
        int result = query(0, n-1, 1, left, right);

        cout << result << " ";
    }
}