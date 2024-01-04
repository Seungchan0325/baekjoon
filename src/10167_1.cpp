#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using Mine = tuple<int, int, ll>;

const int MAXN = 3005;

int n;
vector<Mine> mines;
ll arr[MAXN];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;

    vector<int> xs, ys;
    for(int i = 0; i < n; i++) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        mines.emplace_back(x, y, w);
        xs.push_back(x);
        ys.push_back(y);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<vector<tuple<int, ll>>> updates(xs.size());
    for(auto [x, y, w] : mines) {
        int nx = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        int ny = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
        updates[nx].emplace_back(ny, w);
    }

    ll ans = 0;
    for(int l = 0; l < xs.size(); l++) {
        for(int r = l; r < xs.size(); r++) {
            for(auto [y, w] : updates[r]) arr[y] += w;

            ll sum = 0;
            for(int y = 0; y < ys.size(); y++) {
                sum += arr[y];
                sum = max(0LL, sum);
                ans = max(sum, ans);
            }
        }
        memset(arr, 0, sizeof(arr));
    }

    cout << ans;
}