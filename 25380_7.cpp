#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

ll calc(vector<int> road, vector<int> police) {
    ll ret = 0;
    int k = police.size();

    sort(police.begin(), police.end());
    vector<ll> pSum(police.size() + 1);
    for (int i = 1; i <= police.size(); i++) pSum[i] = pSum[i - 1] + police[i - 1];

    for (int i = 0; i < police.size(); i++)
        ret += pSum[police.size()] - pSum[i] - police[i] * (police.size() - i);

    // for (int i = 0; i < k; i++) {
    //     ret += (ll)police[i] * (ll)(-k + 2 * i + 1);
    // }


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