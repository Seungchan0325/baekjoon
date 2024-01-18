#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

const int INF = 987654321;

ll calc(vector<int> road, vector<int> police) {
    ll ret = 0;
    int k = police.size();

    sort(police.begin(), police.end());
    sort(road.begin(), road.end());
    // vector<ll> pSum(police.size() + 1);
    // for (int i = 1; i <= police.size(); i++) pSum[i] = pSum[i - 1] + police[i - 1];

    // for (int i = 0; i < police.size(); i++)
    //     ret += pSum[police.size()] - pSum[i] - police[i] * (police.size() - i);

    // for (int i = 0; i < k; i++) {
    //     ret += (ll)police[i] * (ll)(-k + 2 * i + 1);
    // }

    for (int i = 0; i < k; i++) {
        auto l = lower_bound(road.begin(), road.end(), police[i]);
        for (int j = i + 1; j < k; j++) {
            if (l != road.end() && *l <= police[j]) {
                ret += police[j] - police[i];
            }
            else {
                ret += min(l == road.begin() ? INF : police[i] + police[j] - *(l - 1) * 2,
                           l == road.end() ? INF : *l * 2 - police[i] - police[j]);
            }
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> a(n), b(m), p(k), q(k);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0; i < k; i++) cin >> p[i] >> q[i];

    ll ans = 0;

    ans += calc(a, p);
    ans += calc(b, q);

    cout << ans << "\n";
}