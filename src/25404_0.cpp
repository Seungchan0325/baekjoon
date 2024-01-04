#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int MAXN = 100005;

int n;
pii arr[MAXN];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++ ) {
        cin >> arr[i].first;
        arr[i].second = i;
    }

    sort(arr, arr + n);

    int init_dist = arr[0].second;
    ll ans = min(init_dist, n - init_dist);
    for(int i = 0; i < n - 1; i++) {
        int dist = abs(arr[i].second - arr[i+1].second);
        ans += min(dist, n - dist);
    }

    cout << ans;
}