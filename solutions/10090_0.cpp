#include <bits/stdc++.h>

using namespace std;

using pii = pair<long long, long long>;

const long long MAXN = 1000005;

long long n, tree[MAXN * 4];
pii arr[MAXN];

void tree_update(long long start, long long end, long long idx, long long i, long long v) {
    if(i < start || end < i) return;

    if(start == end) {
        tree[idx] += v;
        return;
    }

    long long mid = (start + end) / 2;
    tree_update(start, mid, idx * 2, i, v);
    tree_update(mid + 1, end, idx * 2 + 1, i, v);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

long long tree_query(long long start, long long end, long long idx, long long qstart, long long qend) {
    if(qend < start || end < qstart) return 0;

    if(qstart <= start && end <= qend) {
        return tree[idx];
    }

    long long mid = (start + end) / 2;
    return tree_query(start, mid, idx * 2, qstart, qend) + tree_query(mid + 1, end, idx * 2 + 1, qstart, qend);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(long long i = 0; i < n; i++) { cin>>arr[i].first; arr[i].second = i; }

    sort(arr, arr + n);

    long long sum = 0;
    for(long long i = 0; i < n; i++) {
        sum += tree_query(0, n-1, 1, arr[i].second, n-1);
        tree_update(0, n-1, 1, arr[i].second, 1);
    }
    cout<<sum;
}