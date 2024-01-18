#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250005;
const int MAXV = 65540;

using ll = long long;

int n, k, arr[MAXN];
int tree[4*MAXV];

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

    if(left <= start && end <= right) {
        return tree[index];
    }

    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right)
         + query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int left = 0, right = k-1;
    for(int i = 0; i < k; i++) update(0, MAXV, 1, arr[i], 1);

    ll sum = 0;
    for(; right < n; left++, right++) {
        int l = 0, r = MAXV;
        while(l < r) {
            int mid = (l + r) / 2;
            int cnt = query(0, MAXV, 1, 0, mid);
            if(cnt < (k+1) / 2) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }

        sum += l;

        update(0, MAXV, 1, arr[left], -1);
        update(0, MAXV, 1, arr[right+1], 1);
    }

    cout << sum;
}