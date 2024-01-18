#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, tree[4*MAXN];
pair<int, int> arr[MAXN];
map<string, int> m;

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
    return query(start, mid, 2*index, left, right) + query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    while(true) {
        memset(tree, 0, sizeof(tree));

        cin >> n;
        if(n == 0) break;

        for(int i = 0; i < n; i++) {
            string s; cin >> s;
            m[s] = i;
        }

        for(int i = 0; i < n; i++) {
            string s; cin >> s;
            arr[i].first = m[s];
            arr[i].second = i;
        }

        sort(arr, arr + n);

        long long cnt = 0;
        for(int i = 0; i < n; i++) {
            cnt += query(0, n-1, 1, arr[i].second, n-1);
            update(0, n-1, 1, arr[i].second, 1);
        }

        cout << cnt << "\n";
    }
}